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

	// ī�޶� ���� Ÿ���� ������ �ɰ��̹Ƿ� �������� �̵��մϴ�.
	CameraTarget = std::make_shared<UEngineRenderTarget>();
	CameraTarget->CreateTarget(UEngineCore::GetScreenScale());
	CameraTarget->CreateDepth();

	// ī�޶� ������ ����� �׸��� ������ŭ�� �ٸ� �ָ� ���� �������� �ִµ�.
}

UEngineCamera::~UEngineCamera()
{
	Renderers.clear();
}

void UEngineCamera::Tick(float _DetlaTime)
{
	USceneComponent::ComponentTick(_DetlaTime);
	// ī�޶�� ƽ���� �ڽ��� ��� ������Ʈ�� ����Ѵ��� �������鿡�� �������� �̴ϴ�.
	Transform.View;
	Transform.Projection;
}

void UEngineCamera::Render(float _DetlaTime)
{
	// ������ �����ϱ� ���� �ѹ� ����Ʈ �����ϰ� 
	UEngineCore::GetDevice().GetContext()->RSSetViewports(1, &ViewPortInfo);
	CameraTarget->Clear();
	CameraTarget->Setting();

	//// Ranged for�� �������� ���簡 �Ͼ�Ƿ�
	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& RenderList = RenderGroup.second;

		if (true == RendererZSort[RenderGroup.first])
		{
			// ���� z���� ������ ������������ ���� ����.
			// ũ�� ���ؼ� ũ�Ⱑ �� �������� �������� �ű��.
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

	//// Ranged for�� �������� ���簡 �Ͼ�Ƿ�
	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& RenderList = RenderGroup.second;
		std::list<std::shared_ptr<URenderer>>::iterator StartIter = RenderList.begin();
		std::list<std::shared_ptr<URenderer>>::iterator EndIter = RenderList.end();

		// �𸮾��� �߰��� �����Ҽ� ����.
		for (; StartIter != EndIter; )
		{
			if (false == (*StartIter)->IsDestroy())
			{
				++StartIter;
				continue;
			}

			// �������� ���� �ʿ䰡 �����ϴ�.
			// (*RenderStartIter) ���� ���� ������ ��������.
			// ������Ʈ�� �޸𸮸� �����Ҽ� ������ ������ ���͸� ������ �ִ�.
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
			MSGASSERT("�������� �ʴ� �ݸ��� �׷�� �浹�Ҽ��� �����ϴ�.");
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
				MSGASSERT("���̷� �浹�Ҽ� ���� Ÿ���Դϴ�.");
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
			MSGASSERT("�������� �ʴ� �ݸ��� �׷�� �浹�Ҽ��� �����ϴ�.");
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
				MSGASSERT("���̷� �浹�Ҽ� ���� Ÿ���Դϴ�.");
				break;
			}
		}
	}


	return _Collision.size() != 0;
}