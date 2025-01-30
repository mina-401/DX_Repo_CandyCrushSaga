#pragma once
#include<EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>

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
	
	bool IsGameEnd = false;
	void StartGame(int x, int y);

protected:

	void LevelChangeStart() override;
	void LevelChangeEnd() override {};
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

private:
	void SoundInit();



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
};

