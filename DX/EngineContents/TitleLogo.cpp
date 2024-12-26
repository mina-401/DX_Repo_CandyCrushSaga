#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>

ATitleLogo::ATitleLogo()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 랜더러를 만든다.
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetSprite("Candy.png", 0);
	LogoRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	LogoRenderer->SetupAttachment(RootComponent);


	std::shared_ptr<class USpriteRenderer> Child = CreateDefaultSubObject<USpriteRenderer>();
	Child->SetSprite("Candy.png", 2);
	Child->SetLocation({ 100.0f, 0.0f, 0.0f });
	Child->SetRelativeScale3D({ 50.0f, 50.0f, 1.0f });
	Child->SetupAttachment(RootComponent);

	// 애를 했을때는 실제 스케일은 1 1 1 
	std::shared_ptr<class USpriteRenderer> Child2 = CreateDefaultSubObject<USpriteRenderer>();
	Child2->SetSprite("Candy.png", 2);
	Child2->SetLocation({ -100.0f, 0.0f, 0.0f });
	Child2->SetRelativeScale3D({ 1.0f, 1.0f, 1.0f });

	Child->SetupAttachment(LogoRenderer);
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

	if (UEngineInput::IsPress('A'))
	{
		AddActorLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	if (UEngineInput::IsPress('W'))
	{
		AddActorLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddActorLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('Q'))
	{
		AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}