#include "PreCompile.h"
#include "TitleMap.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCore.h>
#include "CustomTestRenderer.h"

ATitleMap::ATitleMap()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<CustomTestRenderer>();
	Renderer->SetupAttachment(RootComponent);
	//UEngineSprite::CreateSpriteToMeta("Title.png", ".sdata");
	//Renderer = CreateDefaultSubObject<USpriteRenderer>();
	//Renderer->SetSprite("Title.png");
	//Renderer->SetTexture("Title.png");

	FVector Size = UEngineCore::GetScreenScale();

	Renderer->SetRelativeScale3D({ 100,100,1.0f});
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