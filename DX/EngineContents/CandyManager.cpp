#include "PreCompile.h"
#include "CandyManager.h"   
#include <EngineCore/Level.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "CCSConst.h"
#include "Candy.h"
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

void ACandyManager::ColCheck(int X, int Y)
{


    std::list<ACandy*> CandyList;
    EColor CurColor = Candys[X][Y]->CandyData.CandyColor;

    int col = Y;
    CandyList.push_back(Candys[X][Y]); // 맨 처음 기준이 되는 캔디 보관

    for (int row = X; row < CandyRow; row++)
    {
        if (X == row) {
            continue;

        }
       ACandy* Target = Candys[row][col];
       EColor DiffColor= Target->CandyData.CandyColor;

       if (CurColor == DiffColor)
       {
           CandyList.push_back(Target);
           CandyCombo.Combo++;
       }
       else
       {
           if (false == CandyList.empty())
           {
               // 1,2개만 연속해서 연결되 있다.

               if (CCSConst::Combo > CandyCombo.Combo)
               {
                   if (false == CandyList.empty())
                   {
                       CandyList.clear();
                   }
               }
               else
               {
                   for (ACandy* candy : CandyList)
                   {
                       if (std::find(DestroyCandy.begin(), DestroyCandy.end(), Candys[X][Y]) == DestroyCandy.end()) {
                           //3개 연속해서 연결됬으면 삭제캔디 리스트에 추가한다.

                           DestroyCandy.push_back(candy);
                       }
                   }
               }
               CandyCombo.Combo = 0;
           }
           

       }
    }
   /* if (false == CandyList.empty())
    {
        for (ACandy* candy : CandyList)
        {
            if (std::find(DestroyCandy.begin(), DestroyCandy.end(), Candys[X][Y]) == DestroyCandy.end()) {

                DestroyCandy.push_back(candy);

            }
        }
    }*/
}
void ACandyManager::RowCheck(int X, int Y)
{
    
    std::list<ACandy*> CandyList;

    ACandy* DiffTarget = nullptr;
    ACandy* CurTarget = Candys[X][Y];
    EColor CurColor = CurTarget->CandyData.CandyColor;

    int row = X;

    for (int col = Y; col < CandyCol; col++)
    {
        if (Y == col) continue;

        DiffTarget = Candys[row][col];
        EColor DiffColor = DiffTarget->CandyData.CandyColor;

        if (CurColor == DiffColor)
        {
            CandyList.push_back(DiffTarget);
            CandyCombo.Combo++;
        }
        else
        {
            // 비교 색깔이 다르다.  
            if (false == CandyList.empty())
            {
                // 1,2개만 연속해서 연결되 있다.

                if (CCSConst::Combo > CandyCombo.Combo)
                {
                   CandyList.clear();  
                }
                else
                {
                    for (ACandy* candy : CandyList)
                    {
                        if (std::find(DestroyCandy.begin(), DestroyCandy.end(), Candys[X][Y]) == DestroyCandy.end()) {
                            //3개 연속해서 연결됬으면 삭제캔디 리스트에 추가한다.

                            DestroyCandy.push_back(candy);

                        }
                    }
                }
                CandyCombo.Combo = 0;
            }
           

        }

        CurTarget = Candys[row][col];
        
    }
 /*   if (false == CandyList.empty())
    {
        for (ACandy* candy : CandyList)
        {
            if (std::find(DestroyCandy.begin(), DestroyCandy.end(), Candys[X][Y]) == DestroyCandy.end()) {

                DestroyCandy.push_back(candy);

            }
        }
    }*/
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

    int a = DestroyCandy.size();

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

