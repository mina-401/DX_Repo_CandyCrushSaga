#pragma once
#include<EngineCore/GameMode.h>


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
protected:

	void LevelChangeStart() override;
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

private:
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
	//class UWidget* ScoreTextWidget;


};

