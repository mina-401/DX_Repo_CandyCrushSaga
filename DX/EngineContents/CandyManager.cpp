#include "PreCompile.h"
#include "CandyManager.h"   
#include <EngineCore/Level.h >
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/TimeEventComponent.h>

#include "CCSConst.h"
#include "Candy.h"
#include <queue>
#include "Mouse.h"
#include "Shine.h"
#include "BackGroundTile.h"

ACandyManager::ACandyManager()
{
    TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();
}

ACandyManager::~ACandyManager()
{
}

void ACandyManager::CreateStageBackTile()
{
    {
        for (int row = 0; row < CandyRow; row++)
        {

            for (int col = 0; col < CandyCol; col++)
            {
  
                if (false == Data[row][col].IsActive) {}
                else {
                    // 캔디 스폰
                    class ABackGroundTile* BackTile = GetWorld()->SpawnActor<ABackGroundTile>().get();             
                    BackTile->GetRenderer()->SetRelativeScale3D({CandyScale.X,CandyScale.Y,0.0f});
                    BackTile->SetActorLocation(Data[row][col].Pos);
                }
            }


        }
    }
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

    
    FVector SetPos = LeftBottom;

    Data.resize(X);
    for (int i = 0; i < X; i++)
    {
        Data[i].resize(Y);
        for (int y = 0; y < Y; y++)
        {
            Data[i][y].Pos = { SetPos.X,SetPos.Y };
            SetPos.X += CandyScale.X;
        }
        SetPos.X = LeftBottom.X;
        SetPos.Y += CandyScale.Y;
    }



    // SetPos = { -100,100 };
    

}


void ACandyManager::DeleteIndex(int X, int Y)
{
    Data[X][Y].IsActive = false;
}

