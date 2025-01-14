#include "PreCompile.h"
#include "Candy.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/Collision.h>
#include <EngineCore/Level.h>
#include "PlayGameMode.h"
#include <EnginePlatform/EngineInput.h>


ACandy::ACandy()
{
	//SetActorLocation({ -500,0,0.0f });

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;


	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetRelativeScale3D({ 50,50,0.0f });
	//Renderer->SetWorldLocation({ 250,100,0.f });
	Renderer->SetAutoScale(false);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Candy");

	Collision->SetRelativeScale3D({ 50,50,0.0f });

}

ACandy::~ACandy()
{
}

void ACandy::SetCandy(FVector RenderPos, FVector& _Pos, int _Index)
{
	//AddActorLocation(_Pos);

	GetRenderer()->SetSprite("Candy",_Index);

	CandyData.row = RenderPos.X;
	CandyData.col = RenderPos.Y;
	CandyData.SpriteIndex = _Index;
	CandyData.SetPos = _Pos;

	CandyData.SetSpriteColor(_Index);
	CandyData.SetSpriteType(_Index);

	//SetName("Candy");
}
void ACandy::BeginPlay()
{
	AActor::BeginPlay();
	
}

void ACandy::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	SetActorLocation(CandyData.SetPos);

}

