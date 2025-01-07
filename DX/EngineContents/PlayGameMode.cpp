#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/Level.h>
#include "PlayMap.h"


APlayGameMode::APlayGameMode()
{
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);
	PlayDirLoad();
	SpritesInit();
	{
		Map=GetWorld()->SpawnActor<APlayMap>();
	}


}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::PlayDirLoad()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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

}

void APlayGameMode::SpritesInit()
{
	
}

