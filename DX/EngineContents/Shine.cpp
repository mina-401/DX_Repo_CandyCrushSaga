#include "PreCompile.h"
#include "Shine.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

AShine::AShine()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;


	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetTexture("CandyCrushStarParticle.png");
	Renderer->SetRelativeScale3D({ 50,50,0.0f });
}

AShine::~AShine()
{
}

void AShine::BeginPlay()
{
	AActor::BeginPlay();
}

void AShine::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

