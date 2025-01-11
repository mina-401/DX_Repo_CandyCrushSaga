#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/Level.h>	
#include <EngineCore/EngineCamera.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/SpriteRenderer.h>
#include "PlayMap.h"

#include "Candy.h"
#include "ContentsEditorGUI.h"
#include "CandyManager.h"
#include "Mouse.h"
#include <EnginePlatform/EngineInput.h>

class DebugWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{

		if (true == ImGui::Button("FreeCameraOn")) 
		{
 			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine(); 
		ImGui::Text("Free Camera");

	}
};
APlayGameMode::APlayGameMode()
{
	{
		std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
		Camera->GetCameraComponent()->SetZSort(0, true);
	}
	PlayDirLoad();
	SpritesInit();
	{
		Map=GetWorld()->SpawnActor<APlayMap>();
	}

}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	{
		std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("CCSEditorGUI");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("CCSEditorGUI");
		}

		Window->SetActive(true);
	}

	{
		std::shared_ptr<DebugWindow> Window = UEngineGUI::FindGUIWindow<DebugWindow>("DebugWindow");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<DebugWindow>("DebugWindow");
		}

		Window->SetActive(true);
	}
}

void APlayGameMode::BeginPlay()
{
	AActor::BeginPlay();
	{
		GetWorld()->CreateCollisionProfile("Candy");
		GetWorld()->CreateCollisionProfile("Mouse");
		//GetWorld()->LinkCollisionProfile("Candy", "Mouse");
		GetWorld()->LinkCollisionProfile("Mouse", "Candy");
	}
	{
		CandyMouseObj = GetWorld()->SpawnActor<AMouse>();
		
	}
	{
		CandyManager = GetWorld()->SpawnActor<ACandyManager>();
		CandyManager->CreateStage(3, 3);
		//CandyManager->DeleteIndex(0, 0);
		CandyManager->CandyCreate();

	}


}

void APlayGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	
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

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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

}

void APlayGameMode::SpritesInit()
{
	//UEngineSprite::CreateSpriteToMeta("Candys.png", ".sdata");

}

