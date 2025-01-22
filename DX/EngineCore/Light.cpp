
#include <EngineCore/Actor.h>

//#include "ULevel.h"
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

    LightData.LightDir = GetWorldForwardVector(); // ���� Forward
    LightData.LightRevDir = -LightData.LightDir; // ���� �ݴ������ < L!!!!! <= 
    LightData.LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    LightData.AmbientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);
    LightData.ViewLightPos = LightData.LightPos * _Camera->GetTransformRef().View;
    LightData.ViewLightDir = LightData.LightDir * _Camera->GetTransformRef().View;
    LightData.ViewLightRevDir = LightData.LightRevDir * _Camera->GetTransformRef().View;
    LightData.CameraPosition = _Camera->GetWorldLocation() * _Camera->GetTransformRef().View;

}

