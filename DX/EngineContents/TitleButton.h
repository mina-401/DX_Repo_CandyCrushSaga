#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ATitleButton : public AActor
{
public:
	// constrcuter destructer
	ATitleButton();
	~ATitleButton();

	// delete Function
	ATitleButton(const ATitleButton& _Other) = delete;
	ATitleButton(ATitleButton&& _Other) noexcept = delete;
	ATitleButton& operator=(const ATitleButton& _Other) = delete;
	ATitleButton& operator=(ATitleButton&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

	std::shared_ptr<class UImageWidget> Button;
	class UFontWidget* TitleText;
};

