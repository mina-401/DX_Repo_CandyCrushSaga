#include "PreCompile.h"
#include "TitleButton.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/ImageWidget.h>
#include <EngineCore/Level.h>
#include <EngineCore/HUD.h>
#include <EngineCore/FontWidget.h>

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
		Button->SetScale3D({ 180,180,1.0f });
	});
	Button->SetDownEvent([this]{
		UEngineCore::OpenLevel("PlayLevel");
		});
	

	TitleText = GetWorld()->GetHUD()->CreateWidget<UFontWidget>(-1).get();
	TitleText->SetFont("BrandonGrotesqueBold", 20.0f, TColor<unsigned char>::BLACK, FW1_CENTER);
	TitleText->SetWorldLocation({ 0,15,-100 });
	//TitleText->SetRelativeScale3D({ 100,100 });
	TitleText->SetHoverEvent([this]{
		TitleText->SetFont("BrandonGrotesqueBold", 100.0f, TColor<unsigned char>::BLACK, FW1_CENTER);
		TitleText->SetText("시작하기");

		});

	TitleText->SetText("시작하기");


}

void ATitleButton::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	Button->SetScale3D({ 150,150,1.0f });

}

