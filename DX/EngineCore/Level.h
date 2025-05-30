#pragma once

#include <EngineBase/Object.h>
#include <EngineBase/EngineDebug.h>
#include "Light.h"

// 설명 :
class ULevel : public UObject
{
	friend class URenderUnit;
	friend class UCollision;
	friend class UEngineCore;
	friend class ULight;
	friend class UEngineCamera;

public:
	// constrcuter destructer
	ENGINEAPI ULevel();
	ENGINEAPI ~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	// 내가 이제 실행되는 레벨이 되었을때
	void LevelChangeStart();
	// 내가 교체 당했을때
	void LevelChangeEnd();

	UEngineRenderTarget* GetLastRenderTarget()
	{
		return LastRenderTarget.get();
	}

	template<typename Type>
	Type* GetGameMode()
	{
		return dynamic_cast<Type*>(GameMode);
	}


	class AGameMode* GetGameMode()
	{
		return GameMode;
	}

	template<typename Type>
	Type* GetMainPawn()
	{
		return dynamic_cast<Type*>(MainPawn);
	}

	class APawn* GetMainPawn()
	{
		return MainPawn;
	}

	template<typename Type>
	Type* GetHUD()
	{
		return dynamic_cast<Type*>(HUD);
	}


	class AHUD* GetHUD()
	{
		return HUD;
	}



	void Tick(float _DeltaTime);
	void Render(float _DeltaTime);
	void Collision(float _DeltaTime);
	void Release(float _DeltaTime);

	std::shared_ptr<class ACameraActor> GetMainCamera()
	{
		return GetCamera(0);
	}

	template<typename EnumType>
	std::shared_ptr<class ACameraActor> GetCamera(EnumType _Order)
	{
		return GetCamera(static_cast<int>(_Order));
	}

	std::shared_ptr<class ACameraActor> GetCamera(int _Order)
	{
		if (false == Cameras.contains(_Order))
		{
			MSGASSERT("존재하지 않는 카메라를 사용하려고 했습니다.");
		}

		return Cameras[_Order];
	}

	template<typename EnumType>
	std::shared_ptr<class ACameraActor> SpawnCamera(EnumType _Order)
	{
		return SpawnCamera(static_cast<int>(_Order));
	}

	std::shared_ptr<class ACameraActor> SpawnCamera(int _Order);

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor(std::string_view _Name = "")
	{
		// AMonster : public AActor
		// SpawnActor<AMonster>();
		// std::shared_ptr<AMonster>

		static_assert(std::is_base_of_v<AActor, ActorType>, "액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");

		if (false == std::is_base_of_v<AActor, ActorType>)
		{
			MSGASSERT("액터를 상속받지 않은 클래스를 SpawnActor하려고 했습니다.");
			return nullptr;
			// static_assert
		}

		char* ActorMemory = new char[sizeof(ActorType)];


		AActor* ActorPtr = reinterpret_cast<ActorType*>(ActorMemory);
		ActorPtr->World = this;

		ActorType* NewPtr = reinterpret_cast<ActorType*>(ActorMemory);
		// 레벨먼저 세팅하고
		// 플레이스먼트 new 
		std::shared_ptr<ActorType> NewActor(NewPtr = new(ActorMemory) ActorType());

		ActorPtr->SetName(_Name);

		//컴파일러는 그걸 모른다.
		BeginPlayList.push_back(NewActor);

		return NewActor;
	}

	//                           0              100그룹
	ENGINEAPI void ChangeRenderGroup(int _CameraOrder, int _PrevGroupOrder, std::shared_ptr<class URenderer> _Renderer);

	ENGINEAPI void ChangeCollisionProfileName(std::string_view _ProfileName, std::string_view _PrevProfileName, std::shared_ptr<class UCollision> _Collision);

	ENGINEAPI void PushCollisionProfileEvent(std::shared_ptr<class URenderer> _Renderer);

	ENGINEAPI void CreateCollisionProfile(std::string_view _ProfileName);

	ENGINEAPI void LinkCollisionProfile(std::string_view _LeftProfileName, std::string_view _RightProfileName);

	// light를 가지고 있는 LightActor가 Level을 가지고 있지 않기 때문에 위험하지는
	ENGINEAPI void PushLight(std::shared_ptr<class ULight> _Light);

	// #ifdef _DEBUG
		// 에디터에서는 빠른지 느린지를 따지지 않는다.
		// 에디터기능을 만들때는 최적화를 신경안쓰는 경우가 많다.
		// 실제 플레이와는 전혀 관련이 없으니까.
	template<typename ConvertType>
	ENGINEAPI std::list<std::shared_ptr<ConvertType>> GetAllActorListByClass()
	{
		std::list<std::shared_ptr<ConvertType>> List;

		for (std::shared_ptr<class AActor> Actor : AllActorList)
		{
			std::shared_ptr<ConvertType> Convert = std::dynamic_pointer_cast<ConvertType>(Actor);
			if (nullptr == Convert)
			{
				continue;
			}
			List.push_back(Convert);
		}

		return List;
	}

	template<typename ConvertType>
	ENGINEAPI std::vector<std::shared_ptr<ConvertType>> GetAllActorArrayByClass()
	{
		std::vector<std::shared_ptr<ConvertType>> List;

		for (std::shared_ptr<class AActor> Actor : AllActorList)
		{
			std::shared_ptr<ConvertType> Convert = std::dynamic_pointer_cast<ConvertType>(Actor);
			if (nullptr == Convert)
			{
				continue;
			}
			List.push_back(Convert);
		}

		return List;
	}
	// #endif

protected:

private:
	class AHUD* HUD = nullptr;

	class AGameMode* GameMode = nullptr;

	class APawn* MainPawn = nullptr;

	std::list<std::shared_ptr<class AActor>> BeginPlayList;

	std::list<std::shared_ptr<class AActor>> AllActorList;

	// 0번에 mainamera라고 불리는 애를 만든다.
	std::map<int, std::shared_ptr<class ACameraActor>> Cameras;
	// 모든 카메라가 바라본 이미지를 섞은 타겟
	std::shared_ptr<class UEngineRenderTarget> LastRenderTarget;

	// 빛은 order가 필요없습니다. 빛의 최종결과물은 모든 빛의 연산결과의 +
	std::vector<std::shared_ptr<class ULight>> Lights;
	FLightDatas LightDatas;

	// 빌드하기전에 string Hash화 라는 작업을 통해서 다 숫자로 
	// 면접때 하기 좋은 이야기
	std::map<std::string, std::list<std::shared_ptr<class UCollision>>> Collisions;

	// 이벤트가 존재하는 애들만 충돌 체크하려고.
	std::map<std::string, std::list<std::shared_ptr<class UCollision>>> CheckCollisions;

	std::map<std::string, std::list<std::string>> CollisionLinks;



	ENGINEAPI void InitLevel(AGameMode* _GameMode, APawn* _Pawn, AHUD* _HUD);

	FLightDatas& GetLightDatasRef()
	{
		return LightDatas;
	}
};

