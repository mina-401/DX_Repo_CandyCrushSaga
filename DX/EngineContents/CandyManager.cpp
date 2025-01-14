#include "PreCompile.h"
#include "CandyManager.h"	
#include <EngineCore/Level.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>


#include "Candy.h"
#include <EnginePlatform/EngineInput.h>
#include "Queue.h"


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
	Visited.resize(X);
	for (int i = 0; i < X; i++)
	{
		Visited[i].resize(Y);
		for (int j = 0; j < Y; j++)
		{
			Visited[i][j] = false;
		}
	}

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

			std::shared_ptr< ACandy> NewCandy = nullptr;
			for (int col = 0; col < CandyCol; col++)		
			{
				SetPos.X += CandyScale.X;
				if (false == Data[row][col].IsActive) {}
				else {
					// 캔디 스폰
					int RandomIndx = RandomInt(1, 55);
					//NewCandy =GetWorld()->SpawnActor<ACandy*>();
					NewCandy = GetWorld()->SpawnActor<ACandy>();
					
					NewCandy->SetCandy({row,col}, SetPos, RandomIndx);
					Candys[row][col] = NewCandy.get();
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
void ACandyManager::CandyBFS(class ACandy* _SelectCandy,class ACandy* _ChangedCandy)
{

	int dx[4] = { 1, 0, -1, 0 };
	int dy[4] = { 0, 1, 0, -1 };

	Queue<ACandy*> Q(CandyCol*CandyRow);

	EColor CurColor = _SelectCandy->CandyData.CandyColor;
	int row = _ChangedCandy->CandyData.row;
	int col = _ChangedCandy->CandyData.col;

	Visited[row][col] = true;

	Q.Push(_ChangedCandy);

	while (!Q.Emtpy())
	{
		ACandy* Cur = Q.Front();
		Q.Pop();

		for (int dir = 0; dir < 4; dir++)
		{
			int nx = Cur->CandyData.row + dx[dir];
			int ny = Cur->CandyData.col + dy[dir];

			if (nx < 0 || nx >= CandyRow || ny < 0 || ny >= CandyCol)
			{
				continue;
			}

			EColor NextColor = Candys[nx][ny]->CandyData.CandyColor;

			bool IsDiff = CurColor == NextColor ? false : true;


			//캔디끼리 색깔이 다르다, 방문한 노드이다.
			if (true == Visited[nx][ny] || true==IsDiff)
			{
				continue;
			}

			Visited[nx][ny] = true;
			Q.Push(Candys[nx][ny]);
		}
	}
	int a = 0;

}

void ACandyManager::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	
}

