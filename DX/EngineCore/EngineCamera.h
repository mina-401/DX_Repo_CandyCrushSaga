#pragma once
#include <map>
#include <list>
#include "Renderer.h"
#include "SceneComponent.h"

// MinimapCamera;
// PlayerCamera
// PlayCamera
// UICamera

// 설명 :
class UEngineCamera : public USceneComponent
{
	friend class ULevel;

public:
	// constrcuter destructer
	UEngineCamera();
	~UEngineCamera();

	// delete Function
	UEngineCamera(const UEngineCamera& _Other) = delete;
	UEngineCamera(UEngineCamera&& _Other) noexcept = delete;
	UEngineCamera& operator=(const UEngineCamera& _Other) = delete;
	UEngineCamera& operator=(UEngineCamera&& _Other) noexcept = delete;

	void Render(float _DetlaTime);

	void Tick(float _DetlaTime);


protected:


private:
	// 내가 바라보는 랜더러의 그룹은 카메라가 가진다.
	std::map<int, std::list<std::shared_ptr<class URenderer>>> Renderers;

	void ChangeRenderGroup(int _PrevGroupOrder, std::shared_ptr<URenderer> _Renderer);
};

