#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class AHUD : public AActor
{
public:
	// constrcuter destructer
	AHUD();
	~AHUD();

	// delete Function
	AHUD(const AHUD& _Other) = delete;
	AHUD(AHUD&& _Other) noexcept = delete;
	AHUD& operator=(const AHUD& _Other) = delete;
	AHUD& operator=(AHUD&& _Other) noexcept = delete;
	
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class USpriteRenderer> Child_ScoreTextBox;
	std::shared_ptr<class USpriteRenderer> Child_ScoreBar;
	std::shared_ptr<class USpriteRenderer> Child_Score;

	float MaxScore = 100.0f;
	//float ScoreScale={200,}
};

