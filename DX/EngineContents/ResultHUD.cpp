#include "PreCompile.h"
#include "ResultHUD.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/FontWidget.h>
#include "CandyGameInstance.h"
#include <EngineCore/TimeEventComponent.h>


AResultHUD::AResultHUD()
{


	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>().get();
	Renderer->SetupAttachment(RootComponent);

	Renderer->SetTexture("ScorePanel.png");
	Renderer->SetAutoScale(false);
	Renderer->SetRelativeScale3D({300,200,0.0f });
	Renderer->SetWorldLocation({0,0,-300.0f });

	{
		Stars[0] = CreateDefaultSubObject<USpriteRenderer>().get();
		Stars[0]->SetupAttachment(RootComponent);

		Stars[0]->SetTexture("Score_Star1.png");
		Stars[0]->SetAutoScale(false);
		Stars[0]->SetRelativeScale3D({ 100,100,0.0 });
		Stars[0]->SetWorldLocation({ -30,30,-310.0f });
	}
	{
		Stars[1] = CreateDefaultSubObject<USpriteRenderer>().get();
		Stars[1]->SetupAttachment(RootComponent);

		Stars[1]->SetTexture("Score_Star2.png");
		Stars[1]->SetAutoScale(false);
		Stars[1]->SetRelativeScale3D({ 100,100,0.0 });
		Stars[1]->SetWorldLocation({ 80,30,-310.0f });
	}

	{
		Stars[2] = CreateDefaultSubObject<USpriteRenderer>().get();
		Stars[2]->SetupAttachment(RootComponent);
		Stars[2]->SetTexture("Score_Star3.png");
		Stars[2]->SetAutoScale(false);
		Stars[2]->SetRelativeScale3D({ 100,100,0.0 });
		Stars[2]->SetWorldLocation({ 25,40,-310.0f });
	}

	
}

AResultHUD::~AResultHUD()
{
	int a = 0;
}
void AResultHUD::SetSprite(int index)
{
	Renderer->SetSprite("Message.png", index);
}
void AResultHUD::BeginPlay()
{
	AActor::BeginPlay();

	for (int i = 0; i <= 2; i++)
	{
		Stars[i]->SetActive(false);
	}

	{

		UFontWidget* ScoreText = CreateWidget<UFontWidget>(-1).get();
		ScoreText->SetFont("BrandonGrotesqueBold", 20.0f, TColor<unsigned char>::BLACK, FW1_LEFT);
		ScoreText->SetWorldLocation({ -30,0 ,0 });

		ScoreText->SetText("내 점수는..: ");

	}
}

void AResultHUD::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//ScoreText->SetText("점수: " + std::to_string(GetGameInstance<CandyGameInstance>()->PlayerStat.Score ));




	if (CurTime > DestroyTime)
	{
		CurTime = 0;

		Destroy();

	}

	CurTime += 0.2f;


}

void AResultHUD::StarSetActive(int _value) {

	Stars[_value]->SetActive(true);

	
}
void AResultHUD::SetScoreStar(int _value) {

	ScoreStar = _value;


}
