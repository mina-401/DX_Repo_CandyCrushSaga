#include "PreCompile.h"
#include "EngineCamera.h"
#include "Renderer.h"
#include "EngineRenderTarget.h"
#include "Collision.h"
#include "EngineCore.h"
#include "Level.h"

UEngineCamera::UEngineCamera()
{
}

void UEngineCamera::BeginPlay()
{
	USceneComponent::BeginPlay();

	FVector Scale = UEngineCore::GetScreenScale();

	ProjectionScale = Scale;

	ViewPortInfo.Width = UEngineCore::GetScreenScale().X;
	ViewPortInfo.Height = UEngineCore::GetScreenScale().Y;
	ViewPortInfo.TopLeftX = 0.0f;
	ViewPortInfo.TopLeftY = 0.0f;
	ViewPortInfo.MinDepth = 0.0f;
	ViewPortInfo.MaxDepth = 1.0f;

	// 카메라 마다 타겟을 가지게 될것이므로 이쪽으로 이동합니다.
	CameraTarget = std::make_shared<UEngineRenderTarget>();
	CameraTarget->CreateTarget(UEngineCore::GetScreenScale());
	CameraTarget->CreateDepth();

	// 카메라를 여러개 만들고 그릴때 뎁스만큼은 다른 애를 쓰고 싶을때가 있는데.
}

UEngineCamera::~UEngineCamera()
{
	Renderers.clear();
}

void UEngineCamera::Tick(float _DetlaTime)
{
	USceneComponent::ComponentTick(_DetlaTime);
	// 카메라는 틱에서 자신의 뷰와 프로젝트를 계산한다음 랜더러들에게 전달해줄 겁니다.
	Transform.View;
	Transform.Projection;
}

void UEngineCamera::Render(float _DetlaTime)
{
	// 랜더링 진입하기 전에 한번 뷰포트 세팅하고 
	UEngineCore::GetDevice().GetContext()->RSSetViewports(1, &ViewPortInfo);
	CameraTarget->Clear();
	CameraTarget->Setting();

	//// Ranged for를 돌릴때는 복사가 일어나므로
	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& RenderList = RenderGroup.second;

		if (true == RendererZSort[RenderGroup.first])
		{
			// 둘의 z값이 완전히 겹쳐있을때는 답이 없다.
			// 크기 비교해서 크기가 더 작은쪽을 왼쪽으로 옮긴다.
			RenderList.sort([](std::shared_ptr<URenderer>& _Left, std::shared_ptr<URenderer>& _Right)
				{
					return _Left->GetTransformRef().WorldLocation.Z > _Right->GetTransformRef().WorldLocation.Z;
				});
		}


		for (std::shared_ptr<URenderer> Renderer : RenderList)
		{
			if (false == Renderer->IsActive())
			{
				continue;
			}

			Renderer->Render(this, _DetlaTime);
		}
	}
}

void UEngineCamera::Release(float _DeltaTime)
{

	//// Ranged for를 돌릴때는 복사가 일어나므로
	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& RenderList = RenderGroup.second;
		std::list<std::shared_ptr<URenderer>>::iterator StartIter = RenderList.begin();
		std::list<std::shared_ptr<URenderer>>::iterator EndIter = RenderList.end();

		// 언리얼은 중간에 삭제할수 없어.
		for (; StartIter != EndIter; )
		{
			if (false == (*StartIter)->IsDestroy())
			{
				++StartIter;
				continue;
			}

			// 랜더러는 지울 필요가 없습니다.
			// (*RenderStartIter) 누가 지울 권한을 가졌느냐.
			// 컴포넌트의 메모리를 삭제할수 권한은 오로지 액터만 가지고 있다.
			StartIter = RenderList.erase(StartIter);
		}
	}
}

void UEngineCamera::SetZSort(int _Order, bool _Value)
{
	RendererZSort[_Order] = _Value;
}

void UEngineCamera::ChangeRenderGroup(int _PrevGroupOrder, std::shared_ptr<URenderer> _Renderer)
{
	Renderers[_PrevGroupOrder].remove(_Renderer);
	Renderers[_Renderer->GetOrder()].push_back(_Renderer);
}

void UEngineCamera::CalculateViewAndProjection()
{
	FTransform& Trans = GetTransformRef();

	Trans.View.View(Trans.World.ArrVector[3], Trans.World.GetFoward(), Trans.World.GetUp());

	switch (ProjectionType)
	{
	case EProjectionType::Perspective:
		Trans.Projection.PerspectiveFovDeg(FOV, ProjectionScale.X, ProjectionScale.Y, Near, Far);
		break;
	case EProjectionType::Orthographic:
		Trans.Projection.OrthographicLH(ProjectionScale.X, ProjectionScale.Y, Near, Far);
		break;
	default:
		break;
	}

	int a = 0;
}



