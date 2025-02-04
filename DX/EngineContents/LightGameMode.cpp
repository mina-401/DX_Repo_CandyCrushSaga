#include "PreCompile.h"
#include "LightGameMode.h"
//#include "TitleLogo.h"
//#include "Monster.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include "MeshActor.h"
#include <EngineCore/EngineCore.h>
#include "TitleGameMode.h"
#include "TileMapGameMode.h"
//#include "TitleHUD.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/LightActor.h>
#include <EngineCore/ImageWidget.h>
#include <EngineCore/TimeEventComponent.h>

ALightGameMode::ALightGameMode()
{
	CreateDefaultSubObject<UTimeEventComponent>();

	// 레벨마다 해주셔야 합니다.
	// 이걸 UI공유할건지 
	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Player");
	// 충돌체크 해야한다.
	GetWorld()->LinkCollisionProfile("Player", "Monster");



	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	{
		std::shared_ptr<ALightActor> Light = GetWorld()->SpawnActor<ALightActor>();
	}

	{
		//std::shared_ptr<ALightActor> Light = GetWorld()->SpawnActor<ALightActor>();
		//Light->SetActorRotation({ 0.0f, 90.0f, 0.0f });
	}





	{
		NewMonster = GetWorld()->SpawnActor<AMeshActor>();
		NewMonster->SetActorRelativeScale3D({ 100.0f, 100.0f, 100.0f, 1.0f });
		NewMonster->SetActorLocation({ 0.0f, 0.0f, 0.0f });
	}

	{
		NewMonster = GetWorld()->SpawnActor<AMeshActor>();
		NewMonster->SetActorRelativeScale3D({ 100.0f, 100.0f, 100.0f, 1.0f });
		NewMonster->SetActorLocation({ 0.0f, 0.0f, -200.0f });
	}

	{
		NewMonster = GetWorld()->SpawnActor<AMeshActor>();
		NewMonster->SetActorRelativeScale3D({ 100.0f, 100.0f, 100.0f, 1.0f });
		NewMonster->SetActorLocation({ 200.0f, 0.0f, -200.0f });
	}

	{
		NewMonster = GetWorld()->SpawnActor<AMeshActor>();
		NewMonster->SetActorRelativeScale3D({ 100.0f, 100.0f, 100.0f, 1.0f });
		NewMonster->SetActorLocation({ -200.0f, 0.0f, -200.0f });
	}

	{
		NewMonster = GetWorld()->SpawnActor<AMeshActor>();
		NewMonster->SetActorRelativeScale3D({ 100.0f, 100.0f, 100.0f, 1.0f });
		NewMonster->SetActorLocation({ -200.0f, 0.0f, 200.0f });
	}



}

void ALightGameMode::BeginPlay()
{
	AGameMode::BeginPlay();


	//{
	//	std::shared_ptr<UImageWidget> Wi = GetWorld()->GetHUD()->CreateWidget<UImageWidget>(1000);

	//	Wi->SetWorldLocation({ 300, 0.0f, 0.0f });
	//	Wi->SetScale3D({ 500, 500, 1.0f });
	//}

	//{
	//	std::shared_ptr<UImageWidget> Wi = GetWorld()->GetHUD()->CreateWidget<UImageWidget>(1000);

	//	Wi->SetScale3D({ 500, 500, 1.0f });
	//	Wi->ColorData.MulColor = { 0.0f, 0.0f, 0.0f, -1.0f };
	//}
}

ALightGameMode::~ALightGameMode()
{
	//SoundPlayer.Stop();
}

void ALightGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	if (0 != UEngineWindow::GetWheelDir())
	{
		UEngineDebug::OutPutString(std::to_string(UEngineWindow::GetWheelDir()));

		int a = 0;
	}

	if (UEngineInput::IsDown('A'))
	{
		// SoundPlayer.Stop();
	}
	if (UEngineInput::IsDown(VK_F4))
	{
		//UEngineCore::ResetLevel<ALightGameMode, APawn, AHUD>("LightLevel");
	}



	if (true == UEngineCore::GetMainWindow().IsMouseScreenOut())
	{
		int a = 0;
	}
}

void ALightGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	// SoundPlayer = UEngineSound::Play("Grand_Prix.mp3");
}