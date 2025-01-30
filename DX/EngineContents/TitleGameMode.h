#pragma once

#include<EngineCore/GameMode.h>
#include <EnginePlatform/EngineSound.h>

class ATitleGameMode : public AGameMode
{
public:
	// constrcuter destructer
	 ATitleGameMode();
	 ~ATitleGameMode();

	// delete Function
	ATitleGameMode(const ATitleGameMode& _Other) = delete;
	ATitleGameMode(ATitleGameMode&& _Other) noexcept = delete;
	ATitleGameMode& operator=(const ATitleGameMode& _Other) = delete;
	ATitleGameMode& operator=(ATitleGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

protected:
	void LevelChangeStart() override;
	void LevelChangeEnd() override;
private:
	std::shared_ptr<class ATitleMap> Map;
	std::shared_ptr<class ATitleButton> Button;
	

	void TitleDirLoad();
	void SpritesInit();
	void SoundInit();

	USoundPlayer SoundPlayer;
};

