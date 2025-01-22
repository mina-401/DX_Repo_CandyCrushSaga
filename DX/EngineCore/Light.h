#pragma once
#include "SceneComponent.h"
#include "EngineSprite.h"
#include "RenderUnit.h"


// ���� ����ϱ� ���� ������ۿ� ����ü
struct FLightData
{
    float4 LightPos; // ���� ��ġ
    float4 LightDir; // ���� Forward
    float4 LightRevDir; // ���� �ݴ������ < L!!!!! <= 
    float4 LightColor = float4(1.0f, 1.0f, 1.0f, 1.0f);
    float4 AmbientLight = float4(0.1f, 0.1f, 0.1f, 1.0f);
    float4 ViewLightPos;
    float4 ViewLightDir;
    float4 ViewLightRevDir;
    float4 CameraPosition;
    // �� ���� ����Ҷ��� ī�޶� ��ġ�� ���� �־���� �մϴ�.
    // ����ŧ������Ʈ�� ����Ϸ��� �ٶ󺸴� �������ʿ��ϴ�.
};

struct FLightDatas
{
    // 256���� �����Ҽ� �ִ� ������
    int Count;
    FLightData LightArr[256];
};


// ���� : � �������̵� �Ҽ� �մ� ������ ����ڴ�.
// �������̶� �������� �ϴ°� �ƴմϴ�. 3D
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

