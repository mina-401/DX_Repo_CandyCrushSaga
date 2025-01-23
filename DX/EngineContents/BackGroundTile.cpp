#include "PreCompile.h"
#include "BackGroundTile.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

ABackGroundTile::ABackGroundTile()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);

	Renderer->SetSprite("Candy", 0);
	//Renderer->SetRelativeScale3D({ 50.0f,50.0f,0.0f });
	FVector Size = UEngineCore::GetScreenScale();
}

ABackGroundTile::~ABackGroundTile()
{

}

void ABackGroundTile::BeginPlay()
{
	AActor::BeginPlay();
}

void ABackGroundTile::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
