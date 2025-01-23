#include "PreCompile.h"
#include "MeshActor.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/TimeEventComponent.h>
#include "MyCustomRenderer.h"
#include <EngineCore/Collision.h>
#include <EngineCore/Level.h>

AMeshActor::AMeshActor()
{

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;
	RootComponent->Parent;

	// 사이드 이펙트.
	std::shared_ptr<URenderer> Renderer = CreateDefaultSubObject<URenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->CreateRenderUnit();
	Renderer->Parent;

	URenderUnit& Unit = Renderer->GetRenderUnit();
	Unit.SetMesh("Sphere");
	Unit.SetMaterial("LightMesh");
	Unit.ConstantBufferLinkData("MeshColor", &ResultColor);

	// 

	// Renderer->SetTexture("Test.png");
	// Renderer->SetScale3D({ 50.0f, 50.0f });

}

AMeshActor::~AMeshActor()
{
}

void AMeshActor::BeginPlay()
{
	AActor::BeginPlay();
}

void AMeshActor::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (UEngineInput::IsDown('P'))
	{
		GetWorld()->GetMainCamera()->FreeCameraOn();
		GetWorld()->GetMainCamera()->SetFreeCameraRotSpeed(1000.0f);
	}

	// AddActorRotation({0.0f, 0.0f, 360.0f * _DeltaTime });
}
