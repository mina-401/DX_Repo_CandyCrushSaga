#include "PreCompile.h"
#include "CandyGameInstance.h"
#include "CCSConst.h"

CandyGameInstance::CandyGameInstance()
{

	
	Init();

}

CandyGameInstance::~CandyGameInstance()
{
}

void CandyGameInstance::Init()
{

	 IsRestart = false;
	 IsGameEnd = false;
	 Score = 0;
	 Turn = CCSConst::MaxTurn;

	 IsRestart = false;
	 IsGameEnd = false;

	CandyMouseCon.IsTransEnd = false;
	GameStat.MaxScore = CCSConst::MaxScore;
	PlayerStat.Score = 0;
	PlayerStat.Turn = CCSConst::MaxTurn;



}
