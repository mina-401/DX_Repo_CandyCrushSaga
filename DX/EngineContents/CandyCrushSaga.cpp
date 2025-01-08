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

// #define�� �׳� ������ ����
CreateContentsCoreDefine(UCandyCrushSaga);

UCandyCrushSaga::UCandyCrushSaga()
{
}

UCandyCrushSaga::~UCandyCrushSaga()
{
}


void UCandyCrushSaga::EngineStart(UEngineInitData& _Data)
{
	// mainwindow�� �ƹ��� �ǵ�� �ȵȴ�.
	// �� �������ݾ� ������ �����ϴ� �������°� �����ϴ����� ������Ѵ�.

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