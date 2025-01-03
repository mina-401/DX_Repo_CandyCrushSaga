#include "PreCompile.h"
#include "TitleGameMode.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/Level.h>
#include "TitleMap.h"
#include "TitleButton.h"

//class TestWindow : public UEngineGUIWindow
//{
//public:
//	void OnGUI() override
//	{
//		ImGui::Button("WindowButton");
//		ImGui::SameLine(); // �Ѱ� ���
//		ImGui::Text("test");
//
//	}
//};

ATitleGameMode::ATitleGameMode()
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
		UEngineSprite::CreateSpriteToMeta("TitleMap.png", ".sdata");

	}
	{
		Map = GetWorld()->SpawnActor<ATitleMap>();

	}
	{
		//Button = GetWorld()->SpawnActor<ATitleButton>();
	}
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({0.0f, 0.0f, -1000.0f, 1.0f});

	//UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
}

ATitleGameMode::~ATitleGameMode()
{

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);



}