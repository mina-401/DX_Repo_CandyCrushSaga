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
				UEngineDebug::OutPutString("Not Candy");
				

			}
			else {
				UEngineDebug::OutPutString("Candy Select");
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

							FCandySpriteData& SelectCandyDataRef = this->SelectCandy->GetCandyData();
							SelectCandyData = this->SelectCandy->CandyData;

							FCandySpriteData& CurCandyDataRef = CurCandy->GetCandyData();
							CurCandyData = CurCandy->CandyData;
						
							/*SelectCandyData = this->SelectCandy->CandyData;
							CurCandyData = CurCandy->CandyData;*/

							for (int i = 0; i < 4; ++i) {

								/*int NextRow = SelectCandyDataRef.row + dx[i];
								int NextCol = SelectCandyDataRef.col + dy[i];*/

								int NextRow = this->SelectCandy->CandyData.row + dx[i];
								int NextCol = this->SelectCandy->CandyData.col + dy[i];

								if (NextRow == CurCandyData.row && NextCol == CurCandyData.col)
								{
									//TimeEventComponent->AddEndEvent(2.0f, std::bind(&AMouse::TestFunction,this,std::placeholders::_1), false);
									/*TimeEventComponent->AddEndEvent(0.5f, [this]() {
										SelectCandyDataRef.row = CurCandyData.row;
										SelectCandyDataRef.col = CurCandyData.col;
										SelectCandyDataRef.SetPos = CurCandyData.SetPos;

										CurCandyDataRef.row = SelectCandyData.row;
										CurCandyDataRef.col = SelectCandyData.col;
										CurCandyDataRef.SetPos = SelectCandyData.SetPos;


									});*/

									/*this->SelectCandy->GetCandyData().row = CurCandyData.row;
									this->SelectCandy->GetCandyData().col = CurCandyData.col;
									this->SelectCandy->GetCandyData().SetPos = CurCandyData.SetPos;

									CurCandy->GetCandyData().row = SelectCandyData.row;
									CurCandy->GetCandyData().col = SelectCandyData.col;
									CurCandy->GetCandyData().SetPos = SelectCandyData.SetPos;*/
									
									SelectCandyDataRef.row = CurCandyData.row;
									SelectCandyDataRef.col = CurCandyData.col;
									SelectCandyDataRef.SetPos = CurCandyData.SetPos;

									CurCandyDataRef.row = SelectCandyData.row;
									CurCandyDataRef.col = SelectCandyData.col;
									CurCandyDataRef.SetPos = SelectCandyData.SetPos;
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

