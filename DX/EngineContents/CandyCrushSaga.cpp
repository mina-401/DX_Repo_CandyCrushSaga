#include "PreCompile.h"
#include "CandyCrushSaga.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include "TitleGameMode.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/Pawn.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>

#include "PlayGameMode.h"  

// #define은 그냥 무조건 복붙
CreateContentsCoreDefine(UCandyCrushSaga);

UCandyCrushSaga::UCandyCrushSaga()
{
}

UCandyCrushSaga::~UCandyCrushSaga()
{
}


void UCandyCrushSaga::EngineStart(UEngineInitData& _Data)
{
	// mainwindow는 아무나 건들면 안된다.
	// 넌 컨텐츠잖아 엔진이 관리하는 윈도우라는게 존재하는지도 몰라야한다.

	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 720, 480 };

	

	MyGSetting();

	// UEngineCore::CreateLevel<APlayGameMode, APawn>("PlayLevel");

	UEngineCore::CreateLevel<ATitleGameMode, APawn>("TitleLevel");
	UEngineCore::CreateLevel<APlayGameMode, APawn>("PlayLevel");
	UEngineCore::OpenLevel("PlayLevel");
	
}

void UCandyCrushSaga::EngineTick(float _DeltaTime)
{

}

void UCandyCrushSaga::EngineEnd()
{

}