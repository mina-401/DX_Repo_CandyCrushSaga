#pragma once
#include <EngineCore/GameMode.h>
#include <atomic>
#include <EnginePlatform/EngineThread.h>
#include <EnginePlatform/EngineSound.h>

// ���� :
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
	// �̷��� ��� ������ ���� �׿��ٰ� �����ϴµ�. ��������� �ִ�.
	// ATitleLogo* Logo; => ���۸� ������ ��Ȱ.
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
//// �ﰢ�� �ϳ�
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
//	// ������ ������ָ� �˴ϴ�.
//	void LinkProgress();
//};
//
//class Player
//{
//	FNaviData* CurNaviMesh;
//};