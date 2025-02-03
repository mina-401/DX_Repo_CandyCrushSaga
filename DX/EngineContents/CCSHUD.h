#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/HUD.h>
#include <EngineCore/Widget.h>
#include "CCSStruct.h"
// Ό³Έν :
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
	
	class UFontWidget* ScoreText;
	class UFontWidget* MaxScoreText;
	class UFontWidget* TransText;

	class UImageWidget* ScoreTextBox;
	class UImageWidget* FrameWidget;
	class UImageWidget* ScoreBar;
	class UImageWidget* ScoreStar1;
	class UImageWidget* ScoreStar2;
	class UImageWidget* ScoreStar3;

	class UImageWidget* ButtonWidget;

	//class UImageWidget* Score;
	std::shared_ptr<UImageWidget> Score;

	bool IsRestart = false;
	//class USpriteRenderer* Score;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

	
	float ACC = 0;
	//PlayerStatus PlayerStat;
	int Turn;
	int MaxScore;
};

