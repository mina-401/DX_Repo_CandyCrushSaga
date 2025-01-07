#include "PreCompile.h"
#include "HUD.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

AHUD::AHUD()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	RootComponent->SetRelativeScale3D({ 1, 1, 0.0f });

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetRelativeScale3D({ 259,150,0.0f });
	Renderer->SetWorldLocation({ -250,100,-1 });

	Child_ScoreTextBox = CreateDefaultSubObject<USpriteRenderer>();
	Child_ScoreTextBox->SetupAttachment(RootComponent);
	Child_ScoreTextBox->SetRelativeScale3D({ 210,200,0.0f });
	Child_ScoreTextBox->SetWorldLocation({ -270,30,-2 });

	Child_ScoreBar = CreateDefaultSubObject<USpriteRenderer>();
	Child_ScoreBar->SetupAttachment(RootComponent);
	Child_ScoreBar->SetRelativeScale3D({ 68,150,0.0f });
	Child_ScoreBar->SetWorldLocation({ -190,5,-3 });

	Child_Score = CreateDefaultSubObject<USpriteRenderer>();
	Child_Score->SetupAttachment(RootComponent);
	Child_Score->SetRelativeScale3D({ 30,100,0.0f });
	Child_Score->SetWorldLocation({ -191,-54,-4 });
	

	Renderer->SetTexture("HUD_1.png");
	Child_ScoreTextBox->SetTexture("HUD_2.png");
	Child_ScoreBar->SetTexture("HUD_3.png");
	Child_Score->SetTexture("HUD_4.png");

	
	

	



}

AHUD::~AHUD()
{
}

void AHUD::BeginPlay()
{
	AActor::BeginPlay();
}

void AHUD::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}