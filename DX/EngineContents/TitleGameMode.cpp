#include "PreCompile.h"
#include "TitleGameMode.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/Level.h>
#include "TitleMap.h"
#include <EnginePlatform/EngineInput.h>


//class TestWindow : public UEngineGUIWindow
//{
//public:
//	void OnGUI() override
//	{
//		ImGui::Button("WindowButton");
//		ImGui::SameLine(); // 한간 띄기
//		ImGui::Text("test");
//
//	}
//};

ATitleGameMode::ATitleGameMode()
{
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);
	TitleDirLoad();
	SpritesInit();
	{
		Map = GetWorld()->SpawnActor<ATitleMap>();

	}
	{
		//Button = GetWorld()->SpawnActor<ATitleButton>();
	}

	//UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
}

void ATitleGameMode::TitleDirLoad()
{

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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

}

ATitleGameMode::~ATitleGameMode()
{

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsPress('P'))
	{
		UEngineCore::OpenLevel("PlayLevel");
		//AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}

}

void ATitleGameMode::SpritesInit()
{
	{
		//UEngineSprite::CreateSpriteToMeta("TitleMap.png", ".sdata");
		//UEngineSprite::CreateSpriteToMeta("MenuIcons.png", ".sdata");

	}
}
