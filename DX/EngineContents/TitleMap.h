#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class ATitleMap : public AActor
{
public:
	// constrcuter destructer
	ATitleMap();
	~ATitleMap();

	// delete Function
	ATitleMap(const ATitleMap& _Other) = delete;
	ATitleMap(ATitleMap&& _Other) noexcept = delete;
	ATitleMap& operator=(const ATitleMap& _Other) = delete;
	ATitleMap& operator=(ATitleMap&& _Other) noexcept = delete;

	std::shared_ptr<class CustomTestRenderer> GetRenderer()
	{
		return Renderer;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class CustomTestRenderer> Renderer;
	std::shared_ptr<class USpriteRenderer> Child;
};

