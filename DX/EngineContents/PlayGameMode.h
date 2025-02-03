#pragma once
#include<EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>
enum class EGameModeState
{
	GameStart,
	InGame,
	Paused,
	GameEnd 
};
class APlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	 APlayGameMode();
	 ~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

	class ACandyManager* GetCandyManager()
	{
		return CandyManager;
	}	
	
	//bool IsGameEnd = false;
	void StartGame(int x, int y);

	void GameEndStart();

	void GameEnd(float _DeltaTime);

	void InGame(float _DeltaTime);

	void InGameStart();

protected:

	void LevelChangeStart() override;
	void LevelChangeEnd() override;
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

	EGameModeState GetGameModeState()
	{
		return GameModeState;
	}

	void ChangeState(EGameModeState _State)
	{
		GameModeState = _State;
		switch (GameModeState)
		{
		case EGameModeState::GameStart:
			break;
		case EGameModeState::InGame:
			break;
		case EGameModeState::Paused:
			break;
		case EGameModeState::GameEnd:
			GameEndStart();

			break;
		default:
			break;
		}
	}
private:
	void SoundInit();

	EGameModeState GameModeState = EGameModeState::GameStart;

	std::shared_ptr<class APlayMap> Map;
	//std::vector<std::vector<std::shared_ptr<class ACandy>>> Candys;

	 class ACandyManager* CandyManager;
	 std::shared_ptr< class AMouse> CandyMouseObj;
	void PlayDirLoad();
	void SpritesInit();

	std::shared_ptr<class AHUD> GameMainHud;
	class UWidget* ScoreWidget;
	class UWidget* ScoreBarWidget;
	class UWidget* ScoreTextBoxWidget;

	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	//class UWidget* ScoreTextWidget;

	USoundPlayer SoundPlayer;

	std::shared_ptr<class AResultHUD> Result = nullptr;

	float CurTime = 0.0f;
	float StarTime = 50.0f;

	int star = 0;
	int ScoreStar = 0;
};

