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
	void StarSetActive(int _value);

	void SetScoreStar(int _value);

	int ScoreStar = 0;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	class UFontWidget* ScoreText;
	class USpriteRenderer* Renderer = nullptr;

   USpriteRenderer* Stars[3];

   float DestroyTime = 50.0f;
   float CurTime = 0.0f;

   std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
};

