#include "PreCompile.h"
#include "Collision.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/Level.h>	
#include <EngineCore/Actor.h>	

UCollision::UCollision()
{
}

UCollision::~UCollision()
{
	for (UCollision* Other : CollisionCheckSet)
	{
		// 너한테서 나를 빼야해를 하고 죽습니다.
		Other->CollisionCheckSet.erase(this);
	}
}

void UCollision::SetCollisionProfileName(std::string_view _ProfileName)
{
	if (_ProfileName == GetCollisionProfileName())
	{
		return;
	}

	std::string UpperName = UEngineString::ToUpper(_ProfileName);

	std::string PrevProfileName = GetCollisionProfileName();
	ProfileName = UpperName;
	ULevel* Level = GetActor()->GetWorld();

	std::shared_ptr<UCollision> ThisPtr = GetThis<UCollision>();
	Level->ChangeCollisionProfileName(ProfileName, PrevProfileName, ThisPtr);
}

bool UCollision::CollisionCheck(std::string_view _OtherName, std::vector<UCollision*>& _Vector)
{
	std::string UpperName = UEngineString::ToUpper(_OtherName);

	std::map<std::string, std::list<std::shared_ptr<class UCollision>>>& Collision = GetWorld()->Collisions;

	if (false == Collision.contains(UpperName))
	{
		MSGASSERT("존재하지 않는 그룹과 충돌할수 없습니다" + std::string(UpperName));
		return false;
	}

	// 절대 네버 절대 안된다.
	// std::list<std::shared_ptr<class UCollision>> Group = Collision[_OtherName];

	std::list<std::shared_ptr<class UCollision>>& Group = Collision[UpperName];

	for (std::shared_ptr<class UCollision>& OtherCol : Group)
	{
		if (false == OtherCol->IsActive())
		{
			continue;
		}

		if (true == FTransform::Collision(CollisionType, Transform, OtherCol->CollisionType, OtherCol->Transform))
		{
			_Vector.push_back(OtherCol.get());
		}
	}

	return 0 != _Vector.size();
}

bool UCollision::CollisionCheck(std::string_view _OtherName, FVector _NextPos, std::vector<UCollision*>& _Vector)
{
	std::string UpperName = UEngineString::ToUpper(_OtherName);

	std::map<std::string, std::list<std::shared_ptr<class UCollision>>>& Collision = GetWorld()->Collisions;

	if (false == Collision.contains(UpperName))
	{
		MSGASSERT("존재하지 않는 그룹과 충돌할수 없습니다" + std::string(UpperName));
		return false;
	}

	// 절대 네버 절대 안된다.
	// std::list<std::shared_ptr<class UCollision>> Group = Collision[_OtherName];

	FTransform NextTransform = Transform;

	NextTransform.Location += _NextPos;
	NextTransform.TransformUpdate();

	std::list<std::shared_ptr<class UCollision>>& Group = Collision[UpperName];

	for (std::shared_ptr<class UCollision>& OtherCol : Group)
	{
		if (false == OtherCol->IsActive())
		{
			continue;
		}

		if (true == FTransform::Collision(CollisionType, NextTransform, OtherCol->CollisionType, OtherCol->Transform))
		{
			_Vector.push_back(OtherCol.get());
		}
	}

	return 0 != _Vector.size();
}


void UCollision::BeginPlay()
{
	USceneComponent::BeginPlay();
}

void UCollision::SetRadius(float _Value)
{
	FVector Scale = GetWorldScale3D();
	Scale.X = _Value * 2.0f;
	SetScale3D(Scale);
}

