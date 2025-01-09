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
	Renderer->SetWorldLocation({ 250,100,0.f });
	Renderer->SetAutoScale(false);
	
}

ACandy::~ACandy()
{
}

void ACandy::SetCandy(FVector RenderPos, FVector& _Pos, int _Index)
{
	row = RenderPos.X;
	col = RenderPos.Y;

	GetRenderer()->SetSprite("Candy", _Index);

	FVector ScaleSprite = GetRenderer()->GetWorldScale3D();
	ScaleSprite.X += 10.0f;
	_Pos = { _Pos.X - ScaleSprite.X,_Pos.Y };

	AddActorLocation(_Pos);

}

void ACandy::BeginPlay()
{
	AActor::BeginPlay();
	

	
	
}

void ACandy::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}

