#include "PreCompile.h"
#include "TitleLogo.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>

ATitleLogo::ATitleLogo()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// �������� �����.
	LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();
	LogoRenderer->SetSprite("Player.png", 0);

	// �θ� �������� �ʴ� root�� Relative�� Local�̴� 
	// ����� ����. 
	// �θ��� ũ�⿡ ���� ������ ������ �ֱ� �빮�� �Լ��� �������̴�.
	// �θ� ������
	LogoRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	LogoRenderer->SetupAttachment(RootComponent);


	Child = CreateDefaultSubObject<USpriteRenderer>();
	Child->SetSprite("Player.png", 2);
	// �θ��� �������� ������ ������ �ָ鼭 ���� 100�� �ƴҼ��� �ִ�
	Child->SetRelativeLocation({ 100.0f, 0.0f, 0.0f });
	Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	// Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
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

	if (UEngineInput::IsPress('A'))
	{
		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	if (UEngineInput::IsPress('W'))
	{
		AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('Q'))
	{
		AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	}

	if (UEngineInput::IsPress('E'))
	{
		// �� 1������ ó���Ǵ� �ɷ� 
		Child->AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f , 0.0f });
	}

	if (UEngineInput::IsPress('R'))
	{
		Child->SetLocation(FVector{ 100.0f, 0.0f , 0.0f });
	}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}