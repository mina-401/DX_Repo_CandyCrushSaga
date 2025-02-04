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
#include "CCSHUD.h"

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
                    // 캔디 스폰
                   
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

bool ACandyManager::RowCheckInProgress(int X, int Y)
{
    bool Combo = false;
  

    int dx[8] = {-1,1,1,-1,1,-1,0,0};

    int row = X;
    int col = Y;
    int Nextcol = Y+1;
    int NextNextcol = Y+2;


     
    if (col >= CandyCol || NextNextcol >= CandyCol || Nextcol > CandyCol) return Combo;

    for (int i = 0; i < 8; i++)
    {
        int NextRow = row+dx[i];

        if (NextRow >= CandyRow || NextRow < 0) return Combo;

        ACandy* CurTarget = Candys[row][col];
        ACandy* NextTarget = nullptr;
        ACandy* NextNextTarget = nullptr;

        if (i == 0 || i == 1)
        {
            NextTarget = Candys[row][Nextcol];
            NextNextTarget = Candys[NextRow][NextNextcol];
        }
       
        if (i == 2 || i == 3)
        {
            NextTarget = Candys[NextRow][Nextcol];
            NextNextTarget = Candys[row][NextNextcol];
        }

        if (i == 4 || i == 5)
        {
            NextTarget = Candys[NextRow][Nextcol];
            NextNextTarget = Candys[NextRow][NextNextcol];
        }
        if (i == 6 )
        {
            if (col + 3 >= CandyCol) return Combo;
            NextTarget = Candys[row][col+1];
            NextNextTarget = Candys[row][col+3];
        }
        if (i == 7)
        {
            if (col + 2 >= CandyCol)  break;
            if (col + 3 >= CandyCol) break;

            NextTarget = Candys[row][col + 2];
            NextNextTarget = Candys[row][col + 3];
        }
        if (nullptr == CurTarget || nullptr == NextTarget || nullptr == NextNextTarget)
        {
            break;
        }

        EColor CurColor = CurTarget->CandyData.CandyColor;
        EColor NextColor = NextTarget->CandyData.CandyColor;
        EColor NextNextColor = NextNextTarget->CandyData.CandyColor;

        // 세개가 연속이다.
        if (CurColor == NextColor && NextColor == NextNextColor)
        {
            Combo = true;


        }
        else {
            Combo = false;
        }
    } 

    return Combo;

}
bool ACandyManager::ColCheckInProgress(int X, int Y)
{
    bool Combo = true;


    int dy[8] = { 1,-1,1,-1,-1,1,0,0 };

    int row = X;
    int col = Y;
    int NextRow = X + 1;
    int NextNextRow = X + 2;



    if (row >= CandyRow || NextNextRow >= CandyRow || NextRow > CandyRow) return true;

    for (int i = 0; i < 8; i++)
    {
        int NextCol = col + dy[i];

        if (NextCol >= CandyCol || NextCol < 0) break;

        ACandy* CurTarget = Candys[row][col];
        ACandy* NextTarget = nullptr;
        ACandy* NextNextTarget = nullptr;

        if (i == 0 || i == 1)
        {
            NextTarget = Candys[NextRow][col];
            NextNextTarget = Candys[NextNextRow][NextCol];
        }

        if (i == 2 || i == 3)
        {
            NextTarget = Candys[NextRow][NextCol];
            NextNextTarget = Candys[NextNextRow][col];
        }

        if (i == 4 || i == 5)
        {
            NextTarget = Candys[NextRow][NextCol];
            NextNextTarget = Candys[NextNextRow][NextCol];
        }
        if (i == 6)
        {
            if (row + 3 >= CandyRow) break;
            if (row + 2 >= CandyRow) break;
            NextTarget = Candys[row+1][NextCol];
            NextNextTarget = Candys[row+3][NextCol];
        }
        if (i == 7)
        {
            if (row + 3 >= CandyRow) break;


            NextTarget = Candys[row+2][NextCol];
            NextNextTarget = Candys[row+3][NextCol];
        }
        if (nullptr == CurTarget || nullptr == NextTarget || nullptr == NextNextTarget)
        {
            break;
        }

        EColor CurColor = CurTarget->CandyData.CandyColor;
        EColor NextColor = NextTarget->CandyData.CandyColor;
        EColor NextNextColor = NextNextTarget->CandyData.CandyColor;

       

        // 세개가 연속이다.
        if (CurColor == NextColor && NextColor == NextNextColor)
        {
            Combo = true;
        }
        else {
            Combo = false;
        }
    }

    return Combo;
}
bool  FindInProgressCombo = true;
void ACandyManager::CandyFindConsecInProgress()
{
    //CandyClear();
    //InProgressCandyClear();

     FindInProgressCombo = true;
    for (int row = 0; row < CandyRow; row++)
    {
        for (int col = 0; col < CandyCol; col++)
        {
            if (false == Data[row][col].IsActive) //빈자리는 체크 안함
            {
                continue;
            }

            if (false == RowCheckInProgress(row, col))
            {
                FindInProgressCombo = false;
                
            }
            if (false == ColCheckInProgress(row, col))
            {
                FindInProgressCombo = false;

                // 콤보가 하나라도 있다.
              
            }
           
        }
    }
   
   
}

