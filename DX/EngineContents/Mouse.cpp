#include "PreCompile.h"
#include "Mouse.h"
#include "Candy.h"
#include <EngineCore/EngineCore.h>
#include <EngineCore/Collision.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/Level.h>
#include <EnginePlatform/EngineInput.h>

AMouse::AMouse()
{

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;


	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	Renderer->SetAutoScale(false);

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Mouse");

	//Collision->SetRelativeScale3D({ 50,50,0.0f });

	//Collision->SetCollisionEnter(std::bind(&AMouse::CollisionStay, this, std::placeholders::_1));

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			//
			if (true == UEngineInput::IsDown(VK_LBUTTON))
			{
				
			}

		});

	Collision->SetCollisionStay([](UCollision* _This, UCollision* _Other)
		{
		

			class ACandy* SelectCandy = dynamic_cast<ACandy*>(_Other->GetActor());
			class AMouse* me = dynamic_cast<AMouse*>(_This->GetActor());
			

			if (SelectCandy != nullptr) {
				if (true == UEngineInput::IsPress(VK_LBUTTON))
				{
					me->IsCandy = true;

					//if (true == me->IsCandy) return;

					FVector Pos = _This->GetActor()->GetActorLocation();


					SelectCandy->SetActorLocation(Pos);  
				}

				else if (true == UEngineInput::IsUp(VK_LBUTTON))
				{
					me->IsCandy = false;

					SelectCandy->SetActorLocation(SelectCandy->GetCandyData().SetPos);
					
				}
			}
			
		});

	Collision->SetCollisionEnd([](UCollision* _This, UCollision* _Other)
		{
			//UEngineDebug::OutPutString("End");

		});
}

AMouse::~AMouse()
{
}

void AMouse::BeginPlay()
{
	AActor::BeginPlay();
}

void AMouse::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
	FVector Pos = Camera->ScreenMousePosToWorldPos();
	Pos.Z = 0.0f;

	SetActorLocation(Pos);
}

