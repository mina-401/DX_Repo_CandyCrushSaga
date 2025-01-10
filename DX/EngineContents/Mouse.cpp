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
#include "PlayGameMode.h"
#include "CandyManager.h"

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

	//Collision->SetCollisionEnter(std::bind(&AMouse::CollisionEnter, this, std::placeholders::_1,std::placeholders::_2));

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			class ACandy* CurCandy = dynamic_cast<ACandy*>(_Other->GetActor());
			UEngineDebug::OutPutString("End");
			CurCandy->GetCandyData();

		});


	Collision->SetCollisionStay([this](UCollision* _This, UCollision* _Other)
		{
			class ACandy* CurCandy = dynamic_cast<ACandy*>(_Other->GetActor());
			class AMouse* me = dynamic_cast<AMouse*>(_This->GetActor());

			if (nullptr == this->SelectCandy)
			{
				UEngineDebug::OutPutString("Not Candy");
			}
			else {
				UEngineDebug::OutPutString("Candy Select");
			}

			if (CurCandy != nullptr) {
				if (true == UEngineInput::IsDown(VK_LBUTTON))
				{
					this->SelectCandy = CurCandy;
				}

				if (true == UEngineInput::IsUp(VK_LBUTTON))
				{
					if (nullptr != this->SelectCandy)
					{
						if (this->SelectCandy == CurCandy)
						{
							this->SelectCandy = nullptr;
						}
						else 
						{

							int dx[4] = { 0,0,-1,1 };
							int dy[4] = { 1,-1,0,0 };
							int SelectRow= this->SelectCandy->GetCandyData().row;
							int SelectCol= this->SelectCandy->GetCandyData().col;

							int CurRow= CurCandy->GetCandyData().row;
							int CurCol= CurCandy->GetCandyData().col;

							for (int i = 0; i < 4; ++i) {
								int NextRow = SelectRow + dx[i];
								int NextCol = SelectCol + dy[i];

								/*if (NextRow >= 1 && NextRow <= MaxRow && NextCol >= 1 && NextCol <= MaxCol) {
									
								}*/

								if (NextRow == CurRow && NextCol == CurCol)
								{
									SelectCandy->GetCandyData().row = CurRow;
									SelectCandy->GetCandyData().col = CurRow;


									FVector NextPos = SelectCandy->GetCandyData().SetPos;

									CurCandy->GetCandyData().row = SelectRow;
									CurCandy->GetCandyData().col = SelectCol;
									CurCandy->GetCandyData().SetPos = { SelectCandy->GetCandyData().SetPos };

									SelectCandy->GetCandyData().SetPos = NextPos;
								}
							}
							
							//일단 체인지 하게끔

							int a = 0;
						}
					}
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

//void AMouse::CollisionEnter(UCollision* _This, UCollision* _Other)
//{
//	int a = 0;
//}
void AMouse::BeginPlay()
{
	AActor::BeginPlay();

	class APlayGameMode* PlayGameMode= dynamic_cast<APlayGameMode*>(GetWorld()->GetGameMode());
	std::shared_ptr<class ACandyManager> CandyManager = PlayGameMode->GetCandyManager();
	
	int MaxRow= CandyManager->CandyRow;
	int MaxCol= CandyManager->CandyCol;
}

void AMouse::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
	FVector Pos = Camera->ScreenMousePosToWorldPos();
	Pos.Z = 0.0f;

	SetActorLocation(Pos);
}