void ACandyManager::InProgress(float _DeltaTime)
{
    //AActor::Tick(_DeltaTime);

    if (GetCandyState() != ECandyManagerState::Select) return;
    else
    {
        if (true == FindInProgressCombo)
        {
            //ChangeBoardState(ECandyBoardState::InProgress);

            return;
        }
        else
        {
           // ChangeBoardState(ECandyBoardState::Resetting);

            return;
        }
    }
    
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
void ACandyManager::InProgressCandyClear()
{
    InProgressCandy.clear();

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

            ACandy* Candy = Candys[x][y];
            if (Candy == nullptr) continue;
            Candys[x][y]->Destroy();
           // Candys[x][y] = nullptr;
        }
    }

}
void ACandyManager::ResettingStart()
{
    ResetCandyBoard();
    //ChangeBoardState(ECandyBoardState::InProgress);
    
}
void ACandyManager::ResetCandyBoard()
{

    ClearCandys(); // 캔디딀 저장 삭제
    CandyCreate(); // 캔디 다시 만듦
    CandyFindConsec(); // 콤보캔디 찾기
    CandyDestroyCheck(); // 상태 어디로 갈지.

    
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
                int Index = Random.RandomInt(1, 78);
                FVector Pos = IndexToWorldPos({ NewCandyRow, col });
                ACandy* NewCandy = NewCandyCreate(row,col,Pos);

                DropData NewData;
                NewData.Candy = NewCandy;
                NewData.StartPos = NewCandy->CandyData.SetPos;
                NewData.EndPos = Data[row][col].Pos;
                NewData.EndPos.Z = -100.0f;
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
                PlaySoundPlayer("candy_land1.wav");
                

                TimeEventComponent->AddEndEvent(CCSConst::DropTime, [this]()
                    {
                        IsCandyDrop = true;
                    });
            });
    }
}
void ACandyManager::PlaySoundPlayer(std::string _sound)
{
    {
        USoundPlayer SoundPlayer;
        SoundPlayer.SetVolume(0.5f);
        SoundPlayer = UEngineSound::Play(_sound);
    }
}
void ACandyManager::NewCandyDrop(float _Delta)
{

    if (IsCandyDrop == false) return;
  
    else if (0 == DropCandy.size())
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




// 캔디 부수기
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

        // 콤보 카운트
        
        if (PrevColor != EColor::None && PrevColor == CurColor)
        {
            Combo++;
            //IsCombo = true;
        }
        else {
            Combo = 1;

        }

        // 캔디 스프라이트 모양에 따른 기본 점수 계산한다.
        BasicPlayerStateScore(Candy);

        //UI HUD에서 스코어 바를 조정한다
        HudScoreBar();
       
        // 연쇄해서 부서지는 캔디 존재한다.
        if (ComboCount >= 2)
        {
            AScoreActor* ScoreActor = GetWorld()->SpawnActor< AScoreActor>().get();

            USoundPlayer SoundPlayer;
            SoundPlayer.SetVolume(0.5f);

            switch (ComboCount)
            {
            case 2:
                ScoreActor->SetSprite(3);
                ScoreActor->SetActorLocation({ -100,100,-200 });

                SoundPlayer = UEngineSound::Play("sweet.wav");  
                break;
            case 3:
                ScoreActor->SetSprite(1);
                ScoreActor->SetActorLocation({ -100,100,-201 });

                SoundPlayer = UEngineSound::Play("tasty.wav");           
                break;
            case 4:
                ScoreActor->SetSprite(0);
                ScoreActor->SetActorLocation({ -100,100,-202 });

                SoundPlayer = UEngineSound::Play("delicious.wav");
                break;
            case 5:
                ScoreActor->SetSprite(2);
                ScoreActor->SetActorLocation({ -100,100,-203 });

                SoundPlayer = UEngineSound::Play("divine.wav");
            
                break;
            
            default:
                break;
            }
            Score += BonusScore*ComboCount;
        }

        PrevColor = CurColor;
       
         Candys[Candy->CandyData.row][Candy->CandyData.col] = nullptr;
         Candy->Destroy();
         Candy = nullptr;
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
        // combo count 초기화
        TimeEventComponent->AddEndEvent(1.0f, [this]()
        {
            DestroyEnd = true;
            ComboCount = 0;

        });
    }
}

