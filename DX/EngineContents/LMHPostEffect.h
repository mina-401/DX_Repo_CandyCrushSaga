#pragma once
#include <EngineCore/EngineRenderTarget.h>
#include <EngineCore/EngineCamera.h>

// Ό³Έν :
class ULMHPostEffect : public UPostEffect
{
public:
	// constrcuter destructer
	ULMHPostEffect();
	~ULMHPostEffect();

	// delete Function
	ULMHPostEffect(const ULMHPostEffect& _Other) = delete;
	ULMHPostEffect(ULMHPostEffect&& _Other) noexcept = delete;
	ULMHPostEffect& operator=(const ULMHPostEffect& _Other) = delete;
	ULMHPostEffect& operator=(ULMHPostEffect&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(UEngineCamera* Camera, float _DeltaTime) override;

private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

	// URenderUnit SecondEffect;
};

