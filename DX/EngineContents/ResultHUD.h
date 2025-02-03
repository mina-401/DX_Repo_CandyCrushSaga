#pragma once
#include <EngineCore/HUD.h>

// Ό³Έν :
class AResultHUD : public AHUD
{
public:
	// constrcuter destructer
	AResultHUD();
	~AResultHUD();

	void SetSprite(int index);

	// delete Function
	AResultHUD(const AResultHUD& _Other) = delete;
	AResultHUD(AResultHUD&& _Other) noexcept = delete;
	AResultHUD& operator=(const AResultHUD& _Other) = delete;
	AResultHUD& operator=(AResultHUD&& _Other) noexcept = delete;

	class USpriteRenderer* GetRenderer()
	{
		return Renderer;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

	class USpriteRenderer* Renderer = nullptr;
};

