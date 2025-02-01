#pragma once
#include <EngineCore/GameInstance.h>
#include <EngineCore/Widget.h>
#include "CCSStruct.h"
class MouseController
{
public:
	//int MaxTransCount = 10;
	//int CurTransCount = MaxTransCount;

	bool IsTransEnd = false;

	

};


// Ό³Έν :
class CandyGameInstance : public UGameInstance
{
public:
	// constrcuter destructer
	CandyGameInstance();
	~CandyGameInstance();

	void Init();

	// delete Function
	CandyGameInstance(const CandyGameInstance& _Other) = delete;
	CandyGameInstance(CandyGameInstance&& _Other) noexcept = delete;
	CandyGameInstance& operator=(const CandyGameInstance& _Other) = delete;
	CandyGameInstance& operator=(CandyGameInstance&& _Other) noexcept = delete;
		

	PlayerStatus PlayerStat;
	GameStatus GameStat;

	MouseController CandyMouseCon;

	int Score = 0;
	int Turn = CCSConst::MaxTurn;

	bool IsRestart = false;
	bool IsGameEnd = false;
protected:	

private:

	
};