void ACandyManager::HudScoreBar()
{

    if (Score > 5000)
    {
        ScoreStar = 2;
    }
    else if (Score > 2700)
    {
        ScoreStar = 1;


    }
    else if (Score > 1000)
    {
        ScoreStar = 0;


    }
    else {
        ScoreStar = -1;

    }

    
    HudBar(Score);
}

void ACandyManager::HudBar(int Score)
{
    ACCSHUD* Hud = dynamic_cast<ACCSHUD*>(GetWorld()->GetHUD());

    float Acc = static_cast<float>( Score);
    if (Score > 7000)
    {
        Acc = 7000;
    }

    //2000 
    if (Hud != nullptr)
    {
        Hud->Score->SetRelativeScale3D({ 33.0f,(float)Acc / 2,0.0f });
        Hud->Score->SetWorldLocation({ -191,-57 + (float)Acc * 0.01f,0 });
    }
}


void ACandyManager::BasicPlayerStateScore(ACandy* Candy)
{
    switch (Candy->CandyData.CandySpriteType)
    {
    case ESpriteType::Normal:
        Score += 10;

        break;
    case ESpriteType::StripedHorizontal:
        Score += 30;

        break;
    case ESpriteType::StripedVertical:
        Score += 30;

        break;
    case ESpriteType::Wrapped:
       Score += 50;

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

}

void ACandyManager::CandyDestroyCheck()
{
    if (false == IsCandyDestroy())
    {
        //콤보 캔디가 없다.
        ChangeCandyState(ECandyManagerState::Select);
        return;
    }
    else {
        //콤보 캔디가 있다.
        ChangeCandyState(ECandyManagerState::Destroy);
        return;
    }

}

void ACandyManager::Update(float _DeltaTime)
{
    if (false == IsCandyDestroy() && (GetGameInstance<CandyGameInstance>()->CandyMouseCon.IsTransEnd == true))
    {
        // 이동이 끝.
        ChangeCandyState(ECandyManagerState::Disable);
        return;
    }
    if (false == IsCandyDestroy())
    {
        //콤보 캔디가 없다.
        ChangeCandyState(ECandyManagerState::Select);
        return;
    }
    else {
        //콤보 캔디가 있다.
        ChangeCandyState(ECandyManagerState::Destroy);
        return;
    }

}
void ACandyManager::DisableStart()
{
    //마지막 캔디 부수기
    CandyFindConsec();
    if (false == IsCandyDestroy())
    {
        //콤보 캔디가 없다.
        
    }
    else {
        //콤보 캔디가 있다.
        ChangeCandyState(ECandyManagerState::Destroy);
        return;
    }

    //이동횟수 끝남으로 게임끝
}
void ACandyManager::Disable(float _DeltaTime)
{
    // 마우스를 움직일 수 없는 경우.
    // 움직임 횟수가 끝나서 게임이 끝났다.
    // 

    GetGameInstance<CandyGameInstance>()->IsGameEnd = true;
}

void ACandyManager::BeginPlay()
{
    AActor::BeginPlay();


}

void ACandyManager::Tick(float _DeltaTime)
{
    AActor::Tick(_DeltaTime);

    GetGameInstance<CandyGameInstance>()->PlayerStat.ScoreStar = ScoreStar;
    GetGameInstance<CandyGameInstance>()->PlayerStat.Score = Score;


    if (UEngineInput::IsDown('R') == true)
    {
        ResettingStart();
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

