#pragma once
#include<EngineCore/GameMode.h>
#include <random>

class Random
{

};
class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	 APlayGameMode();
	 ~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

protected:

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);
private:
	std::shared_ptr<class APlayMap> Map;
	std::vector<std::vector<std::shared_ptr<class ACandy>>> Candys;

	std::shared_ptr<class ACandy> SpawnCandy(FVector& _CurPos, int _CandyIndex);
	void PlayDirLoad();
	void SpritesInit();


	int CandyRow = 5;
	int CandyCol = 5;

	
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

