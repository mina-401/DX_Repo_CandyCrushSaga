#include "PreCompile.h"
#include "CandyCrushSaga.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/Pawn.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include <EngineCore/HUD.h>
#include <EngineCore/EngineGUI.h>
#include "ContentsEditorGUI.h"

#include "PlayGameMode.h"  
#include "TileMapGameMode.h" 
#include "TitleGameMode.h"
#include "CCSHUD.h"
#include "CandyManager.h"

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


	UEngineCore::CreateLevel<ATitleGameMode, APawn, AHUD>("TitleLevel");
	UEngineCore::CreateLevel<APlayGameMode, ACandyManager, ACCSHUD>("PlayLevel");
	//UEngineCore::CreateLevel<ATileMapGameMode, APawn>("TileMapEditor");
	//UEngineCore::OpenLevel("TileMapEditor");
	UEngineCore::OpenLevel("PlayLevel");

	UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("CCSEditorGUI");
	std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("CCSEditorGUI");
	Window->SetActive(true);
	
}

void UCandyCrushSaga::EngineTick(float _DeltaTime)
{

}

void UCandyCrushSaga::EngineEnd()
{

}