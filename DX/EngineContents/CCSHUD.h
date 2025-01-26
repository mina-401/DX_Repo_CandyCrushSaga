#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/HUD.h>
#include <EngineCore/Widget.h>
// ���� :
class ACCSHUD : public AHUD
{
public:
	// constrcuter destructer
	ACCSHUD();
	~ACCSHUD();

	// delete Function
	ACCSHUD(const ACCSHUD& _Other) = delete;
	ACCSHUD(ACCSHUD&& _Other) noexcept = delete;
	ACCSHUD& operator=(const ACCSHUD& _Other) = delete;
	ACCSHUD& operator=(ACCSHUD&& _Other) noexcept = delete;
	
	class UImageWidget* ScoreTextBox;
	class UImageWidget* FrameWidget;
	class UImageWidget* ScoreBar;
	class UImageWidget* Score;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class USpriteRenderer> Child_ScoreTextBox;
	std::shared_ptr<class USpriteRenderer> Child_ScoreBar;
	std::shared_ptr<class USpriteRenderer> Child_Score;

	float MaxScore = 100.0f;
	

};

