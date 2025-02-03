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
		ButtonWidget = CreateWidget<UImageWidget>(-1).get();

		FVector Size = UEngineCore::GetMainWindow().GetWindowSize();

		float X = Size.X / 2 - 100.0f;
		float Y = Size.Y / 2 - 100.0f;

		ButtonWidget->SetWorldLocation({ -290,-50,0 });
		ButtonWidget->SetScale3D({ 100,150.0f,0.0f });
		ButtonWidget->SetTexture("StartButton_2.png");
		ButtonWidget->SetAutoScale(false);

		

		UFontWidget* RestartText = CreateWidget<UFontWidget>(-1).get();
		RestartText->SetFont("BrandonGrotesqueBold", 20.0f, TColor<unsigned char>::BLACK, FW1_CENTER);
		RestartText->SetWorldLocation({ -290,-35,0 });

		RestartText->SetText("돌리기");

		ButtonWidget->SetDownEvent([this] {
			ButtonWidget->SetScale3D({ 120,170.0f,0.0f });
		});
		ButtonWidget->SetUpEvent([this] {
			ButtonWidget->SetScale3D({ 100,150,0.0f });
			IsRestart = true;
		});
	}
	{

		Score = CreateWidget<UImageWidget>(-1);
		Score->SetAutoScale(false);
		Score->SetWorldLocation({ -191,-57 });
		Score->SetScale3D({ 33,0.0f,0.0f });
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

		ScoreStar1 = CreateWidget<UImageWidget>(-1).get();
		ScoreStar1->SetAutoScale(false);
		ScoreStar1->SetWorldLocation({ -175,-30 });
		ScoreStar1->SetScale3D({ 50,50,0.0f });
		ScoreStar1->SetTexture("Score_Star1.png");

		ScoreStar2 = CreateWidget<UImageWidget>(-1).get();
		ScoreStar2->SetAutoScale(false);
		ScoreStar2->SetWorldLocation({ -175,10 });
		ScoreStar2->SetScale3D({ 50,50,0.0f });
		ScoreStar2->SetTexture("Score_Star2.png");

		ScoreStar3 = CreateWidget<UImageWidget>(-1).get();
		ScoreStar3->SetAutoScale(false);
		ScoreStar3->SetWorldLocation({ -175,50 });
		ScoreStar3->SetScale3D({ 50,50,0.0f });
		ScoreStar3->SetTexture("Score_Star3.png");
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

		MaxScoreText = CreateWidget<UFontWidget>(-1).get();
		MaxScoreText->SetFont("BrandonGrotesqueBold", 20.0f, TColor<unsigned char>::BLACK, FW1_LEFT);
		MaxScoreText->SetWorldLocation({ -310,200 });

	}

}

void ACCSHUD::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);



	Turn = GetGameInstance<CandyGameInstance>()->PlayerStat.Turn;

	TransText->SetText("남은 턴수: " + (std::to_string(Turn)));

	MaxScore = GetGameInstance<CandyGameInstance>()->GameStat.MaxScore;
	if (GetGameInstance<CandyGameInstance>()->PlayerStat.Score >= 9999) {
		GetGameInstance<CandyGameInstance>()->PlayerStat.Score = 9999;
	}

	MaxScoreText->SetText("목표 점수: " + (std::to_string(GetGameInstance<CandyGameInstance>()->GameStat.MaxScore)));
	ScoreText->SetText("점수: " + (std::to_string(GetGameInstance<CandyGameInstance>()->PlayerStat.Score)));

	if (IsRestart == true)
	{
		GetGameInstance<CandyGameInstance>()->IsRestart = true;
		IsRestart = false;
	}


}