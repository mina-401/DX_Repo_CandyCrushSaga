#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"
#include "RenderUnit.h"


// 빛을 계산하기 위한 상수버퍼용 구조체
struct FLightData
{
    float4 LightPos; // 빛의 위치
    float4 LightDir; // 빛의 Forward
    float4 LightRevDir; // 빛의 반대방향이 < L!!!!! <= 
    float4 LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    float4 AmbientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);
    float4 ViewLightPos;
    float4 ViewLightDir;
    float4 ViewLightRevDir;
    float4 CameraPosition;
    // 이 빛을 계산할때의 카메라 위치를 같이 넣어줘야 합니다.
    // 스펙큘러라이트를 계산하려면 바라보는 연산이필요하다.
};

struct FLightDatas
{
    // 256개를 세팅할수 있는 데이터
    int Count;
    FLightData LightArr[256];
};


// 설명 : 어떤 랜더링이든 할수 잇는 구조로 만들겠다.
// 랜더링이란 랜더러만 하는게 아닙니다. 3D
class ULight : public USceneComponent
{
    friend class ULevel;
    friend class UEngineCamera;

public:
    // constrcuter destructer
    ENGINEAPI ULight();
    ENGINEAPI ~ULight();

    // delete Function
    ULight(const ULight& _Other) = delete;
    ULight(ULight&& _Other) noexcept = delete;
    ULight& operator=(const ULight& _Other) = delete;
    ULight& operator=(ULight&& _Other) noexcept = delete;

protected:
    ENGINEAPI void BeginPlay() override;


private:
    FLightData LightData;

    void LightUpdate(class UEngineCamera* _Camera, float _DeltaTime);
};

