#include "PreCompile.h"
#include "TitleMap.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
ATitleMap::ATitleMap()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetTexture("Title.png");
	Renderer->SetRelativeScale3D({ 100, 100, 1.0f });
	Renderer->SetupAttachment(RootComponent);
}

ATitleMap::~ATitleMap()
{
}
void ATitleMap::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}