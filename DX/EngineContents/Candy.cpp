#include "PreCompile.h"
#include "Candy.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

ACandy::ACandy()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetRelativeScale3D({ 50,50,0.0f });
	Renderer->SetWorldLocation({ -100,100,0.f });
	Renderer->SetAutoScale(false);
	


}

ACandy::~ACandy()
{
}

void ACandy::BeginPlay()
{
	AActor::BeginPlay();
	

	
	
}

void ACandy::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}

