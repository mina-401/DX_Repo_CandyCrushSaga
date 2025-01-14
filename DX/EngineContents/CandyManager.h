#pragma once
#include <EngineCore/Actor.h>
#include <random>

class StageCandyData
{
public:
	bool IsActive = true;
};

class CandyCombo
{
public:
	
};

class StageCombo
{
public:

};

class ACandyManager : public AActor
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
	 void CandyCreate(); // 진짜 캔디 만들기
	void CandyBFS();
	void ShowOff();
	void ShowON();


	 std::vector<std::vector<class ACandy*>> Candys;
	 std::vector<std::vector<bool>> Visited;
	 int CandyRow = 5;
	 int CandyCol = 5;
	 FVector CandyScale = { 50,50 };
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	 std::vector<std::vector<StageCandyData>> Data;
	 int ComboCount = 0;












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

