#include "PreCompile.h"
#include "ResultHUD.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

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
	//FVector Size = UEngineCore::GetScreenScale();
}

AResultHUD::~AResultHUD()
{

}
void AResultHUD::SetSprite(int index)
{
	Renderer->SetSprite("Message.png", index);
}
void AResultHUD::BeginPlay()
{
	AActor::BeginPlay();

	//Destroy(2);
}

void AResultHUD::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	//SetActorLocation(GetActorLocation()+ GetActorUpVector()*_DeltaTime*50.0f);
	//Renderer->AddRelativeLocation({ 0.0f,GetActorForwardVector()*_DeltaTime*100.0f,1.0f });

}
