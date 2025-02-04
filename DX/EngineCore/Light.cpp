#include "PreCompile.h"
#include "Light.h"
#include <EngineBase/EngineString.h>
#include <EngineCore/EngineCamera.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/Mesh.h>
#include "EngineVertex.h"
#include "EngineBlend.h"
#include "Level.h"

ULight::ULight()
{
}

ULight::~ULight()
{

}

void ULight::BeginPlay()
{
    GetWorld()->PushLight(GetThis<ULight>());
}

void ULight::LightUpdate(UEngineCamera* _Camera, float _DeltaTime)
{
    // 디렉셔널 라이트일때는 위치를 넣어줘봐야 의미가 없다.
    // 태양은 너무 멀리있고 너무 밝아.
    // 포인트 라이트 일때는 중요하지만 디렉셔널 라이트일때는 무시하는게 기본이다.
    LightData.LightPos = GetWorldLocation(); // 빛의 위치

    // LightDir은 회전에 관련된 녀석이기 때문에 Nomrmal되어 있어야 하고 이동관련 수치가 적용되면 안된다.
    LightData.LightDir = GetWorldForwardVector(); // 빛의 Forward
    LightData.LightRevDir = -LightData.LightDir; // 빛의 반대방향이 < L!!!!! <= 
    LightData.LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    LightData.AmbientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);

    float4x4 View = _Camera->GetTransformRef().View;

    LightData.ViewLightPos = LightData.LightPos * View;
    LightData.ViewLightDir = LightData.LightDir * View;
    LightData.ViewLightRevDir = LightData.LightRevDir * View;
    FVector Pos = _Camera->GetWorldLocation();
    LightData.CameraPosition = _Camera->GetWorldLocation() * View;

}

