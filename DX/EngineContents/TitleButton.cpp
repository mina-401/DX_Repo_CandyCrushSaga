#include "PreCompile.h"
#include "TitleButton.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

ATitleButton::ATitleButton()
{

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetTexture("StartButton.png");
	//Renderer->SetSprite("MenuIcons.png",0);


	Renderer->SetRelativeScale3D({ 100,100,1.0f });
}

ATitleButton::~ATitleButton()
{
}

void ATitleButton::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleButton::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

