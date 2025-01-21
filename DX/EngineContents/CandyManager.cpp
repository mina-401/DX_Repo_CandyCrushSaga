#include "PreCompile.h"
#include "CandyManager.h"   
#include <EngineCore/Level.h >
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>

#include "CCSConst.h"
#include "Candy.h"
#include <queue>
#include "Mouse.h"
#include <EngineCore/TimeEventComponent.h>


ACandyManager::ACandyManager()
{
    TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
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
        for (int y = 0; y < Y; y++)
        {
            Data[i][y].Pos = { (SetPos.X += CandyScale.X),SetPos.Y };
        }
        SetPos.X = -100;
        SetPos.Y -= CandyScale.Y;
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
        //FVector SetPos = { -100,100 };
        for (int row = 0; row < CandyRow; row++)
        {

            std::shared_ptr< ACandy> NewCandy = nullptr;
            for (int col = 0; col < CandyCol; col++)
            {
                //SetPos.X += CandyScale.X;
                if (false == Data[row][col].IsActive) {}
                else {
                    // 캔디 스폰
                    int RandomIndx = RandomInt(1, 55);
                    FIntPoint Index = { row,col };
                    NewCandy = GetWorld()->SpawnActor<ACandy>();
                    NewCandy->SetCandy(Index, Data[row][col].Pos, RandomIndx);

                    Candys[row][col] = NewCandy.get();
                }
            }
           // SetPos.X = -100;
            //SetPos.Y -= CandyScale.Y;


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

        if (nullptr == CurTarget || nullptr == DiffTarget)
        {
            continue;
        }

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
        if (nullptr == CurTarget || nullptr == DiffTarget)
        {
            continue;
        }
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
    // 리스트에 쓰레기값 들어옴
    return DestroyCandy.size() !=0 ? true : false ;
}
void ACandyManager::CandyFindConsec()
{ 
    CandyClear();

    for (int row = 0; row < CandyRow; row++)
    {
        for (int col = 0; col < CandyCol; col++)
        {
            if (false == Data[row][col].IsActive) //빈자리는 체크 안함
            {
                continue;
            }
            
            RowCheck(row, col);
            ColCheck(row, col);
        }
    }

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
    // row, col 바꾸기
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
    //DestroyCandy.resize(0);
}
ACandy* ACandyManager::NewCandyCreate()
{
    ACandy* NewCandy = (GetWorld()->SpawnActor<ACandy>()).get();
    
    return NewCandy;
}
//void ACandyManager::CandyDropAt(ACandy* candy, FVector pos) {
//
//    Candys[pos.X][pos.Y] = candy; 
//    candy->SetPos(pos.X, pos.Y); 
//
//}
void ACandyManager::CandyPlaceAt(int EmptyRow, int Col)
{
    int row = EmptyRow;
    int col = Col;
    while (row >= 0)
    {

        if (Data[row][col].IsActive == false) {}
        else {
            ACandy* NewCandy = NewCandyCreate();
            int RandSpriteIndex = RandomInt(1, 55);
            NewCandy->SetCandy({ row,col }, Data[row][col].Pos, RandSpriteIndex);

            Candys[row][col] = NewCandy;
        }
        row--;
    }
}

void ACandyManager::ChangeCandyState(ECandyManagerState _CandyState)
{

    CandyState = _CandyState;
    switch (_CandyState)
    {
    case ECandyManagerState::Select:
        break;
    case ECandyManagerState::Move:
        break;
    case ECandyManagerState::Destroy:
        CandyDestroyStart();
        break;
    case ECandyManagerState::NewCandyDrop:
        NewCandyDropStart();
        break;
    case ECandyManagerState::Update:
        UpdateStart();
        break;
    default:
        break;
    }

}
void ACandyManager::NewCandyDropStart()
{

 
    if (0 == Empty.size())
    {
        ChangeCandyState(ECandyManagerState::Select);
        return;
    }

    for (int i = 0; i < Empty.size(); i++)
    {

       //int SpriteIndex = RandomInt(1, 55);
       int SpriteIndex =0;

       FIntPoint TargetIndex = Empty[i]; //터질 캔디의 인덱스
       FVector Pos = Data[0][TargetIndex.Y].Pos; // 위치

       {
           int NewX = (CandyRow-1) - TargetIndex.X ; //뉴캔디 인덱스

           int X = TargetIndex.X;
           int Y = static_cast<int>(Candys[X].size());

 
           Pos.Y += static_cast<float>(CandyScale.Y * (NewX + 1)); // 뉴캔디 위치

           ACandy* NewCandy = NewCandyCreate();
           {
               StageCandyData StageCandy;

               StageCandy.IsActive = true;
               StageCandy.Pos = Pos;

               Data[X].push_back(StageCandy);
           }

           NewCandy->SetCandy({ X,Y }, Pos, SpriteIndex);

           Candys[X].push_back(NewCandy);
       }

       //{
       //   ACandy* NewCandy = NewCandyCreate();
       //    int X = static_cast<int>(Candys.size()); //3
       //    int Y = TargetIndex.Y; // 1

 
       //    int EXCandy = X - CandyRow ;

       //    
       //    Pos.Y += static_cast<int>(CandyScale.Y * (EXCandy+1));
       //    
       //    {
       //        StageCandyData StageCandy;
       //        StageCandy.IsActive = true;
       //        StageCandy.Pos = Pos; 

       //        if (X >= Data.size())
       //        {
       //             Data.resize(X+1); // X 인덱스에 해당하는 벡터를 생성

       //            if (Data[X].empty())
       //            {
       //                Data[X].resize(CandyCol);
       //            }
       //        }

       //        Data[X][Y] = StageCandy;
       //    }

       //    if (X >=Candys.size() )
       //    {
       //       Candys.resize(X+1); // X 인덱스에 해당하는 벡터를 생성
       //       if (Candys[X].empty())
       //       {
       //           Candys[X].resize(CandyCol);
       //       }
       //    }
       //     
       //    NewCandy->SetCandy({ X,Y }, Pos, SpriteIndex);
       //    Candys[X][Y] = NewCandy;
       //}
       
    }

    Empty.clear();
}

void ACandyManager::NewCandyDrop()
{
    ChangeCandyState(ECandyManagerState::Select);
    return;
    //ChangeCandyState(ECandyManagerState::Move);

    //int EmptyRow = -1;

    //for (int col = 0; col < CandyCol; col++)
    //{
    //    //제일 아래칸부터 시작한다
    //    for (int row = CandyRow - 1; row >= 0; row--)
    //    {
    //        if (false == Data[row][col].IsActive) {
    //            
    //            continue;
    //        }

    //        if (nullptr == Candys[row][col])
    //        {
    //            // 처음으로 비어있는 칸
    //            if(-1 == EmptyRow) EmptyRow = row;
    //        }

    //        else if (-1 != EmptyRow)
    //        {
    //            Candys[EmptyRow][col] = Candys[row][col];

    //           // 위에서 가장 가까운 캔디, 아래로 내린다.
    //           /*TimeEventComponent->AddUpdateEvent(CCSConst::MoveTime, [this, EmptyRow,row,col](float _Delta, float _Acc)
    //            { */ 

    //                //FVector StartPos = Data[row][col].Pos;
    //               // FVector EndPos = Data[EmptyRow][col].Pos;

    //              // Candys[EmptyRow][col]->GetCandyData().SetPos = FVector::Lerp(StartPos, EndPos, _Acc * 1 / CCSConst::MoveTime);
    //            //});

    //            //TimeEventComponent->AddEndEvent(CCSConst::MoveTime, [this, EmptyRow,row, col]()
    //            //{
    //                Candys[EmptyRow][col]->CandyData.row = EmptyRow;
    //                Candys[EmptyRow][col]->CandyData.col = col;
    //                Candys[EmptyRow][col]->CandyData.SetPos= Data[EmptyRow][col].Pos;
    //                Candys[row][col] = nullptr;


    //           //});

    //            EmptyRow -= 1;

    //        }
    //    }

    //   if (-1 != EmptyRow) {


    //       // 비어있는 칸에 배치
    //       CandyPlaceAt(EmptyRow,col);
    //       

    //    }
    //    EmptyRow = -1;
    //}

    //CandyFindConsec();

    //if (false == IsCandyDestroy())
    //{
    //    ChangeCandyState(ECandyManagerState::Select);
    //    return;
    //}
    //else
    //{
    //    ChangeCandyState(ECandyManagerState::Destroy);
    //    return;
    //}

    //ChangeCandyState(ECandyManagerState::Select);
   //return;
}
void ACandyManager::UpdateStart()
{

}
void ACandyManager::CandyDestroyStart()
{
    //
}
void ACandyManager::CandyDestroy()
{
    for (ACandy* Candy : DestroyCandy)
    {
        Empty.push_back({ Candy->CandyData.row,Candy->CandyData.col });

        Candys[Candy->CandyData.row][Candy->CandyData.col] = nullptr;
        Candy->Destroy();
        Candy = nullptr;
    }

    CandyClear();
    ChangeCandyState(ECandyManagerState::NewCandyDrop);
    return;
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
        NewCandyDrop();
        break;
    default:
        break;
    }
}

