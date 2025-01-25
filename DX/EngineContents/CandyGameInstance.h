#pragma once
#include <EngineCore/GameInstance.h>
#include <EngineCore/Widget.h>

struct PlayerStatus
{
	int Score;
	int Star;
};
// Ό³Έν :
class CandyGameInstance : public UGameInstance
{
public:
	// constrcuter destructer
	CandyGameInstance();
	~CandyGameInstance();

	// delete Function
	CandyGameInstance(const CandyGameInstance& _Other) = delete;
	CandyGameInstance(CandyGameInstance&& _Other) noexcept = delete;
	CandyGameInstance& operator=(const CandyGameInstance& _Other) = delete;
	CandyGameInstance& operator=(CandyGameInstance&& _Other) noexcept = delete;

	UWidget* ScoreTextBox;
	UWidget* ScroeBar;
	UWidget* Score;

	PlayerStatus PlayerStat;
protected:	

private:
};

