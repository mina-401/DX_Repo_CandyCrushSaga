#pragma once
#include <EngineCore/Pawn.h>
#include <random>
//#include "Queue.h"
#include <queue>

class StageCandyData
{
public:
	bool IsActive = true;
	FVector Pos;

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


class StageCombo
{
public:
	int Combo = 0;


};

enum class ECandyManagerState
{
	Select,
	Move,
	Destroy,
	NewCandyDrop,
	Update,
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

	void CreateStage(int X, int Y);
	void DeleteIndex(int X, int Y);
	void CandyCreate();
	bool IsCandyDestroy();
	void CandyFindConsec();
	void CandyChange(class  ACandy* SelectCandy, class ACandy* CurCandy);
	void CandyClear();
	void NewCandyDrop();
	void CandyPlaceAt(int EmptyRow,int Col);
	void CandyDropAt(ACandy* candy, FVector pos);
	void CandyDestroy();
	ACandy* NewCandyCreate();

	void NewCandyDropStart();
	void UpdateStart();

	void CandyDestroyStart();
	


	void RowCheck(int X, int Y);
	void ColCheck(int X, int Y);

	 std::vector<std::vector<class ACandy*>> Candys;
	 int CandyRow = 0;
	 int CandyCol = 0;
	 int Combo = 0;

	 StageCombo CandyCombo;
	 FVector CandyScale = { 50,50 };

	 ECandyManagerState GetCandyState()
	 {
		 return CandyState;
	 }

	 void ChangeCandyState(ECandyManagerState _CandyState);

protected:
	void BeginPlay() override;

	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	ECandyManagerState CandyState = ECandyManagerState::Select;
	std::vector<std::vector<StageCandyData>> Data;
	std::list<ACandy*> DestroyCandy;
	std::vector<FIntPoint> Empty;
	
	



//밑은 랜덤함수

private:
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));

public:


	void SetSeed(__int64 _Seed)
	{
		MtGen = std::mt19937_64(_Seed);
	}
	int RandomInt(int _Min, int _Max)
	{
		if (_Max < _Min)
		{
			int SwapValue = _Min;
			_Min = _Max;
			_Max = SwapValue;
		}

		// _Min ~ _Max 랜덤값 뽑아줘
		std::uniform_int_distribution<int> RandomCreate(_Min, _Max);

		// MtGen 제네레이터 써서
		// std::mt19937_64 메르헨 트위스터 알고리즘 써서 만들어줘.
		return RandomCreate.operator()(MtGen);
	}

};

