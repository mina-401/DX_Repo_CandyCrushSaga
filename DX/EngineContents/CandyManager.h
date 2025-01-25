#pragma once
#include <EngineCore/Pawn.h>
#include <EngineBase/EngineRandom.h>
//#include "Queue.h"
#include <queue>
#include "CCSEnums.h"
#include <EngineCore/ImageWidget.h>

class StageCandyData
{
public:
	bool IsActive = true;
	FVector Pos = { -1,-1,-100 };
	//FVector TargetPos = { -1,-1 };

	bool operator==(std::nullptr_t) const
	{
		return !IsActive; // IsActive가 false일 때 nullptr로 간주
	}

	bool operator==(const StageCandyData& other) const
	{
		return (IsActive == other.IsActive) && (Pos == other.Pos);
	}


	// operator!= 오버로드
	bool operator!=(const StageCandyData& other) const
	{
		return !(*this == other); 
	}
};

class DropData
{
public:
	class ACandy* Candy;
	FVector StartPos;
	FVector EndPos;
};

class StageMapData
{
public:
	int Combo;
	int Bonus;

	
};
class CandyBlock
{
	int Count = 0;
};

enum class ECandyManagerState
{
	Select,
	Move,
	Destroy,
	NewCandyDrop,
	Update,
	Disable,
};

class ACandyManager : public APawn
{
public:
	// constrcuter destructer
	 ACandyManager();
	 ~ACandyManager();


	// delete Function
	ACandyManager(const ACandyManager& _Other) = delete;
	ACandyManager(ACandyManager&& _Other) noexcept = delete;
	ACandyManager& operator=(const ACandyManager& _Other) = delete;
	ACandyManager& operator=(ACandyManager&& _Other) noexcept = delete;

	 void CreateStageBackTile();
	void CreateStage(int X, int Y);
	void DeleteIndex(int X, int Y);
	void CandyCreate();
	bool IsCandyDestroy();
	void CandyFindConsec();
	void CandyCascadeExplosion();
	void CandyDestroyCheck();
	void CandyChange(class  ACandy* SelectCandy, class ACandy* CurCandy);
	void CandyClear();

	void ClearCandys();

	void ResetCandyBoard();

	//void CandyDropAt(ACandy* candy, FVector pos);
	void CandyDestroy();
	
	ACandy* NewCandyCreate(int row, int col);

	ACandy* NewCandyCreate(int row, int col, FVector Pos);

	void NewCandyDropStart();
	void NewCandyDrop(float _Delta);

	void PushDestroyCandy(int _row, int _col,ESpriteType SpriteType);

	void UpdateStart();
	void Update(float _DeltaTime);
	void DisableStart();
	void Disable(float _DeltaTime);
	void CandyDestroyStart();
	


	void RowCheck(int X, int Y);
	void ColCheck(int X, int Y);

	 std::vector<std::vector<class ACandy*>> Candys;
	 int CandyRow = 0; //Y
	 int CandyCol = 0; //X
	 int Combo = 0;

	 StageMapData StageData;
	 FVector CandyScale = { 50,50 };

	 ECandyManagerState GetCandyState()
	 {
		 return CandyState;
	 }

	 void ChangeCandyState(ECandyManagerState _CandyState);

	 FVector IndexToWorldPos(FIntPoint _Index);

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	ECandyManagerState CandyState = ECandyManagerState::Select;
	std::vector<std::vector<StageCandyData>> Data;
	std::list<ACandy*> DestroyCandy;
	std::vector<FIntPoint> Empty;

	std::vector<DropData> DropCandy;
	std::vector<ACandy*> NewCandys;
	std::vector<ACandy*> DestroySpecialCandy;

	
	FVector LeftBottom = { -100,-200 };
	//FVector LeftTop = { -50,-100 };

	float DropSpeed = 50.0f;
	bool IsDropCandy = false;
	bool DestroyEnd = false;
	bool IsCandyDrop = false;

	const int Three = 3;
	const int Four = 4;
	const int Five = 5;

	
	UEngineRandom Random;

	UWidget* PlayerStatsWidget;

//밑은 랜덤함수

};

