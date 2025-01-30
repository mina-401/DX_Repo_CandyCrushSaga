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
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/FontRenderer.h>
#include "ScoreActor.h"

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
                    // ĵ�� ����
                    class ABackGroundTile* BackTile = GetWorld()->SpawnActor<ABackGroundTile>().get();             
                    BackTile->GetRenderer()->SetRelativeScale3D({CandyScale.X,CandyScale.Y,0.0f});

                    FVector BackTilePos = Data[row][col].Pos;
                    BackTilePos.Z = 0.0f;
                    BackTile->SetActorLocation(BackTilePos);
                    
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
            Data[i][y].Pos = { SetPos.X,SetPos.Y};
            SetPos.X += CandyScale.X;
        }
        SetPos.X = LeftBottom.X;
        SetPos.Y += CandyScale.Y;
    }

}


void ACandyManager::DeleteIndex(int X, int Y)
{
    Data[X][Y].IsActive = false;
}
ACandy* ACandyManager::NewCandyCreate(int row,int col)
{
    int RandomIndx = Random.RandomInt(1, 78);
    ACandy* NewCandy = GetWorld()->SpawnActor<ACandy>().get();
    FVector CandyPos = Data[row][col].Pos;
    NewCandy->SetCandy({row,col}, CandyPos, RandomIndx);

    return NewCandy;
}
ACandy* ACandyManager::NewCandyCreate(int row, int col,FVector Pos)
{
    int RandomIndx = Random.RandomInt(1, 78);
    ACandy* NewCandy = GetWorld()->SpawnActor<ACandy>().get();
    FVector CandyPos = Pos + FVector(0,0,-100);
    NewCandy->SetCandy({ row,col }, CandyPos, RandomIndx);

    return NewCandy;
}
void ACandyManager::CandyCreate()
{

    {
        for (int row = 0; row < CandyRow; row++)
        {

            ACandy* NewCandy = nullptr;
            for (int col = 0; col < CandyCol; col++)
            {
                if (false == Data[row][col].IsActive) {}
                else {
                    // ĵ�� ����
                   
                    NewCandy = NewCandyCreate(row, col);

                    Candys[row][col] = NewCandy;
                }
            }


        }
    }
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

    // 3�� �̻��� �޺��� �߻��� ��쿡�� DestroyCandy�� �߰�
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
            break; // ������ �ٸ��� ���� ����
        }

        CurTarget = Candys[row][col];
    }

    // 3�� �̻��� �޺��� �߻��� ��쿡�� DestroyCandy�� �߰�
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
            if (false == Data[row][col].IsActive) //���ڸ��� üũ ����
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

    //�ڷ� �ٲٱ�
 
    //ĵ�� ���� ��ġ �ٲٱ�
    Candys[SelectCandyData.row][SelectCandyData.col] = CurCandy;
    Candys[CurCandyData.row][CurCandyData.col] = SelectCandy;

    //setpos�� ������ �� �ٲ��� ���� ����
    // row, col �ٲٱ�
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
void ACandyManager::ClearCandys()
{
    for (int x = 0; x < CandyRow; x++)
    {
        for (int y = 0; y < CandyCol; y++)
        {
            if (Data[x][y].IsActive == false) continue;

            Candys[x][y]->Destroy();
           // Candys[x][y] = nullptr;
        }
    }

}
void ACandyManager::ResetCandyBoard()
{

    ClearCandys(); // ĵ���� ���� ����
    CandyCreate(); // ĵ�� �ٽ� ����
    CandyFindConsec(); // �޺�ĵ�� ã��
    CandyDestroyCheck(); // ���� ���� ����.
    
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
    IsCandyDrop = false;
    // ����ִ� ���� ���� �ִ� ĵ��� ä���
    for (int col = 0; col < CandyCol; col++)
    {
        //���� �Ʒ�ĭ���� �����Ѵ�
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
                    NewData.StartPos.Z = -100.0f;

                    NewData.EndPos = Data[row][col].Pos;
                    NewData.EndPos.Z = -100.0f;

                    DropCandy.push_back(NewData);

                    //�����           // �����ϴ� ĵ�� ����
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

    // ���ο� ĵ�� ������ �����Ѵ�
    for (int row = 0; row < CandyRow; row++)
    {
        for (int col = 0; col < CandyCol; col++)
        {
            if (nullptr == Candys[row][col] && Data[row][col].IsActive == true)
            {
                int Index = Random.RandomInt(1, 78);
                FVector Pos = IndexToWorldPos({ NewCandyRow, col });
                ACandy* NewCandy = NewCandyCreate(row,col,Pos);


                DropData NewData;
                NewData.Candy = NewCandy;
                NewData.StartPos = NewCandy->CandyData.SetPos;
                NewData.EndPos = Data[row][col].Pos;
                NewData.EndPos.Z = -100.0f;
                DropCandy.push_back(NewData);
                
                // �� ����(����ĭ)�� ĵ�� �ֱ�
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
    
    // ������� ĵ�� ���
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

                TimeEventComponent->AddEndEvent(CCSConst::DropTime, [this]()
                    {
                        IsCandyDrop = true;
                    });
            });
    }
}

void ACandyManager::NewCandyDrop(float _Delta)
{

    if (IsCandyDrop == false) return;
  
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
            ACandy* Cur = Candys[row][col];
            if (Cur == nullptr)
            {
                continue;
            }
            DestroySpecialCandy.push_back(Candys[row][col]);

        }
    }  
}




