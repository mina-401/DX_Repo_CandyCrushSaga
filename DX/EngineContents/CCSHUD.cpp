#include "PreCompile.h"
#include "CCSHUD.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/ImageWidget.h>

ACCSHUD::ACCSHUD()
{
	/*std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	RootComponent->SetRelativeScale3D({ 1, 1, 0.0f });

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetRelativeScale3D({ 259,150,0.0f });
	Renderer->SetWorldLocation({ -250,100,-1 });

	Child_ScoreTextBox = CreateDefaultSubObject<USpriteRenderer>();
	Child_ScoreTextBox->SetupAttachment(RootComponent);
	Child_ScoreTextBox->SetRelativeScale3D({ 230,200,0.0f });
	Child_ScoreTextBox->SetWorldLocation({ -270,30,-2 });

	Child_ScoreBar = CreateDefaultSubObject<USpriteRenderer>();
	Child_ScoreBar->SetupAttachment(RootComponent);
	Child_ScoreBar->SetRelativeScale3D({ 78,150,0.0f });
	Child_ScoreBar->SetWorldLocation({ -190,5,-3 });

	Child_Score = CreateDefaultSubObject<USpriteRenderer>();
	Child_Score->SetupAttachment(RootComponent);
	Child_Score->SetRelativeScale3D({ 33,100,0.0f });
	Child_Score->SetWorldLocation({ -191,-54,-4 });
	

	Renderer->SetTexture("HUD_1.png");
	Child_ScoreTextBox->SetTexture("HUD_2.png");
	Child_ScoreBar->SetTexture("HUD_3.png");
	Child_Score->SetTexture("HUD_4.png");*/

	
	

	



}

ACCSHUD::~ACCSHUD()
{
}

void ACCSHUD::BeginPlay()
{
	AActor::BeginPlay();


	{
		FrameWidget = CreateWidget<UImageWidget>(-1).get();

		FrameWidget->SetScale3D({ 100, 100, 1 });
		FrameWidget->SetWorldLocation({ -250,100});
		FrameWidget->SetRelativeScale3D({ 259,150,0.0f });
		FrameWidget->SetTexture("HUD_1.png");
		FrameWidget->SetDownEvent([]()
		{
			//UEngineDebug::OutPutString("Click~~~~~~~~~");
		});
	}
	{
		ScoreTextBox = CreateWidget<UImageWidget>(-1).get();

		ScoreTextBox->SetScale3D({ 100, 100, 1 });
		ScoreTextBox->SetScale3D({ 100, 100, 1 });
		ScoreTextBox->SetWorldLocation({ -270,30 });
		ScoreTextBox->SetRelativeScale3D({ 230,200,0.0f });
		ScoreTextBox->SetTexture("HUD_2.png");
		ScoreTextBox->SetDownEvent([]()
		{
			//UEngineDebug::OutPutString("Click~~~~~~~~~");
		});
	}
	{
		 ScoreBar = CreateWidget<UImageWidget>(-1).get();

		ScoreBar->SetScale3D({ 100, 100, 1 });
		ScoreBar->SetWorldLocation({ -190,5 });
		ScoreBar->SetRelativeScale3D({ 78,150,0.0f });
		ScoreBar->SetTexture("HUD_3.png");
		ScoreBar->SetDownEvent([]()
		{
			//UEngineDebug::OutPutString("Click~~~~~~~~~");
		});
	}
	{
		Score = CreateWidget<UImageWidget>(-1).get();

		Score->SetScale3D({ 100, 100, 1 });
		Score->SetWorldLocation({ -191,-54 });
		Score->SetRelativeScale3D({ 33,100,0.0f });
		Score->SetTexture("HUD_4.png");
		Score->SetDownEvent([]()
		{
			//UEngineDebug::OutPutString("Click~~~~~~~~~");
		});
	}



}

void ACCSHUD::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}