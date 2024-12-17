#include "PreCompile.h"
#include "TitleGameMode.h"

ATitleGameMode::ATitleGameMode()
{
	// GetWorld()->
}

ATitleGameMode::~ATitleGameMode()
{
}
void ATitleGameMode::BeginPlay()
{
	AActor::BeginPlay();
}
void ATitleGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);


}