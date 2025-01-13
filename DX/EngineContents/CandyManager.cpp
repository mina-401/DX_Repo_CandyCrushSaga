#include "PreCompile.h"
#include "CandyManager.h"	
#include <EngineCore/Level.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>


#include "Candy.h"
#include <EnginePlatform/EngineInput.h>


ACandyManager::ACandyManager()
{
	
}

ACandyManager::~ACandyManager()
{
}

void ACandyManager::CreateStage(int X, int Y)
{

	CandyRow = X;
	CandyCol = Y;

	Candys.resize(X);
	for (int i = 0; i < X; i++)
	{
		Candys[i].resize(Y);
	}

	Data.resize(X);
	for (int i = 0; i < X; i++)
	{
		Data[i].resize(Y);
	}

	//
	
}

void ACandyManager::DeleteIndex(int X, int Y)
{
	Data[X][Y].IsActive = false;
}

void ACandyManager::CandyCreate()
{
	{
		FVector SetPos = { -100,100};
		for (int row = 0; row < CandyRow; row++)
		{

			std::shared_ptr<class ACandy> NewCandy = nullptr;
			for (int col = 0; col < CandyCol; col++)		
			{
				SetPos.X += CandyScale.X;
				if (false == Data[row][col].IsActive) {}
				else {
					// Äµµð ½ºÆù
					int RandomIndx = RandomInt(1, 46);
					NewCandy =GetWorld()->SpawnActor<ACandy>();

					
					NewCandy->SetCandy({row,col}, SetPos, RandomIndx);
					Candys[row][col] = NewCandy;
				}
			}
			SetPos.X = -100;
			SetPos.Y -= CandyScale.Y;
		
			
		}
	}
}

void ACandyManager::BeginPlay()
{
	AActor::BeginPlay();
	

}

void ACandyManager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	
}

