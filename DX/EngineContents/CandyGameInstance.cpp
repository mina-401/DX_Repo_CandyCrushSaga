#include "PreCompile.h"
#include "CandyGameInstance.h"

CandyGameInstance::CandyGameInstance()
{

	int MaxTurn = 3;
	int MaxScore = 20000;
	int Score = 0;
	int Turn = MaxTurn;

	PlayerStat.Score = Score;
	PlayerStat.Turn = Turn;
}

CandyGameInstance::~CandyGameInstance()
{
}

