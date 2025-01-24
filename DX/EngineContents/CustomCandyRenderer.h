#pragma once

#include <EngineCore/Renderer.h>


// Ό³Έν :
class UCustomCandyRenderer : public URenderer
{
public:
	// constrcuter destructer
	UCustomCandyRenderer();
	~UCustomCandyRenderer();

	// delete Function
	UCustomCandyRenderer(const UCustomCandyRenderer& _Other) = delete;
	UCustomCandyRenderer(UCustomCandyRenderer&& _Other) noexcept = delete;
	UCustomCandyRenderer& operator=(const UCustomCandyRenderer& _Other) = delete;
	UCustomCandyRenderer& operator=(UCustomCandyRenderer&& _Other) noexcept = delete;

public:
	ENGINEAPI void SetSprite(std::string_view _Name, UINT _CurIndex = 0);
	ENGINEAPI std::string GetCurSpriteName()
	{
		return Sprite->GetName();
	}

	ENGINEAPI void SetTexture(std::string_view _Name, bool AutoScale = false, float _Ratio = 1.0f);

	void SetAutoScale(bool _Value)
	{
		IsAutoScale = _Value;
	}

	void SetAutoScaleRatio(float _Scale)
	{
		AutoScaleRatio = _Scale;
	}
	FSpriteData SpriteData;
protected:
	ENGINEAPI void Render(class UEngineCamera* _Camera, float _DeltaTime) override;
	ENGINEAPI void CameraTransUpdate(UEngineCamera* _Camera) override;
	void BeginPlay() override;
	void ComponentTick(float _DeltaTime) override;

	void SetSprite(UEngineSprite* _Sprite);

private:
	URenderUnit* MainUnit;
	int CurIndex = 0;
	bool IsAutoScale = true;
	float AutoScaleRatio = 1.0f;
	UEngineSprite* Sprite = nullptr;
};

