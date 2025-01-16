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
#include "Mouse.h"


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


    int Combo = 0;
    std::list<ACandy*> CandyList;

    ACandy* CurTarget = Candys[X][Y];
    ACandy* DiffTarget = nullptr;

    CandyList.push_back(CurTarget);

    int col = Y;
    for (int row = X; row < CandyRow; row++)
    {
        if (X == row) continue;

        DiffTarget = Candys[row][col];

        EColor CurColor = CurTarget->CandyData.CandyColor;
        EColor DiffColor = DiffTarget->CandyData.CandyColor;

        if (CurColor == DiffColor)
        {
            CandyList.push_back(DiffTarget);
            Combo++;
        }
        else
        {
            break; // 색상이 다르면 루프 종료
        }

        CurTarget = Candys[row][col];
    }

    // 3개 이상의 콤보가 발생한 경우에만 DestroyCandy에 추가
    if (Combo >= CCSConst::Combo)
    {
        for (ACandy* candy : CandyList)
        {
            if (std::find(DestroyCandy.begin(), DestroyCandy.end(), candy) == DestroyCandy.end()) {
                DestroyCandy.push_back(candy);
            }
        }
    }
}
void ACandyManager::RowCheck(int X, int Y)
{
    int Combo = 0;
    std::list<ACandy*> CandyList;

    ACandy* CurTarget = Candys[X][Y];
    ACandy* DiffTarget = nullptr;

    CandyList.push_back(CurTarget);

    int row = X;

    for (int col = Y; col < CandyCol; col++)
    {
        if (Y == col) continue;

        DiffTarget = Candys[row][col];

        EColor CurColor = CurTarget->CandyData.CandyColor;
        EColor DiffColor = DiffTarget->CandyData.CandyColor;

        if (CurColor == DiffColor)
        {
            CandyList.push_back(DiffTarget);
            Combo++;
        }
        else
        {
            break; // 색상이 다르면 루프 종료
        }

        CurTarget = Candys[row][col];
    }

    // 3개 이상의 콤보가 발생한 경우에만 DestroyCandy에 추가
    if (Combo >= CCSConst::Combo)
    {
        for (ACandy* candy : CandyList)
        {
            if (std::find(DestroyCandy.begin(), DestroyCandy.end(), candy) == DestroyCandy.end()) {
                DestroyCandy.push_back(candy);
            }
        }
    }
}

bool ACandyManager::IsCandyDestroy()
{
    // 
    return DestroyCandy.size() !=0 ? true : false ;
}
void ACandyManager::CandyFindConsec()
{ 
    for (int row = 0; row < CandyRow; row++)
    {
        for (int col = 0; col < CandyCol; col++)
        {
            if (false == Data[row][col].IsActive)
            {
                continue;
            }
            RowCheck(row, col);
            ColCheck(row, col);
        }
    }

    int a = DestroyCandy.size();
}
void ACandyManager::CandyChange(class ACandy* SelectCandy, class ACandy* CurCandy)
{
    FCandySpriteData& SelectCandyDataRef = SelectCandy->GetCandyData();
    FCandySpriteData& CurCandyDataRef = CurCandy->GetCandyData();


    FCandySpriteData SelectCandyData = SelectCandy->CandyData;
    FCandySpriteData CurCandyData = CurCandy->CandyData;

    //자료 바꾸기
 
    //캔디 보드 위치 바꾸기
    Candys[SelectCandyData.row][SelectCandyData.col] = CurCandy;
    Candys[CurCandyData.row][CurCandyData.col] = SelectCandy;

    //setpos를 제외한 건 바뀌지 않은 상태
    SelectCandyDataRef.row = CurCandyData.row;
    SelectCandyDataRef.col = CurCandyData.col;
    SelectCandyDataRef.SetPos = SelectCandyData.SetPos;
    CurCandyDataRef.row = SelectCandyData.row;
    CurCandyDataRef.col = SelectCandyData.col;
    CurCandyDataRef.SetPos = CurCandyData.SetPos;

}
void ACandyManager::CandyClear()
{
    DestroyCandy.clear();
}
void ACandyManager::CandyDestroy()
{
    
    
    for (ACandy* Candy : DestroyCandy)
    {
        Candy->Destroy();

        /*int row = Candy->CandyData.row;
        int col = Candy->CandyData.col;*/  
        //ACandy* AboveCandy = Candys[row-1][col];
        //Candys[]

       // Candy->SetActive(false);

        
    }
    
    CandyClear();

    //int dx[4] = { 1, 0, -1, 0 };
   //int dy[4] = { 0, 1, 0, -1 };

   //std::list<ACandy*> DestroyCandy;
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



void ACandyManager::Tick(float _DeltaTime)
{
    AActor::Tick(_DeltaTime);

    switch (CandyState)
    {
    case ECandyManagerState::Select:
        break;
    case ECandyManagerState::Move:
        break;
    case ECandyManagerState::Destroy:
        CandyDestroy();
        break;
    case ECandyManagerState::NewCandyDrop:
        break;
    default:
        break;
    }
}

