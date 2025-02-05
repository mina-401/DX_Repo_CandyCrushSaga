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
#include "CandyGameInstance.h"

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

	
	GEngine->CreateGameInstance<CandyGameInstance>();
	CandyGSetting();

	{
		DirLoad();
		SoundInit();
	}

	UEngineCore::CreateLevel<ATitleGameMode, APawn, AHUD>("TitleLevel");
	UEngineCore::CreateLevel<APlayGameMode, ACandyManager, ACCSHUD>("PlayLevel");

	UEngineCore::OpenLevel("TitleLevel");
	
}
void UCandyCrushSaga::SoundInit()
{


		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Sounds");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".wav", ".mp3" });

		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineSound::Load(FilePath);
		}



}
void UCandyCrushSaga::DirLoad()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image//Title");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image\\Play\\HUD");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
				return;
			}
			Dir.Append("Image\\Play\\BG");

			std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
			for (size_t i = 0; i < ImageFiles.size(); i++)
			{
				std::string FilePath = ImageFiles[i].GetPathToString();
				UEngineTexture::Load(FilePath);
			}
		}

		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
				return;
			}
			Dir.Append("Image//Play//Candy");

			std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
			for (size_t i = 0; i < ImageFiles.size(); i++)
			{
				std::string FilePath = ImageFiles[i].GetPathToString();
				UEngineTexture::Load(FilePath);
			}
			UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		}
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
				return;
			}
			Dir.Append("Image//Play//Effect");

			std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
			for (size_t i = 0; i < ImageFiles.size(); i++)
			{
				std::string FilePath = ImageFiles[i].GetPathToString();
				UEngineTexture::Load(FilePath);
			}
			UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		}
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
				return;
			}
			Dir.Append("Image//Play//Message");

			std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
			for (size_t i = 0; i < ImageFiles.size(); i++)
			{
				std::string FilePath = ImageFiles[i].GetPathToString();
				UEngineTexture::Load(FilePath);
			}
			UEngineSprite::CreateSpriteToMeta("Message.png", ".sdata");
			//UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
		}

}

void UCandyCrushSaga::EngineTick(float _DeltaTime)
{

}

void UCandyCrushSaga::EngineEnd()
{

}