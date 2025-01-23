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
    {
        for (int row = 0; row < CandyRow; row++)
        {

            std::shared_ptr< ACandy> NewCandy = nullptr;
            for (int col = 0; col < CandyCol; col++)
            {
                //SetPos.X += CandyScale.X;
                if (false == Data[row][col].IsActive) {}
                else {
                    // ĵ�� ����
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
    // ����Ʈ�� �����Ⱚ ����
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
ACandy* ACandyManager::NewCandyCreate()
{
    ACandy* NewCandy = (GetWorld()->SpawnActor<ACandy>()).get();
    
    return NewCandy;
}

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
    return LeftBottom + float4(_Index.Y * CandyScale.Y, _Index.X * CandyScale.X);
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
                    NewData.EndPos = Data[row][col].Pos;
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
                int Index = RandomInt(1, 55);
                ACandy* NewCandy = NewCandyCreate();
                NewCandy->SetCandy({ row,col }, IndexToWorldPos({ NewCandyRow, col }), Index);

                DropData NewData;
                NewData.Candy = NewCandy;
                NewData.StartPos = NewCandy->CandyData.SetPos;
                NewData.EndPos = Data[row][col].Pos;
                DropCandy.push_back(NewData);
                
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
                for (size_t i = 0; i < DropCandy.size(); i++)
                {
                    DropCandy[i].Candy->CandyData.SetPos = FVector::Lerp(DropCandy[i].StartPos, DropCandy[i].EndPos, _Acc);
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
    /*ChangeCandyState(ECandyManagerState::Select);
    return;*/
    if (0 == DropCandy.size())
    {
        ChangeCandyState(ECandyManagerState::Update);
        return;
        
    }

   
    

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
    CandyFindConsec();

    if (true == IsCandyDestroy())
    {
        //�޺� ĵ�� �ִ�.
        ChangeCandyState(ECandyManagerState::Destroy);
        return;
    }
    if (false == IsCandyDestroy())
    {
        ChangeCandyState(ECandyManagerState::Select);
        return;
    }

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

    Candys;
}