void UCollision::SetCollisionEnter(std::function<void(UCollision*, UCollision*)> _Function)
{
	if ("NONE" == GetCollisionProfileName())
	{
		MSGASSERT("아직 충돌 그룹이 지정되지 않은 충돌체를 이벤트 등록하려고 했습니다.");
		return;
	}

	if (true == IsEvent())
	{
		Enter = _Function;
		return;
	}

	Enter = _Function;
	ULevel* Level = GetActor()->GetWorld();
	std::shared_ptr<UCollision> ThisPtr = GetThis<UCollision>();

	// 중간에 프로파일 네임을 바꾸거나. 이러면 문제가 생길수 있다.
	Level->CheckCollisions[GetCollisionProfileName()].push_back(ThisPtr);
}

void UCollision::SetCollisionStay(std::function<void(UCollision*, UCollision*)> _Function)
{
	if ("NONE" == GetCollisionProfileName())
	{
		MSGASSERT("아직 충돌 그룹이 지정되지 않은 충돌체를 이벤트 등록하려고 했습니다.");
		return;
	}

	if (true == IsEvent())
	{
		Stay = _Function;
		return;
	}

	Stay = _Function;
	ULevel* Level = GetActor()->GetWorld();
	std::shared_ptr<UCollision> ThisPtr = GetThis<UCollision>();

	// 중간에 프로파일 네임을 바꾸거나. 이러면 문제가 생길수 있다.
	Level->CheckCollisions[GetCollisionProfileName()].push_back(ThisPtr);
}

void UCollision::SetCollisionEnd(std::function<void(UCollision*, UCollision*)> _Function)
{
	if ("NONE" == GetCollisionProfileName())
	{
		MSGASSERT("아직 충돌 그룹이 지정되지 않은 충돌체를 이벤트 등록하려고 했습니다.");
		return;
	}

	if (true == IsEvent())
	{
		End = _Function;
		return;
	}

	End = _Function;
	ULevel* Level = GetActor()->GetWorld();
	std::shared_ptr<UCollision> ThisPtr = GetThis<UCollision>();
	Level->CheckCollisions[GetCollisionProfileName()].push_back(ThisPtr);
}

void UCollision::CollisionEventCheck(std::shared_ptr<UCollision> _Other)
{
	if (false == _Other->IsActive())
	{
		return;
	}

	if (true == FTransform::Collision(CollisionType, Transform, _Other->CollisionType, _Other->Transform))
	{
		// 충돌 했다.
		// 충돌 했는데 너 내가 왜 몰라?
		if (false == CollisionCheckSet.contains(_Other.get()))
		{

			// 없는데 충돌은 최초충돌 
			// 전에는 한쪽만 기억하고 있었다.
			// 플레이어가             몬스터를 기억하는 것 <= ex) 어 이녀석이랑 나랑 충돌했네
			CollisionCheckSet.insert(_Other.get());
			// 몬스터는 플레이어를 기억합니다.
			_Other->CollisionCheckSet.insert(this);
			if (nullptr != Enter)
			{
				Enter(this, _Other.get());
			}
		}
		else
		{
			// 충돌을 했는데 전에 나랑 부딪친적이 있다.
			if (nullptr != Stay)
			{
				Stay(this, _Other.get());
			}
		}
	}
	else
	{
		if (true == CollisionCheckSet.contains(_Other.get()))
		{
			if (nullptr != End)
			{
				End(this, _Other.get());
			}

			// 무조건 가독성과 사용성
			CollisionCheckSet.erase(_Other.get());
			_Other->CollisionCheckSet.erase(this);
		}
	}
}

void UCollision::DebugRender(UEngineCamera* _Camera, float _DeltaTime)
{
	URenderUnit Unit;

	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();
	//	// 랜더러는 월드 뷰 프로젝트를 다 세팅받았고
	RendererTrans.View = CameraTrans.View;
	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;

	Unit.SetMesh("Rect");
	Unit.SetMaterial("CollisionDebugMaterial");


	Unit.ConstantBufferLinkData("FTransform", GetTransformRef());
	FVector Color = { 0.0f, 1.0f, 0.0f };
	Unit.ConstantBufferLinkData("OutColor", Color);

	Unit.Render(_Camera, _DeltaTime);

}



