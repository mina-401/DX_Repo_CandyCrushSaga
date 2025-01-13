#include "PreCompile.h"
#include "PlayMap.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineCore.h>
#include "CustomTestRenderer.h"

APlayMap::APlayMap()
{
	PlayDirLoad();

	
	//GameMainHud = GetWorld()->SpawnActor<AHUD>();

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();
	Renderer->SetupAttachment(RootComponent);

	Renderer->SetTexture("Background.png");
	
	FVector Size = UEngineCore::GetScreenScale();
	Renderer->SetRelativeScale3D({ Size.X,Size.Y,0.0f });
	Renderer->SetWorldLocation({ 0,0,100 });

	//std::shared_ptr<UCustomTestRenderer> CustomRenderer = CreateDefau ltSubObject<UCustomTestRenderer>();
	//CustomRenderer->SetupAttachment(RootComponent);
	//CustomRenderer->SetRelativeScale3D({ Size.X,Size.Y,0.0f });
	//CustomRenderer->SetRelativeLocation({ 0,0,-1 });   

	
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