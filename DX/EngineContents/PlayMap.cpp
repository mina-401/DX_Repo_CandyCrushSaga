#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCore.h>
#include "HUD.h"

APlayMap::APlayMap()
{
	PlayDirLoad();

	
	GameMainHud = GetWorld()->SpawnActor<AHUD>();

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);

	
	Renderer->SetTexture("Background.png");
	

	FVector Size = UEngineCore::GetScreenScale();
	Renderer->SetRelativeScale3D({ Size.X,Size.Y,0.0f });

	
}

APlayMap::~APlayMap()
{
}

void APlayMap::BeginPlay()
{
	AActor::BeginPlay();
}

void APlayMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

void APlayMap::PlayDirLoad()
{
	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("리소스 폴더를 찾지 못했습니다.");
			return;
		}
		Dir.Append("Image\\Play\\HUD");

		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}
}