void ACandyManager::CandyCreate()
{
   // CreateStageBackTile();

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
                    int RandomIndx = Random.RandomInt(1, 55);
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
            break;
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
void ACandyManager::CandyCascadeExplosion()
{

}
void ACandyManager::CandyDestroyCheck()
{
    if (false == IsCandyDestroy())
    {
        //콤보 캔디가 없다.
        ChangeCandyState(ECandyManagerState::Select);
    }
    else {
        //콤보 캔디가 있다.
        ChangeCandyState(ECandyManagerState::Destroy);
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

    
}
ACandy* ACandyManager::NewCandyCreate()
{
    ACandy* NewCandy = (GetWorld()->SpawnActor<ACandy>()).get();
    
    return NewCandy;
}

FVector ACandyManager::IndexToWorldPos(FIntPoint _Index)
{
    return LeftBottom + float4(_Index.Y * CandyScale.Y, _Index.X * CandyScale.X);
}

void ACandyManager::ChangeCandyState(ECandyManagerState _CandyState)
{

    CandyState = _CandyState;
    switch (CandyState)
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

    // 비어있는 공간 위에 있는 캔디로 채우기
    for (int col = 0; col < CandyCol; col++)
    {
        //제일 아래칸부터 시작한다
        for (int row = 0; row < CandyRow; row++)
        {
            if (false == Data[row][col].IsActive) {
                
                continue;
            }  
    
            if (nullptr == Candys[row][col])
            {
                //5 < 4+1
                if (CandyRow < row + 1)
                {
                    continue;
                }

                for (int Newrow = row + 1; Newrow < CandyRow; Newrow++)
                {
                    if (false == Data[Newrow][col].IsActive)
                    {
                        continue;
                    }

                    if (nullptr == Candys[Newrow][col])
                    {
                        continue;
                    }

                    DropData NewData;
                    NewData.Candy = Candys[Newrow][col];
                    NewData.StartPos = Data[Newrow][col].Pos;
                    NewData.EndPos = Data[row][col].Pos;
                    DropCandy.push_back(NewData);

                    //빈공간           // 존재하는 캔디 공간
                    Candys[row][col] = Candys[Newrow][col];   
                    

                    Candys[row][col]->CandyData.row = row;
                    Candys[row][col]->CandyData.col = col;
                    Candys[Newrow][col] = nullptr;
                    break;
                    
                }

            }
        }
    }
    int NewCandyRow=CandyRow;

    // 새로운 캔디를 맨위에 생성한다
    for (int row = 0; row < CandyRow; row++)
    {
        for (int col = 0; col < CandyCol; col++)
        {
            if (nullptr == Candys[row][col] && Data[row][col].IsActive == true)
            {
                int Index = Random.RandomInt(1, 79);
                ACandy* NewCandy = NewCandyCreate();
                NewCandy->SetCandy({ row,col }, IndexToWorldPos({ NewCandyRow, col }), Index);

                DropData NewData;
                NewData.Candy = NewCandy;
                NewData.StartPos = NewCandy->CandyData.SetPos;
                NewData.EndPos = Data[row][col].Pos;
                DropCandy.push_back(NewData);
                
                // 빈 공간(맨윗칸)에 캔디 넣기
                Candys[row][col] = NewCandy;

                IsDropCandy = true;                      
            }
        }
        if (IsDropCandy == true)
        {
            NewCandyRow++;
            IsDropCandy = false;
        }
    }
    
    // 빈공간애 캔디 드롭
    if (0 != DropCandy.size())
    {
        TimeEventComponent->AddUpdateEvent(CCSConst::DropTime, [this](float _Delta, float _Acc)
            {
                for (int i = 0; i < DropCandy.size(); i++)
                {
                    DropCandy[i].Candy->CandyData.SetPos = FVector::Lerp(DropCandy[i].StartPos, DropCandy[i].EndPos, _Acc * (1/CCSConst::DropTime));
                }
            });

        TimeEventComponent->AddEndEvent(CCSConst::DropTime, [this]()
            {
                DropCandy.clear();
            });
    }
}

void ACandyManager::NewCandyDrop(float _Delta)
{

    if (0 == DropCandy.size())
    {
        ChangeCandyState(ECandyManagerState::Update);
        return;
        
    }
}


void ACandyManager::PushDestroyCandy(int _row, int _col, ESpriteType SpriteType)
{
    int BottomRow = _row;
    int BottonCol = _col;

    int TopRow = _row;
    int TopCol = _col;
    
    switch (SpriteType)
    {
    case ESpriteType::Normal:
        return;
        break;
        //return;
    case ESpriteType::StripedHorizontal:
       BottomRow = _row;
       BottonCol = 0;

       TopRow = _row+1;
       TopCol = CandyCol;
        break;
    case ESpriteType::StripedVertical:
       BottomRow = 0;
       BottonCol = _col;

       TopRow = CandyRow;
       TopCol = _col+1;
        break;
    case ESpriteType::Wrapped:
        BottomRow = _row - 1;
        BottonCol = _col - 1;

       TopRow = _row + 2;
       TopCol = _col + 2;
        break;
    case ESpriteType::None:
        return;
        break;
    default:
       // return;
        break;
    }


   
    for (int row = BottomRow; row < TopRow; row++)
    {
        for (int col = BottonCol; col < TopCol; col++)
        {
            if (row < 0 || row >= CandyRow || col < 0 || col >= CandyCol)
            {
                continue;
            }
            if (Data[row][col].IsActive == false) continue;

            if ((_row == row) && (_col == col)) continue;

            DestroySpecialCandy.push_back(Candys[row][col]);

        }
    }
}

bool DestroyEnd = false;

// 캔디 부수기
void ACandyManager::CandyDestroyStart()
{
    DestroyEnd = false;
    for (ACandy* Candy : DestroyCandy)
    {
        if (Candy == nullptr) continue;
        ESpriteType SpriteType = Candy->CandyData.CandySpriteType;

        int row = Candy->CandyData.row;
        int col = Candy->CandyData.col;

        PushDestroyCandy(row, col, SpriteType);
    }
   
   

    for (ACandy* Candy : DestroyCandy)
    {
        if (Candy == nullptr) continue;
      
         class AShine* ShineEffect = GetWorld()->SpawnActor<AShine>().get();
         ShineEffect->SetActorLocation(Candy->GetActorLocation());

         Candys[Candy->CandyData.row][Candy->CandyData.col] = nullptr;
         Candy->Destroy();
         Candy = nullptr;

         TimeEventComponent->AddUpdateEvent(2.0f, [this, Candy,ShineEffect](float _Delta, float _Acc)
             {

             });
         TimeEventComponent->AddEndEvent(2.0f, [this,ShineEffect]()
             {
                 ShineEffect->Destroy();
             });
        // ShineEffectList.push_back(ShineEffect);

    }

    
    CandyClear();
    
    // 특수 캔디 폭발 범위에 캔디가 있다.
    if (0 != DestroySpecialCandy.size())
    {

        for (ACandy* Candy : DestroySpecialCandy)
        {
            DestroyCandy.push_back(Candy);
        }
        DestroySpecialCandy.clear();
        CandyDestroyStart();
   


    }

    TimeEventComponent->AddEndEvent(2.0f, [this]()
    {
        DestroyEnd = true;
        });
   
}



void ACandyManager::CandyDestroy()
{
    if (false == DestroyEnd)
    {
        return;
    }
    // 부술 캔디가 없다.
    if (false == IsCandyDestroy() && 0 == DestroySpecialCandy.size())
    {
        ChangeCandyState(ECandyManagerState::NewCandyDrop);
        return;
    }
}

void ACandyManager::UpdateStart()
{
    //연속하는 캔디 찾음
    CandyFindConsec();

    // 부술 캔디를 확인
}
void ACandyManager::Update(float _DeltaTime)
{
    CandyDestroyCheck();

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

