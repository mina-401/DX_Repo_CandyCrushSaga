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

    
    FVector SetPos = LeftTop;

    Data.resize(X);
    for (int i = 0; i < X; i++)
    {
        Data[i].resize(Y);
        for (int y = 0; y < Y; y++)
        {
            Data[i][y].Pos = { (SetPos.X),SetPos.Y };
            SetPos.X += CandyScale.X;
        }
        SetPos.X = LeftTop.X;
        SetPos.Y -= CandyScale.Y;
    }

    // SetPos = { -100,100 };
    

}


void ACandyManager::DeleteIndex(int X, int Y)
{
    Data[X][Y].IsActive = false;
}

void ACandyManager::CandyCreate()
{
    {
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

FVector ACandyManager::IndexToWorldPos(FIntPoint _Index)
{
    return LeftTop + float4(_Index.X * CandyScale.X, -_Index.Y * CandyScale.Y);
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

FIntPoint TopIndexCheck()
{
    return FIntPoint();
}

void ACandyManager::NewCandyDropStart()
{
    //ChangeCandyState(ECandyManagerState::Move);
 
    /*if (0 == Empty.size())
    {
        ChangeCandyState(ECandyManagerState::Select);
        return;
    }


    Empty.clear();*/

    for (int col = 0; col < CandyCol; col++)
    {
        //제일 아래칸부터 시작한다
        for (int row = CandyRow - 1; row >= 0; row--)
        {
            if (false == Data[row][col].IsActive) {
                
                continue;
            }
    
            if (nullptr == Candys[row][col])
            {
                if (0 > row - 1)
                {
                    continue;
                }

                for (int Newrow = row - 1; Newrow >= 0; Newrow--)
                {
                    if (false == Data[Newrow][col].IsActive)
                    {
                        continue;
                    }

                    if (nullptr == Candys[Newrow][col])
                    {
                        continue;
                    }


                    // Candys[row][col]->CandyData.SetPos = Data[row][col].Pos;
                    DropData NewData;
                    NewData.Candy = Candys[Newrow][col];
                    NewData.StartPos = Data[Newrow][col].Pos;
                    NewData.EndPos = Data[row][col].Pos;
                    DropCandy.push_back(NewData);

                    Candys[row][col] = Candys[Newrow][col];                  
                    Candys[Newrow][col] = nullptr;
                    break;
                    
                }

            }
        }
    }



    for (int col = 0; col < CandyCol; col++)
    {
        //제일 아래칸부터 시작한다
        for (int row = CandyRow - 1; row >= 0; row--)
        {
            if (nullptr == Candys[row][col] && Data[row][col].IsActive == true)
            {
                int Index = RandomInt(1, 55);
                ACandy* NewCandy = NewCandyCreate();
                NewCandy->SetCandy({ row,col }, IndexToWorldPos({-1, col  }), Index);
            }
        }
    }


    if (0 != DropCandy.size())
    {
        TimeEventComponent->AddUpdateEvent(1.0f, [this](float _Delta, float _Acc)
            {
                for (size_t i = 0; i < DropCandy.size(); i++)
                {
                    DropCandy[i].Candy->CandyData.SetPos = FVector::Lerp(DropCandy[i].StartPos, DropCandy[i].EndPos, _Acc);
                }
            });

        TimeEventComponent->AddEndEvent(1.0f, [this]()
            {
                DropCandy.clear();
            });
    }

}

void ACandyManager::NewCandyDrop(float _Delta)
{
    if (0 == DropCandy.size())
    {
        int a = 0;
    }

    //if (드랍이 끝날때까지 기다리다)
    //{
    //}

    int a = 0;
    //for (int row = 0; row < Candys.size(); row++)
    //{
    //    for (int col = CandyCol; col < Candys[row].size(); col++)
    //    {
    //        if (nullptr != Candys[row][col])
    //        {
    //            ACandy* NewCandy = Candys[row][col];
    //            FIntPoint TargetIndex = NewCandy->CandyData.TargetIndex;
    //            FVector Dir = Data[TargetIndex.X][TargetIndex.Y].Pos;
    //            Dir.Normalize();
    //            //FIntPoint Pos = Candys[]

    //            NewCandy->SetActorLocation(Dir * DropSpeed * _Delta);
    // 
    // 
    //        }

    //    }

    //}

    //ChangeCandyState(ECandyManagerState::Update);
     ChangeCandyState(ECandyManagerState::Select);
    return;

   
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
void ACandyManager::Update(float _DeltaTime)
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
       // Empty.push_back({ Candy->CandyData.row,Candy->CandyData.col });

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
        NewCandyDrop(_DeltaTime);

        break;
    case ECandyManagerState::Update:
        Update(_DeltaTime);

        break;
    default:
        break;
    }

}

