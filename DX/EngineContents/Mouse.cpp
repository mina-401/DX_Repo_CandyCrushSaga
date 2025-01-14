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
#include <EngineCore/TimeEventComponent.h>
#include "CCSConst.h"
#include "Queue.h"

AMouse::AMouse()
{

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
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
				//UEngineDebug::OutPutString("Not Candy");
				

			}
			else {
				//UEngineDebug::OutPutString("Candy Select");
			}

			if (CurCandy != nullptr) {
				if (true == UEngineInput::IsDown(VK_LBUTTON))
				{
					this->SelectCandy = CurCandy;
					//this->SelectCandy->SetActive(false);


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
						

							for (int i = 0; i < 4; ++i) {

								int NextRow = SelectCandy->GetCandyData().row + dx[i];
								int NextCol = SelectCandy->GetCandyData().col + dy[i];

								if (NextRow == CurCandy->GetCandyData().row && NextCol == CurCandy->GetCandyData().col)
								{

									ACandy* SelectCandy = this->SelectCandy;
									FVector StartPos = SelectCandy->GetCandyData().SetPos;
									FVector EndPos = CurCandy->GetCandyData().SetPos;

									TimeEventComponent->AddUpdateEvent(CCSConst::MoveTime, [this, SelectCandy, CurCandy,StartPos,EndPos](float _Delta, float _Acc)
										{
											CandyMove(_Delta, _Acc, SelectCandy, CurCandy, StartPos, EndPos, CCSConst::MoveTime);
											
										});

									TimeEventComponent->AddEndEvent(CCSConst::MoveTime, [this, SelectCandy, CurCandy, StartPos, EndPos]()
										{
											// if (검사를 했는데 터질게 없어)

											bool CheckCombo = false;

											CandyManager->CandyBFS(SelectCandy);
											
								
											if (false== CheckCombo)
											{
												TimeEventComponent->AddUpdateEvent(0.2f, [this, SelectCandy, CurCandy, StartPos, EndPos](float _Delta, float _Acc)
													{
														SelectCandy->GetCandyData().SetPos = FVector::Lerp(EndPos, StartPos, _Acc * 1 / 0.2f);

														CurCandy->GetCandyData().SetPos = FVector::Lerp(StartPos, EndPos, _Acc * 1 / 0.2f);
													});
												// return;
											}

										});



									
									
									break;
									

								}

								
							}
							

							this->SelectCandy = nullptr;
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
void AMouse::TestFunction(FCandySpriteData& _a)

{ }
//void AMouse::CollisionEnter(UCollision* _This, UCollision* _Other)
//{
//	int a = 0;
//}
void AMouse::BeginPlay()
{
	AActor::BeginPlay();

	class APlayGameMode* PlayGameMode= dynamic_cast<APlayGameMode*>(GetWorld()->GetGameMode());
	CandyManager = PlayGameMode->GetCandyManager();
	if (CandyManager == nullptr)
	{
		int a = 0;
	}

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


void AMouse::CandyMove(float _Delta, float _Acc, class ACandy* _SelectCandyPtr, class ACandy* _CurCandyPtr, FVector _StartPos, FVector _EndPos, float _MoveTime)
{
	_SelectCandyPtr->GetCandyData().SetPos = FVector::Lerp(_StartPos, _EndPos, _Acc * 1 / _MoveTime);
	_CurCandyPtr->GetCandyData().SetPos = FVector::Lerp(_EndPos, _StartPos, _Acc * 1 / _MoveTime);
}