#include "PreCompile.h"
#include "CCSHUD.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/ImageWidget.h>
#include "CandyGameInstance.h"
#include <EngineCore/FontRenderer.h>
#include <EngineCore/FontWidget.h>

ACCSHUD::ACCSHUD()
{


}

ACCSHUD::~ACCSHUD()
{
}

void ACCSHUD::BeginPlay()
{
	AActor::BeginPlay();

	/*std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Score = CreateDefaultSubObject<USpriteRenderer>().get();
	Score->SetupAttachment(RootComponent);
	Score->SetPivotValue({ 0.0f,0.5f });
	Score->SetScale3D({ 500,500,1 });
	Score->SetWorldLocation({ 0,0,-500 });
	Score->SetAutoScale(false);*/
	//Score->SetupAttachment(RootCompoenent);

	{
		Score = CreateWidget<UImageWidget>(-1).get();
		Score->SetAutoScale(false);
		Score->SetWorldLocation({ -191,-57 });
		Score->SetScale3D({ 33,2000.0f,0.0f });
		Score->SetTexture("HUD_4.png");


		FrameWidget = CreateWidget<UImageWidget>(-1).get();

		FrameWidget->SetScale3D({ 100, 100, 1 });
		FrameWidget->SetWorldLocation({ -250,100 });
		FrameWidget->SetRelativeScale3D({ 259,150,0.0f });
		FrameWidget->SetTexture("HUD_1.png");


		ScoreTextBox = CreateWidget<UImageWidget>(-1).get();

		ScoreTextBox->SetScale3D({ 100, 100, 1 });
		ScoreTextBox->SetScale3D({ 100, 100, 1 });
		ScoreTextBox->SetWorldLocation({ -270,30 });
		ScoreTextBox->SetRelativeScale3D({ 230,200,0.0f });
		ScoreTextBox->SetTexture("HUD_2.png");


		ScoreBar = CreateWidget<UImageWidget>(-1).get();

		ScoreBar->SetScale3D({ 100, 100, 1 });
		ScoreBar->SetWorldLocation({ -190,5 });
		ScoreBar->SetRelativeScale3D({ 78,150,0.0f });
		ScoreBar->SetTexture("HUD_3.png");

		
	}


	{

		TransText = CreateWidget<UFontWidget>(-1).get();
		TransText->SetFont("BrandonGrotesqueBold", 20.0f, TColor<unsigned char>::BLACK, FW1_LEFT);
		//TransText->SetFont("BrandonGrotesque-Bold", 20.0f, TColor<unsigned char>::BLACK, FW1_LEFT);
		TransText->SetWorldLocation({ -310,120 });

		TransText->SetText("남은 턴수: " + (std::to_string(GetGameInstance<CandyGameInstance>()->PlayerStat.Turn)));

		ScoreText = CreateWidget<UFontWidget>(-1).get();
		ScoreText->SetFont("BrandonGrotesqueBold", 20.0f, TColor<unsigned char>::BLACK, FW1_LEFT);
		ScoreText->SetWorldLocation({ -310,45 });

		ScoreText->SetText("점수: " + (std::to_string(GetGameInstance<CandyGameInstance>()->PlayerStat.Score)));

	}

}

void ACCSHUD::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


	Turn = GetGameInstance<CandyGameInstance>()->PlayerStat.Turn;

	TransText->SetText("남은 턴수: " + (std::to_string(Turn)));

	MaxScore = GetGameInstance<CandyGameInstance>()->GameStat.MaxScore;
	if (GetGameInstance<CandyGameInstance>()->PlayerStat.Score >= MaxScore) {
		GetGameInstance<CandyGameInstance>()->PlayerStat.Score = MaxScore;
	}

	ScoreText->SetText("점수: " + (std::to_string(GetGameInstance<CandyGameInstance>()->PlayerStat.Score)));

	


}