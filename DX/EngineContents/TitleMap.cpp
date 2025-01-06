#include "PreCompile.h"
#include "TitleMap.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCore.h>
#include "TitleButton.h"


ATitleMap::ATitleMap()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);

	Renderer->SetTexture("TitleMap.png");
	
	FVector Size = UEngineCore::GetScreenScale();
	Renderer->SetRelativeScale3D({Size.X,Size.Y,0.0f});

	//Button = GetWorld()->SpawnActor<ATitleButton>();

	
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