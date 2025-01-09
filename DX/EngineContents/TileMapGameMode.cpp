#include "PreCompile.h"
#include "TileMapGameMode.h"

#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCore.h>

enum class ESpawnList
{
	Monster,
	Monster2,
};

class UTileMapWindow : public UEngineGUIWindow
{
public:
	int SelectItem = 0;

	void OnGUI() override
	{
		std::vector<const char*> Arr;
		Arr.push_back("Monster");
		Arr.push_back("Monster2");


		ImGui::ListBox("SpawnList", &SelectItem, &Arr[0], 2);

		if (true == UEngineInput::IsDown(VK_LBUTTON))
		{
			ESpawnList SelectMonster = static_cast<ESpawnList>(SelectItem);
			//std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
			//FVector Pos = Camera->ScreenMousePosToWorldPos();
			//Pos.Z = 0.0f;

			//std::shared_ptr<AActor> NewMonster;

			switch (SelectMonster)
			{
			case ESpawnList::Monster:
				//NewMonster = GetWorld()->SpawnActor<AMonster>();
				break;
			case ESpawnList::Monster2:
				//NewMonster = GetWorld()->SpawnActor<AMonster2>();
				break;
			default:
				break;
			}

			//NewMonster->SetActorLocation(Pos);
		}



		if (true == ImGui::Button("Save"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("리소스 폴더를 찾지 못했습니다.");
				return;
			}
			Dir.Append("Data");
			std::string InitPath = Dir.GetPathToString();

			OPENFILENAME ofn;       // common dialog box structure
			char szFile[260] = { 0 };       // if using TCHAR macros
			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = nullptr;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = ("All\0*.*\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrDefExt = "MapData";
			ofn.lpstrInitialDir = InitPath.c_str();
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetSaveFileNameA(&ofn) == TRUE)
			{
				int a = 0;
				ofn.lpstrFile;
			}
		}

		if (true == ImGui::Button("Load"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("리소스 폴더를 찾지 못했습니다.");
				return;
			}
			Dir.Append("Data");
			std::string InitPath = Dir.GetPathToString();

			OPENFILENAME ofn;       // common dialog box structure
			char szFile[260] = { 0 };       // if using TCHAR macros
			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = nullptr;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = ("All\0*.*\0Text\0*.MapData\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = InitPath.c_str();
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileNameA(&ofn) == TRUE)
			{
				int a = 0;
				ofn.lpstrFile;
			}
		}

		

	}
};

ATileMapGameMode::ATileMapGameMode()
{
	// 레벨마다 해주셔야 합니다.
// 이걸 UI공유할건지 
	//GetWorld()->CreateCollisionProfile("Monster");


	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({0.0f, 0.0f, -1000.0f, 1.0f});
	Camera->GetCameraComponent()->SetZSort(0, true);

}

ATileMapGameMode::~ATileMapGameMode()
{
	
}

void ATileMapGameMode::BeginPlay()
{
	AActor::BeginPlay();
}

void ATileMapGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);
}

void ATileMapGameMode::LevelChangeStart() 
{
	UEngineGUI::AllWindowOff();

	{
		std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
		}

		Window->SetActive(true);
	}

	{
		TileMapWindow = UEngineGUI::FindGUIWindow<UTileMapWindow>("TileMapWindow");

		if (nullptr == TileMapWindow)
		{
			TileMapWindow = UEngineGUI::CreateGUIWindow<UTileMapWindow>("TileMapWindow");
		}

		TileMapWindow->SetActive(true);
	}

	/*{
		std::list<std::shared_ptr<AMon>> AllMonsterList = GetWorld()->GetAllActorListByClass<AMon>();
		std::vector<std::string> ArrString;
		for (std::shared_ptr<class AActor> Actor : AllMonsterList)
		{
			ArrString.push_back(Actor->GetName());
		}

		std::vector<const char*> Arr;
		for (size_t i = 0; i < ArrString.size(); i++)
		{
			Arr.push_back(ArrString[i].c_str());
		}


		if (0 < Arr.size())
		{
			ImGui::ListBox("AllActorList", &SelectItem, &Arr[0], Arr.size());
		}
	}*/

}