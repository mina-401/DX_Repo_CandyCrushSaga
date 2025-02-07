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
#include <EngineCore/HUD.h>


AMouse::AMouse()
{

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);
	//Renderer->SetAutoScale(false);
	//Renderer->SetTexture("Mouse.png");
	//Renderer->SetScale3D({ 30.0f,30.0f});
	//Renderer->SetRe({ 30.0f,30.0f,-1000});

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Mouse");
	Collision->DebugOff();
	//Collision->SetRelativeScale3D({ 50,50,0.0f });

	//Collision->SetCollisionEnter(std::bind(&AMouse::CollisionEnter, this, std::placeholders::_1,std::placeholders::_2));

	Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
		{
			
			
			

		});


	Collision->SetCollisionStay([this](UCollision* _This, UCollision* _Other)
		{

			if (CandyManager->GetCandyState() != ECandyManagerState::Select)
			{
				return;
			}

			class ACandy* CurCandy = dynamic_cast<ACandy*>(_Other->GetActor());
			class AMouse* me = dynamic_cast<AMouse*>(_This->GetActor());

	

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
						

							for (int i = 0; i < 4; ++i) {

								int NextRow = SelectCandy->GetCandyData().row + dx[i];
								int NextCol = SelectCandy->GetCandyData().col + dy[i];

								if (NextRow == CurCandy->GetCandyData().row && NextCol == CurCandy->GetCandyData().col)
								{

									ACandy* SelectCandy = this->SelectCandy;
									FVector StartPos = SelectCandy->GetCandyData().SetPos;
									FVector EndPos = CurCandy->GetCandyData().SetPos;
									PlaySoundPlayer("switch_sound1.wav");

									TimeEventComponent->AddUpdateEvent(CCSConst::MoveTime, [this, SelectCandy, CurCandy,StartPos,EndPos](float _Delta, float _Acc)
										{
											CandyManager->ChangeCandyState(ECandyManagerState::Move);
											CandyMove(_Delta, _Acc, SelectCandy, CurCandy, StartPos, EndPos, CCSConst::MoveTime);
											
										});

									TimeEventComponent->AddEndEvent(CCSConst::MoveTime, [this, SelectCandy, CurCandy, StartPos, EndPos]()
										{
											// 자리바꾸기

											CandyManager->CandyChange(SelectCandy, CurCandy); 
											
											// 연속하는 캔디 찾기
											CandyManager->CandyFindConsec();
									
											
											if (false == CandyManager->IsCandyDestroy())
											{
												//콤보 캔디가 없다.
												TimeEventComponent->AddUpdateEvent(CCSConst::MoveTime, [this, SelectCandy, CurCandy, StartPos, EndPos](float _Delta, float _Acc)
													{
														CandyManager->ChangeCandyState(ECandyManagerState::Move);
														CandyMove(_Delta, _Acc, SelectCandy, CurCandy, EndPos, StartPos, CCSConst::MoveTime);
													});

												TimeEventComponent->AddEndEvent(CCSConst::MoveTime, [this, SelectCandy, CurCandy, StartPos, EndPos]()
													{
														CandyManager->CandyChange(SelectCandy, CurCandy);
														CandyManager->ChangeCandyState(ECandyManagerState::Select);
													});
											}

											else {
												//콤보 캔디가 있다.
												CandyManager->ChangeCandyState(ECandyManagerState::Destroy);

												GetGameInstance<CandyGameInstance>()-> PlayerStat.Turn--;
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

}
 
AMouse::~AMouse()
{
}

void AMouse::BeginPlay()
{
	AActor::BeginPlay();
	ImageRenderer = GetWorld()->GetHUD()->CreateWidget<UImageWidget>(-1);
	ImageRenderer->SetAutoScale(false);
	ImageRenderer->SetTexture("Mouse.png");
	ImageRenderer->SetScale3D({ 30.0f,30.0f });
	CandyManager = dynamic_cast<ACandyManager*>( GetWorld()->GetMainPawn());
	

	if (CandyManager == nullptr)
	{
		return;
	}

	int MaxRow= CandyManager->CandyRow;
	int MaxCol= CandyManager->CandyCol;
}

void AMouse::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
	FVector Pos = Camera->ScreenMousePosToWorldPos();

	FVector ImagePos = Pos;

	ImagePos.X += 5.0f;
	ImagePos.Y -= 5.0f;

	SetActorLocation(Pos); 
	ImageRenderer->SetWorldLocation(ImagePos);

	// 마우스 이동횟수 제한 있다.
	if (GetGameInstance<CandyGameInstance>()->PlayerStat.Turn == 0)
	{
		GetGameInstance<CandyGameInstance>()->CandyMouseCon.IsTransEnd = true;
	}

}


void AMouse::CandyMove(float _Delta, float _Acc, class ACandy* _SelectCandyPtr, class ACandy* _CurCandyPtr, FVector _StartPos, FVector _EndPos, float _MoveTime)
{
	_SelectCandyPtr->GetCandyData().SetPos = FVector::Lerp(_StartPos, _EndPos, _Acc * 1 / _MoveTime);
	_CurCandyPtr->GetCandyData().SetPos = FVector::Lerp(_EndPos, _StartPos, _Acc * 1 / _MoveTime);

	
}

void AMouse::PlaySoundPlayer(std::string _sound)
{
	{
		USoundPlayer SoundPlayer;
		SoundPlayer.SetVolume(0.5f);
		SoundPlayer = UEngineSound::Play(_sound);
	}
}
