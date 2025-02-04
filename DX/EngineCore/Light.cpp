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
    // �𷺼ų� ����Ʈ�϶��� ��ġ�� �־������ �ǹ̰� ����.
    // �¾��� �ʹ� �ָ��ְ� �ʹ� ���.
    // ����Ʈ ����Ʈ �϶��� �߿������� �𷺼ų� ����Ʈ�϶��� �����ϴ°� �⺻�̴�.
    LightData.LightPos = GetWorldLocation(); // ���� ��ġ

    // LightDir�� ȸ���� ���õ� �༮�̱� ������ Nomrmal�Ǿ� �־�� �ϰ� �̵����� ��ġ�� ����Ǹ� �ȵȴ�.
    LightData.LightDir = GetWorldForwardVector(); // ���� Forward
    LightData.LightRevDir = -LightData.LightDir; // ���� �ݴ������ < L!!!!! <= 
    LightData.LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    LightData.AmbientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);

    float4x4 View = _Camera->GetTransformRef().View;

    LightData.ViewLightPos = LightData.LightPos * View;
    LightData.ViewLightDir = LightData.LightDir * View;
    LightData.ViewLightRevDir = LightData.LightRevDir * View;
    FVector Pos = _Camera->GetWorldLocation();
    LightData.CameraPosition = _Camera->GetWorldLocation() * View;

}

