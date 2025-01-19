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

    FVector SetPos = { -100,100 };
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
                    // ĵ�� ����
                    int RandomIndx = RandomInt(1, 55);
                    FVector Index = { row,col };
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
    //DestroyCandy.resize(0);
}
ACandy* ACandyManager::NewCandyCreate()
{
    ACandy* NewCandy = (GetWorld()->SpawnActor<ACandy>()).get();
    
    return NewCandy;
}
void ACandyManager::CandyDropAt(ACandy* candy, const FVector pos) {

    Candys[pos.X][pos.Y] = candy; 
    candy->SetPos(pos.X, pos.Y); 

}
void ACandyManager::NewCandyDrop()
{
    int EmptyRow = -1;


    for (int col = 0; col < CandyCol; col++)
    {
        //���� �Ʒ�ĭ���� �����Ѵ�
        for (int row = CandyRow - 1; row >= 0; row--)
        {
            if (false == Data[row][col].IsActive) {
                
                continue;
            }

            if (nullptr == Candys[row][col])
            {
                // ó������ ����ִ� ĭ
                if(-1 == EmptyRow) EmptyRow = row;
            }

            else if (-1 != EmptyRow)
            {

               // ������ ���� ����� ĵ��, �Ʒ��� ������.
                Candys[EmptyRow][col] = Candys[row][col];
                TimeEventComponent->AddUpdateEvent(CCSConst::MoveTime, [this, EmptyRow,row,col](float _Delta, float _Acc)
                {
                    ChangeCandyState(ECandyManagerState::Move);
                    

                    FVector StartPos = Data[row][col].Pos;
                    FVector EndPos = Data[EmptyRow][col].Pos;

                    Candys[EmptyRow][col]->GetCandyData().SetPos = FVector::Lerp(StartPos, EndPos, _Acc * 1 / CCSConst::MoveTime);
                });

                TimeEventComponent->AddEndEvent(CCSConst::MoveTime, [this, EmptyRow,row, col]()
                {
                    
                    Candys[EmptyRow][col]->CandyData.row = EmptyRow;
                    Candys[EmptyRow][col]->CandyData.col = col;

                    Candys[row][col] = nullptr;
                });

                EmptyRow -= 1;

            }
        }

        if (-1 != EmptyRow) {

            int row = EmptyRow;
            while (row >= 0)
            {

                if (Data[row][col].IsActive == false) {}
                else {
                    ACandy* NewCandy = NewCandyCreate();
                    int RandSpriteIndex = RandomInt(1, 55);
                    NewCandy->SetCandy({ row,col }, Data[row][col].Pos, 0);

                    Candys[row][col] = NewCandy;
                }
                row--;
            }

        }
        EmptyRow = -1;
    }


    //CandyFindConsec();
    //

    //if (false == IsCandyDestroy())
    //{
    //    //�޺� ĵ�� ����.
    //   

    //   
    //}

    //else {
    //    //�޺� ĵ�� �ִ�.
    //    ChangeCandyState(ECandyManagerState::Destroy);
    //}
    

    ChangeCandyState(ECandyManagerState::Select);
    return;

}
void ACandyManager::CandyDestroy()
{
    
    
    for (ACandy* Candy : DestroyCandy)
    {
      //  DestroyCandyList.push_back({ Candy->CandyData.row,Candy->CandyData.col });
        Candys[Candy->CandyData.row][Candy->CandyData.col] = nullptr;
        Candy->Destroy();
        Candy = nullptr;

        
        
    }
    
    CandyClear();
    ChangeCandyState(ECandyManagerState::NewCandyDrop);
    return;
    //ChangeCandyState(ECandyManagerState::Select);

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