// ĵ�� �μ���
void ACandyManager::CandyDestroyStart()
{
    DestroyEnd = false;

    ComboCount++;

    for (ACandy* Candy : DestroyCandy)
    {
        if (Candy == nullptr) continue;
        ESpriteType SpriteType = Candy->CandyData.CandySpriteType;

        int row = Candy->CandyData.row;
        int col = Candy->CandyData.col;

        PushDestroyCandy(row, col, SpriteType);
    }
   
   
    EColor PrevColor = EColor::None;
    EColor CurColor = EColor::None;

    int Combo = 1;
    IsCombo = false;
    for (ACandy* Candy : DestroyCandy)
    {
        if (Candy == nullptr) continue;
      
        CurColor = Candy->CandyData.CandyColor;

        // �޺� ī��Ʈ
        
        if (PrevColor != EColor::None && PrevColor == CurColor)
        {
            Combo++;
            //IsCombo = true;
        }
        else {
            Combo = 1;

        }

        // ĵ�� ��������Ʈ ��翡 ���� �⺻ ���� ����Ѵ�.
        BasicPlayerStateScore(Candy);

      
            // 3�޺� ����Ʈ
       

        // �����ؼ� �μ����� ĵ�� �����Ѵ�.
        if (ComboCount >= 2)
        {
            AScoreActor* ScoreActor = GetWorld()->SpawnActor< AScoreActor>().get();
            ScoreActor->SetActorLocation({ -100,100,-200 });
            //ScoreActor->SetActorRelativeScale3D({ 500,500,1 });
            switch (ComboCount)
            {
            case 2:
                ScoreActor->SetSprite(3);
                break;
            case 3:
                ScoreActor->SetSprite(2);

                break;
            case 4:
                ScoreActor->SetSprite(1);

                break;
            
            default:
                break;
            }
            //AScoreActor* ScoreActor = GetWorld()->SpawnActor< AScoreActor>().get();


            GetGameInstance<CandyGameInstance>()->PlayerStat.Score += BonusScore*ComboCount;
        }

            //�⺻����       

       

        PrevColor = CurColor;
        // 
         //class AShine* ShineEffect = GetWorld()->SpawnActor<AShine>().get();
        // ShineEffect->SetActorLocation(Candy->GetActorLocation());
         Candys[Candy->CandyData.row][Candy->CandyData.col] = nullptr;
         Candy->Destroy();
         Candy = nullptr;
           
        /* TimeEventComponent->AddUpdateEvent(2.0f, [this, Candy,ShineEffect](float _Delta, float _Acc)
             {
                
             });
         TimeEventComponent->AddEndEvent(2.0f, [this,ShineEffect]()
             {
                 ShineEffect->Destroy();
             });*/
        // ShineEffectList.push_back(ShineEffect);

    }

    
    CandyClear();

    if (0 != DestroySpecialCandy.size())
    {

      for (ACandy* Candy : DestroySpecialCandy)
      {
          DestroyCandy.push_back(Candys[Candy->CandyData.row][Candy->CandyData.col]);
      }
      DestroySpecialCandy.clear();

       TimeEventComponent->AddEndEvent(1.0f, [this]()
       {
          CandyDestroyStart();
       });

        
    }
    else {
        // combo count �ʱ�ȭ
        TimeEventComponent->AddEndEvent(1.0f, [this]()
        {
            DestroyEnd = true;
            ComboCount = 0;

        });
    }
}


