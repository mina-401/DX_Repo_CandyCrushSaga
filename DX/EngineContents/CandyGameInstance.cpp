#include "PreCompile.h"
#include "CandyGameInstance.h"
#include "CCSConst.h"

CandyGameInstance::CandyGameInstance()
{

	
	int Score = 0;
	int Turn = CCSConst::MaxTurn;
	int MaxTurn = CCSConst::MaxScore;

	PlayerStat.Score = Score;
	PlayerStat.Turn = Turn;
}

CandyGameInstance::~CandyGameInstance()
{
}