bool UEngineCamera::CheckPickCollision(std::string_view _CollisionProfile, std::vector<class UCollision*>& _Collision)
{
	CalculateViewAndProjection();

	if (ProjectionType == EProjectionType::Perspective)
	{
		FVector MousePos = UEngineCore::GetMainWindow().GetMousePos();
		FVector ScreenSize = UEngineCore::GetMainWindow().GetWindowSize();

		FVector RayOrigin = FVector(0.0f, 0.0f, 0.0f, 1.0f);
		FVector RayDirection = MousePos;

		FMatrix ViewPort;
		ViewPort.ViewPort(ScreenSize.X, ScreenSize.Y, 0.0f, 0.0f, 0.0f, 1.0f);
		FMatrix Projection = GetTransformRef().Projection;
		FMatrix InvView = GetTransformRef().View.InverseReturn();

		MousePos.X = (2.0f * MousePos.X / ScreenSize.X - 1.0f) / Projection.Arr2D[0][0];
		MousePos.Y = (-2.0f * MousePos.Y / ScreenSize.Y + 1.0f) / Projection.Arr2D[1][1];
		MousePos.Z = 1.0f;

		RayOrigin.DirectVector = DirectX::XMVector3TransformCoord(RayOrigin.DirectVector, InvView.DirectMatrix);

		RayDirection.DirectVector = DirectX::XMVectorSet(MousePos.X, MousePos.Y, 1.0f, 0.0f);
		RayDirection.DirectVector = DirectX::XMVector3TransformNormal(RayDirection.DirectVector, InvView.DirectMatrix);
		RayDirection.DirectVector = DirectX::XMVector3Normalize(RayDirection.DirectVector);


		FTransform RayTrans;
		RayTrans.SetRayOrigin(RayOrigin);
		RayTrans.SetRayDirection(RayDirection);



		ULevel* Level = GetWorld();

		std::string UpperName = UEngineString::ToUpper(_CollisionProfile.data());

		if (false == GetWorld()->Collisions.contains(UpperName))
		{
			MSGASSERT("존재하지 않는 콜리전 그룹과 충돌할수는 없습니다.");
			return false;
		}

		std::list<std::shared_ptr<UCollision>>& CollisionGroup = GetWorld()->Collisions[UpperName];

		for (std::shared_ptr<UCollision>& Collision : CollisionGroup)
		{
			ECollisionType Type = Collision->GetCollisionType();

			switch (Type)
			{
			case ECollisionType::Sphere:
				if (true == FTransform::OBBToRay(Collision->GetTransformRef(), RayTrans))
				{
					_Collision.push_back(Collision.get());
				}
				break;
			case ECollisionType::AABB:
				if (true == FTransform::OBBToRay(Collision->GetTransformRef(), RayTrans))
				{
					_Collision.push_back(Collision.get());
				}
				break;
			case ECollisionType::OBB:
				if (true == FTransform::OBBToRay(Collision->GetTransformRef(), RayTrans))
				{
					_Collision.push_back(Collision.get());
				}
				break;
			case ECollisionType::RAY:
			case ECollisionType::Max:
			case ECollisionType::Point:
			case ECollisionType::Rect:
			case ECollisionType::CirCle:
			case ECollisionType::OBB2D:
			default:
				MSGASSERT("레이로 충돌할수 없는 타입입니다.");
				break;
			}
		}
	}
	else if (ProjectionType == EProjectionType::Orthographic)
	{
		FVector MousePos = UEngineCore::GetMainWindow().GetMousePos();
		FVector ScreenSize = UEngineCore::GetMainWindow().GetWindowSize();

		MousePos.X = (2.0f * MousePos.X / ScreenSize.X - 1.0f);
		MousePos.Y = (1.0f - 2.0f * MousePos.Y / ScreenSize.Y);
		MousePos.Z = 1.0f;

		MousePos *= GetTransformRef().Projection.InverseReturn();
		MousePos *= GetTransformRef().View.InverseReturn();
		MousePos.Z = 0.0f;

		FTransform RayTrans;
		RayTrans.SetRayOrigin(MousePos);
		RayTrans.SetRayDirection(FVector(0.0f, 0.0f, 1.0f));

		ULevel* Level = GetWorld();

		std::string UpperName = UEngineString::ToUpper(_CollisionProfile.data());

		if (false == GetWorld()->Collisions.contains(UpperName))
		{
			MSGASSERT("존재하지 않는 콜리전 그룹과 충돌할수는 없습니다.");
			return false;
		}

		std::list<std::shared_ptr<UCollision>>& CollisionGroup = GetWorld()->Collisions[UpperName];


		for (std::shared_ptr<UCollision>& Collision : CollisionGroup)
		{
			ECollisionType Type = Collision->GetCollisionType();

			switch (Type)
			{
			case ECollisionType::Sphere:
				if (true == FTransform::OBBToRay(Collision->GetTransformRef(), RayTrans))
				{
					_Collision.push_back(Collision.get());
				}
				break;
			case ECollisionType::AABB:
				if (true == FTransform::OBBToRay(Collision->GetTransformRef(), RayTrans))
				{
					_Collision.push_back(Collision.get());
				}
				break;
			case ECollisionType::OBB:
				if (true == FTransform::OBBToRay(Collision->GetTransformRef(), RayTrans))
				{
					_Collision.push_back(Collision.get());
				}
				break;
			case ECollisionType::RAY:
			case ECollisionType::Max:
			case ECollisionType::Point:
			case ECollisionType::Rect:
			case ECollisionType::CirCle:
			case ECollisionType::OBB2D:
			default:
				MSGASSERT("레이로 충돌할수 없는 타입입니다.");
				break;
			}
		}
	}


	return _Collision.size() != 0;
}