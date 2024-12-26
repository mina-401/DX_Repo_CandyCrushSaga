#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
ATitleLogo::ATitleLogo()
{
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetSprite("Player.png", 0);
	LogoRenderer->SetRelativeScale3D({ 50, 50 });
	RootComponent = LogoRenderer;
	// SetActorRelativeScale3D({50.0f, 50.0f, 1.0f });


	std::shared_ptr<class USpriteRenderer> Child = CreateDefaultSubObject<USpriteRenderer>();
	Child->SetSprite("Player.png", 2);
	Child->SetLocation({ 2.0f, 0.0f, 0.0f });
	Child->SetupAttachment(RootComponent);



}

ATitleLogo::~ATitleLogo()
{
}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	AddActorLocation(FVector{ 0.01f, 0.0f, 0.0f });

}