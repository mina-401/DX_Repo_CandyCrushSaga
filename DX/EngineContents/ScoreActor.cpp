#include "PreCompile.h"
#include "ScoreActor.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

AScoreActor::AScoreActor()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>().get();
	Renderer->SetupAttachment(RootComponent);

	Renderer->SetSprite("Message.png", 0);
	Renderer->SetAutoScale(false);
	Renderer->SetRelativeScale3D({200,100,1.0f });
	FVector Size = UEngineCore::GetScreenScale();
}

AScoreActor::~AScoreActor()
{

}
void AScoreActor::SetSprite(int index)
{
	Renderer->SetSprite("Message.png", index);
}
void AScoreActor::BeginPlay()
{
	AActor::BeginPlay();

	Destroy(2);
}

void AScoreActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	SetActorLocation(GetActorLocation()+ GetActorUpVector()*_DeltaTime*50.0f);
	//Renderer->AddRelativeLocation({ 0.0f,GetActorForwardVector()*_DeltaTime*100.0f,1.0f });

}
