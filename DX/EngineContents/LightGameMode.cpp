#include "PreCompile.h"
#include "LightGameMode.h"

#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include "MeshActor.h"
#include <EngineCore/EngineCore.h>
#include "TitleGameMode.h"
#include "TileMapGameMode.h"


ALightGameMode::ALightGameMode()
{


	

	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({0.0f, 0.0f, -100.0f, 1.0f});
	Camera->GetCameraComponent()->SetZSort(0, true);

	{
		std::shared_ptr<AMeshActor> NewMonster = GetWorld()->SpawnActor<AMeshActor>();
		NewMonster->SetActorRelativeScale3D({ 100.0f, 100.0f, 100.0f, 1.0f });
		NewMonster->SetActorLocation({ 0.0f, 0.0f, 0.0f });
	}


}

ALightGameMode::~ALightGameMode()
{

}

void ALightGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

}

void ALightGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();


}