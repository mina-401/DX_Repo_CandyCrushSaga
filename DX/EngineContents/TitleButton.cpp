#include "PreCompile.h"
#include "TitleButton.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/ImageWidget.h>
#include <EngineCore/Level.h>
#include <EngineCore/HUD.h>
#include <EngineCore/FontWidget.h>
#include <EnginePlatform/EngineSound.h>
#include "PlayGameMode.h"
#include "CCSHUD.h"
#include "CandyManager.h"

ATitleButton::ATitleButton()
{

}

ATitleButton::~ATitleButton()
{
}

void ATitleButton::BeginPlay()
{
	AActor::BeginPlay();
	Button = GetWorld()->GetHUD()->CreateWidget<UImageWidget>(-1);
	Button->SetTexture("StartButton.png");
	Button->SetScale3D({ 150,150,1.0f });
	Button->SetWorldLocation({ 0,0,-100 });
	Button->SetHoverEvent([this] {
		Button->SetScale3D({ 160,160,1.0f });
	});
	Button->SetDownEvent([this] {

		USoundPlayer SoundPlayer;
		SoundPlayer.SetVolume(0.5f);
		SoundPlayer = UEngineSound::Play("button_press.wav");

		UEngineCore::ResetLevel<APlayGameMode, ACandyManager, ACCSHUD>("PlayLevel");
		UEngineCore::OpenLevel("PlayLevel");
	});

	TitleText = GetWorld()->GetHUD()->CreateWidget<UFontWidget>(-1).get();
	TitleText->SetupAttachment(Button.get());


	TitleText->SetFont("BrandonGrotesqueBold", 20.0f, TColor<unsigned char>::BLACK, FW1_CENTER);
	//TitleText->SetRelativeLocation({ 0,0.15,0 });
	//TitleText->SetRelativeScale3D({ 100,100 });
	TitleText->SetHoverEvent([this] {
		TitleText->SetRelativeLocation({ 0.0f,0.12f,0.0f });
		TitleText->SetFont("BrandonGrotesqueBold", 25.0f, TColor<unsigned char>::BLACK, FW1_CENTER);
		TitleText->SetText("시작하기");

	});
	TitleText->SetUpEvent([this] {

		
	});
	TitleText->SetText("시작하기");


}

void ATitleButton::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	Button->SetScale3D({ 150,150,1.0f });
	TitleText->SetRelativeLocation({ 0.0f,0.1f,0.0f });
	TitleText->SetFont("BrandonGrotesqueBold", 20.0f, TColor<unsigned char>::BLACK, FW1_CENTER);
}

