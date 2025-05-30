#pragma once
#include <map>
#include <list>
#include "Renderer.h"
#include "SceneComponent.h"
#include "EngineEnums.h"

// MinimapCamera;
// PlayerCamera
// PlayCamera
// UICamera

// 설명 :
class UEngineCamera : public USceneComponent
{
	friend class ULevel;
	friend class ACameraActor;

public:
	// constrcuter destructer
	UEngineCamera();
	~UEngineCamera();

	// delete Function
	UEngineCamera(const UEngineCamera& _Other) = delete;
	UEngineCamera(UEngineCamera&& _Other) noexcept = delete;
	UEngineCamera& operator=(const UEngineCamera& _Other) = delete;
	UEngineCamera& operator=(UEngineCamera&& _Other) noexcept = delete;

	ENGINEAPI bool CheckPickCollision(std::string_view _CollisionProfile, std::vector<class UCollision*>& _Collision);

	void BeginPlay() override;

	void Render(float _DetlaTime);

	void Tick(float _DetlaTime);

	void CalculateViewAndProjection();

	ENGINEAPI void SetFar(float _Value)
	{
		Far = _Value;
	}

	ENGINEAPI void SetNear(float _Value)
	{
		Near = _Value;
	}

	ENGINEAPI void SetFOV(float _Value)
	{
		FOV = _Value;
	}

	ENGINEAPI void SetProjectionType(EProjectionType _Type)
	{
		ProjectionType = _Type;
	}

	ENGINEAPI void SetZSort(int _Order, bool _Value);

	ENGINEAPI void Release(float _DeltaTime);

	UEngineRenderTarget* GetCameraTarget()
	{
		return CameraTarget.get();
	}


protected:


private:
	float Near = 1.0f;
	float Far = 5000.0f;

	float FOV = 60.0f;

	EProjectionType ProjectionType = EProjectionType::Orthographic;

	D3D11_VIEWPORT ViewPortInfo;



	FVector ProjectionScale = { 0.0f, 0.0f };

	// 내가 바라보는 랜더러의 그룹은 카메라가 가진다.
	std::map<int, std::list<std::shared_ptr<class URenderer>>> Renderers;
	std::map<int, bool> RendererZSort;

	std::shared_ptr<class UEngineRenderTarget> CameraTarget;



	void ChangeRenderGroup(int _PrevGroupOrder, std::shared_ptr<URenderer> _Renderer);
};

