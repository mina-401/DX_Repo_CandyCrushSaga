#include "PreCompile.h"
#include "CandyManager.h"	
#include <EngineCore/Level.h>
#include <EngineCore/EngineCore.h>

#include <EngineCore/SpriteRenderer.h>

#include "Candy.h"

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

	Candys.resize(X + 1);
	for (int i = 1; i <= X; i++)
	{
		Candys[i].resize(Y + 1);
	}

	Data.resize(X + 1);
	for (int i = 1; i <= X; i++)
	{
		Data[i].resize(Y + 1);
	}
	
}

void ACandyManager::DeleteIndex(int X, int Y)
{
	Data[X][Y].IsActive = false;
}

void ACandyManager::CandyCreate()
{
	{


		FVector CurPos = { 0,0 };
		FVector ScaleSprite = { 0,0 };
		for (int row = 1; row <= CandyRow; row++)
		{

			std::shared_ptr<class ACandy> NewCandy = nullptr;
			for (int col = 1; col <= CandyCol; col++)		
			{
				if (false == Data[row][col].IsActive) {}
				else {
					// Äµµð ½ºÆù
					int RandomIndx = RandomInt(1, 47);
					NewCandy =GetWorld()->SpawnActor<ACandy>();			
					NewCandy->SetCandy({row,col}, CurPos, RandomIndx);
					Candys[row][col] = NewCandy;
				}
			}

			float PlusPos = (NewCandy->GetRenderer()->GetWorldScale3D().Y+5.0f);
			CurPos.Y -= PlusPos;
			CurPos.X = 0;
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

