#include "PreCompile.h"
#include "LightActor.h"
#include "Light.h"
#include "EngineCamera.h"

ALightActor::ALightActor()
{
	LightComponent = CreateDefaultSubObject<ULight>();
	// 직접 넣어줘야 합니다.
	RootComponent = LightComponent;
}

ALightActor::~ALightActor()
{
}