void ACandyManager::BasicPlayerStateScore(ACandy* Candy)
{
    switch (Candy->CandyData.CandySpriteType)
    {
    case ESpriteType::Normal:
        GetGameInstance<CandyGameInstance>()->PlayerStat.Score += 10;

        break;
    case ESpriteType::StripedHorizontal:
        GetGameInstance<CandyGameInstance>()->PlayerStat.Score += 30;

        break;
    case ESpriteType::StripedVertical:
        GetGameInstance<CandyGameInstance>()->PlayerStat.Score += 30;

        break;
    case ESpriteType::Wrapped:
        GetGameInstance<CandyGameInstance>()->PlayerStat.Score += 50;

        break;
    case ESpriteType::None:
        break;

    default:
        break;
    }
}



void ACandyManager::CandyDestroy()
{
    if (false == DestroyEnd)
    {
        return;
    }
    // �μ� ĵ�� ����.
    if (false == IsCandyDestroy() && 0 == DestroySpecialCandy.size())
    {
        ChangeCandyState(ECandyManagerState::NewCandyDrop);
        return;
    }
}

void ACandyManager::UpdateStart()
{
    //�����ϴ� ĵ�� ã��
    CandyFindConsec();

    // �μ� ĵ�� Ȯ��
}

void ACandyManager::CandyDestroyCheck()
{
    if (false == IsCandyDestroy())
    {
        //�޺� ĵ�� ����.
        ChangeCandyState(ECandyManagerState::Select);
        return;
    }
    else {
        //�޺� ĵ�� �ִ�.
        ChangeCandyState(ECandyManagerState::Destroy);
        return;
    }

}
void ACandyManager::CandyDisableCheck()
{
    if (false == IsCandyDestroy()  && (GetGameInstance<CandyGameInstance>()->CandyMouseCon.IsTransEnd == true))
    {
        // �̵��� ��.
        ChangeCandyState(ECandyManagerState::Disable);
        return;
    }
}
void ACandyManager::Update(float _DeltaTime)
{
    CandyDestroyCheck();

    CandyDisableCheck();
}
void ACandyManager::DisableStart()
{
    //������ ĵ�� �μ���
    CandyFindConsec();
    if (false == IsCandyDestroy())
    {
        //�޺� ĵ�� ����.
        
    }
    else {
        //�޺� ĵ�� �ִ�.
        ChangeCandyState(ECandyManagerState::Destroy);
        return;
    }

    //�̵�Ƚ�� �������� ���ӳ�
}
void ACandyManager::Disable(float _DeltaTime)
{
    // ���콺�� ������ �� ���� ���.
    // ������ Ƚ���� ������ ������ ������.
    // 
}

void ACandyManager::BeginPlay()
{
    AActor::BeginPlay();



}
void ACandyManager::Tick(float _DeltaTime)
{
    AActor::Tick(_DeltaTime);

    if (UEngineInput::IsDown('R') == true)
    {
        ResetCandyBoard();
    }

    
 
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
    case ECandyManagerState::Disable:
        Disable(_DeltaTime);

        break;
    default:
        break;
    }

}

