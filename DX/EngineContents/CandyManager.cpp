#include "PreCompile.h"
#include "CandyManager.h"   
#include <EngineCore/Level.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>


#include "Candy.h"
#include <EnginePlatform/EngineInput.h>
#include "MyQueue.h"
#include <queue>


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
        FVector SetPos = { -100,100 };
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

                    NewCandy->SetCandy({ row,col }, SetPos, RandomIndx);
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

void ACandyManager::RowCheck(int X, int Y)
{
  
    
    EColor CurColor = Candys[X][Y]->CandyData.CandyColor;

    int col = Y;

    for (int row = X; row < CandyRow; row++)
    {

        if (X == row) continue;
        ACandy* Target = Candys[row][col];
        // 요소가 이미 제거할 캔디 리스트에 있는지 확인한다.
        if (std::find(DestroyCandy.begin(), DestroyCandy.end(), Target) != DestroyCandy.end()) {
            return;
        }

       EColor DiffColor= Candys[row][col]->CandyData.CandyColor;

       if (CurColor == DiffColor)
       {
           DestroyCandy.push_back(Candys[row][col]);
           Combo++;
       }
       else
       {
           //if ( 3 > Combo )
           //{
           //    while (0< Combo)
           //    {
           //        // 2 ->1 -> 0  
           //        Combo--;
           //        //DestroyCandy.Pop();
           //    }
           //    
           //}
           //Combo = 1;

       }
    }
}
void ACandyManager::ColCheck(int X, int Y)
{

}

void ACandyManager::CandyBFS()
{
    int dx[4] = { 1, 0, -1, 0 };
    int dy[4] = { 0, 1, 0, -1 };

    //std::list<ACandy*> DestroyCandy;
    

    for (int row = 0; row < CandyRow; row++)
    {
        for (int col = 0; col < CandyCol; col++)
        {
            RowCheck(row, col);
            ColCheck(row, col);
        }
    }



    //while (!Q.Emtpy())
    //{
    //   ACandy* Cur = Q.Front();
    //   Q.Pop();

    //   EColor CurColor = Cur->CandyData.CandyColor;


    //   for (int dir = 0; dir < 4; dir++)
    //   {
    //      int nx = Cur->CandyData.row + dx[dir];
    //      int ny = Cur->CandyData.col + dy[dir];

    //      if (nx < 0 || nx >= CandyRow || ny < 0 || ny >= CandyCol)
    //      {
    //         continue;
    //      }

    //      // 방문한 노드이다.
    //      if (true == Visited[nx][ny])
    //      {
    //         continue;
    //      }
    //      EColor NextColor = Candys[nx][ny]->CandyData.CandyColor;

    //      if (CurColor == NextColor)
    //      {
    //         
    //         /*Candys[nx][ny]->CandyData.Combo=Cur->CandyData.Combo+1;
    //         Candys[nx][ny]->CandyData.IsCombo = true;*/
    //      }
    //      else
    //      {
    //         
    //      }
    //      Visited[nx][ny] = true;
    //      Q.Push(Candys[nx][ny]);
    //   }
    //}

}

void ACandyManager::ShowOff()
{


    for (int i = 0; i < CandyRow; i++)
    {
        for (int j = 0; j < CandyCol; j++)
        {
            if (Candys[i][j]->CandyData.IsCombo == true)
            {
                Candys[i][j]->SetActive(false);
            }
        }
    }
}

void ACandyManager::ShowON()
{
    for (int i = 0; i < CandyRow; i++)
    {
        for (int j = 0; j < CandyCol; j++)
        {
            if (Candys[i][j]->CandyData.Combo >= 1)
            {
                Candys[i][j]->SetActive(true);
            }
        }
    }
}


void ACandyManager::Tick(float _DeltaTime)
{
    AActor::Tick(_DeltaTime);

    if (true == UEngineInput::IsDown('Q'))
    {

        ShowOff();
    }
    if (true == UEngineInput::IsDown('W'))
    {

        ShowON();
    }
}

