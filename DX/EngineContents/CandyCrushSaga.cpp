#include "PreCompile.h"
#include "CandyCrushSaga.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include "TitleGameMode.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/Pawn.h>

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
	_Data.WindowSize = { 1280, 720 };

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, {".PNG", ".BMP", ".JPG"});
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}

	//UEngineSprite::CreateSpriteToMeta("Title.png", ".sdata");


	// UEngineCore::CreateLevel<APlayGameMode, APawn>("PlayLevel");

	UEngineCore::CreateLevel<ATitleGameMode, APawn>("Titlelevel");
	UEngineCore::OpenLevel("Titlelevel");
	
}

void UCandyCrushSaga::EngineTick(float _DeltaTime)
{

}

void UCandyCrushSaga::EngineEnd()
{

}