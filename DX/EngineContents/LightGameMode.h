#pragma once
#include <EngineCore/GameMode.h>
#include <atomic>
#include <EnginePlatform/EngineThread.h>
#include <EnginePlatform/EngineSound.h>

// 설명 :
class ALightGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ALightGameMode();
	~ALightGameMode();

	// delete Function
	ALightGameMode(const ALightGameMode& _Other) = delete;
	ALightGameMode(ALightGameMode&& _Other) noexcept = delete;
	ALightGameMode& operator=(const ALightGameMode& _Other) = delete;
	ALightGameMode& operator=(ALightGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	void BeginPlay() override;


protected:
	void LevelChangeStart() override;

private:
	// 이렇게 들고 있으면 나는 죽였다고 생각하는데. 살아있을수 있다.
	// ATitleLogo* Logo; => 뎅글링 포인터 부활.
	std::shared_ptr<class ATitleLogo> Logo;

	std::atomic<int> LoadingCount = 0;

	std::atomic<bool> ThreadLoadingInit = false;

	std::atomic<bool> ThreadLoadingEnd = false;
	// std::atomic<bool> TextureLoad = false;
	// std::atomic<bool> SpriteLoad = false;

	USoundPlayer SoundPlayer;
	std::shared_ptr<class AMeshActor> NewMonster;
	// UEngineThread Thread;
};

//
//// 삼각형 하나
//struct FNaviData
//{
//	int Index;
//
//	FVector Arr[3];
//
//	int ArrIndex[3];
//
//	// std::vector<FNaviData*> LinkArr;
//	// std::vector<int> Arr;
//
//	void Intersect(AActor* Player, float& Dis)
//	{
//		// DirectX::TriangleTests::Intersects()
//	}
//};
//
//class ANaviMeshManager : AActor
//{
//	std::vector<FNaviData> Data;
//
//	void LoadModel(std::string_view _Path)
//	{
//		std::vector<FVector> AllVector;
//	}
//
//	// 연결을 만들어주면 됩니다.
//	void LinkProgress();
//};
//
//class Player
//{
//	FNaviData* CurNaviMesh;
//};