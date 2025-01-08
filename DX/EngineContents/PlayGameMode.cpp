#include "PreCompile.h"
#include "PlayGameMode.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/Level.h>	
#include <EngineCore/EngineCamera.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/SpriteRenderer.h>
#include "PlayMap.h"

#include "Candy.h"

class CandyCrushSagaDebugWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{

		if (true == ImGui::Button("FreeCameraOn")) 
		{
 			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine(); 
		ImGui::Text("Free Camera");

	}
};
APlayGameMode::APlayGameMode()
{
	{
		std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
		Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
		Camera->GetCameraComponent()->SetZSort(0, true);
	}
	PlayDirLoad();
	SpritesInit();
	{
		Map=GetWorld()->SpawnActor<APlayMap>();
	}

}

APlayGameMode::~APlayGameMode()
{
}

void APlayGameMode::BeginPlay()
{
	AActor::BeginPlay();
	{
		UEngineGUI::CreateGUIWindow<CandyCrushSagaDebugWindow>("CandyCrushSagaDebugWindow");
	}
	{
		std::shared_ptr<class ACandy> PrevCandy = nullptr;
		Candys.resize(CandyRow + 1);


		FVector CurPos = { 0,0 };

		
		for (int i = 1; i <= CandyRow; i++)
		{
			Candys[i].resize(CandyCol + 1);
		}
		for (int row = 1; row <= CandyRow; row++)
		{
			for (int col = 1; col <= CandyCol; col++)
			{
				
				int RandIndex = RandomInt(1, 46);
				Candys[row][col] = SpawnCandy(CurPos, RandIndex);
				
			}
			float PlusPos = (Candys[row][1]->GetRenderer()->GetWorldScale3D().Y + 10.0f);
			CurPos.Y -= PlusPos;
			CurPos.X = 0;
		}
	}

}
std::shared_ptr<class ACandy> APlayGameMode::SpawnCandy(FVector& _CurPos,int _CandyIndex)
{
	// 캔디는 랜덤 확률로 생성한다.
	// candyIndex++
	// 이미지에서 랜덤으로 가져오기

	
	
	std::shared_ptr<class ACandy> NewCandy = GetWorld()->SpawnActor<ACandy>();

	FVector Scale = NewCandy->GetRenderer()->GetWorldScale3D();
	Scale += {10.0f, 10.0f};
	_CurPos = { _CurPos.X + Scale.X,_CurPos.Y };


	NewCandy->AddActorLocation(_CurPos);
	NewCandy->GetRenderer()->SetSprite("Candy", _CandyIndex);

	return NewCandy;

}
void APlayGameMode::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void APlayGameMode::PlayDirLoad()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\Play\\BG");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image//Play//Candy");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
		UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	}

}

void APlayGameMode::SpritesInit()
{
	//UEngineSprite::CreateSpriteToMeta("Candys.png", ".sdata");

}

