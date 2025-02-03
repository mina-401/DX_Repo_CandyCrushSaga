#include "PreCompile.h"
#include "ResultHUD.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/FontWidget.h>
#include <EngineCore/ImageWidget.h>
#include "CandyGameInstance.h"
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/GameInstance.h>
#include "CandyGameInstance.h"
#include <EngineCore/Actor.h>

AResultHUD::AResultHUD()
{



	Renderer = GetWorld()->GetHUD()->CreateWidget<UImageWidget>(-1).get();

	Renderer->SetTexture("ScorePanel.png");
	Renderer->SetAutoScale(false);
	Renderer->SetRelativeScale3D({300,200,0.0f });
	Renderer->SetWorldLocation({0,0,-300.0f });

	{
		Stars[0] = GetWorld()->GetHUD()->CreateWidget<UImageWidget>(-1).get();

		Stars[0]->SetTexture("Score_Star1.png");
		Stars[0]->SetAutoScale(false);
		Stars[0]->SetRelativeScale3D({ 100,100,0.0 });
		Stars[0]->SetWorldLocation({ -30,30,-310.0f });
	}
	{
		Stars[1] = GetWorld()->GetHUD()->CreateWidget<UImageWidget>(-1).get();

		Stars[1]->SetTexture("Score_Star2.png");
		Stars[1]->SetAutoScale(false);
		Stars[1]->SetRelativeScale3D({ 100,100,0.0 });
		Stars[1]->SetWorldLocation({ 80,30,-310.0f });
	}

	{
		Stars[2] = GetWorld()->GetHUD()->CreateWidget<UImageWidget>(-1).get();
		Stars[2]->SetTexture("Score_Star3.png");
		Stars[2]->SetAutoScale(false);
		Stars[2]->SetRelativeScale3D({ 100,100,0.0 });
		Stars[2]->SetWorldLocation({ 25,40,-310.0f });
	}

	for (int i = 0; i <= 2; i++)
	{
		Stars[i]->SetActive(false);
	}

	{

		ScroeResultText = GetWorld()->GetHUD()-> CreateWidget<UFontWidget>(-1).get();
		ScroeResultText->SetFont("BrandonGrotesqueBold", 20.0f, TColor<unsigned char>::BLACK, FW1_LEFT);
		ScroeResultText->SetWorldLocation({ 10,0 ,0 });

		ScroeResultText->SetText("Á¡¼ö: ");

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

void AResultHUD::Tick(float _DeltaTime)
{
	UWidget::Tick(_DeltaTime);

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
