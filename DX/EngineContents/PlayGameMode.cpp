#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/Level.h>	
#include <EngineCore/HUD.h>	
#include <EngineCore/EngineCore.h>	
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
#include "CandyGameInstance.h"
#include "CCSHUD.h"
#include <EngineCore/FontWidget.h>
#include <EngineCore/TimeEventComponent.h>
#include "TitleGameMode.h"
#include "ResultHUD.h"

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
	//PlayDirLoad();
	//SpritesInit();
	//SoundInit();
	{
		TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
		Map=GetWorld()->SpawnActor<APlayMap>();
	
	}

}
APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::SoundInit()
{

	UEngineDirectory Dir;
	if (false == Dir.MoveParentToDirectory("ContentsResources"))
	{
		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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

void APlayGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	{
		SoundPlayer = UEngineSound::Play("PlayOST.mp3");
		SoundPlayer.SetVolume(0.5f);
	}

	AHUD* HUD = GetWorld()->GetHUD();
	
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
	GetGameInstance<CandyGameInstance>()->IsGameEnd = false;
	GetGameInstance<CandyGameInstance>()->Init();

}

void APlayGameMode::LevelChangeEnd()
{
	SoundPlayer.Stop();

	GetGameInstance<CandyGameInstance>()->IsGameEnd = false;
}

void APlayGameMode::BeginPlay()
{
	AActor::BeginPlay();
	{
		GetWorld()->CreateCollisionProfile("Candy");
		GetWorld()->CreateCollisionProfile("Mouse");
		GetWorld()->LinkCollisionProfile("Mouse", "Candy");
	}
	{
		CandyMouseObj = GetWorld()->SpawnActor<AMouse>();
		
	}
	{

		CandyManager = dynamic_cast<ACandyManager*>(GetWorld()->GetMainPawn());

		//TimeEventComponent->AddEndEvent(1.0f, [this]()
		//{
		ChangeState(EGameModeState::GameStart);

		StartGame(5, 5);

		ChangeState(EGameModeState::InGame);
		//});
	}


}

void APlayGameMode::StartGame(int x, int y)
{
	CandyManager->CreateStage(x, y);
	CandyManager->DeleteIndex(0, 0);

	CandyManager->CreateStageBackTile(); // 캔디 뒤에 배경 만들기
	CandyManager->CandyCreate(); // 진짜 캔디 만들기

	CandyManager->CandyFindConsec();
	CandyManager->CandyDestroyCheck();
}
void APlayGameMode::GameEndStart()
{
	//결과 확인하는 UI 


}
void APlayGameMode::GameEnd(float _DeltaTime)
{
	// 점수판에 점수
	AHUD* Result = GetWorld()->SpawnActor<AResultHUD>().get();
//UEngineCore::ResetLevel<ATitleGameMode, ACandyManager, AHUD>("TitleLevel");
//UEngineCore::OpenLevel("TitleLevel");
}
void APlayGameMode::InGame(float _DeltaTime)
{
	bool IsGameEnd = GetGameInstance<CandyGameInstance>()->IsGameEnd;


	if (true == IsGameEnd)
	{

		ChangeState(EGameModeState::GameEnd);
		return;
	}

	bool IsRestart = GetGameInstance<CandyGameInstance>()->IsRestart;
	if (true == IsRestart)
	{
		GetGameInstance<CandyGameInstance>()->IsRestart = false;
		CandyManager->ResetCandyBoard();

	}
}
void APlayGameMode::InGameStart()
{
	//결과 확인하는 UI 
}
void APlayGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	switch (GameModeState)
	{
	case EGameModeState::GameStart:
		break;
	case EGameModeState::InGame:
		InGame(_DeltaTime);
		break;
	case EGameModeState::Paused:
		break;
	case EGameModeState::GameEnd:
		GameEnd(_DeltaTime);
		break;
	default:
		break;
	}
	//if (UEngineInput::IsPress(VK_F1)) IsGameEnd = true;

	


	
	
}

void APlayGameMode::SpritesInit()
{
	//

}

