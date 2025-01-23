#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :
class AShine : public AActor
{
public:
	// constrcuter destructer
	AShine();
	~AShine();

	// delete Function
	AShine(const AShine& _Other) = delete;
	AShine(AShine&& _Other) noexcept = delete;
	AShine& operator=(const AShine& _Other) = delete;
	AShine& operator=(AShine&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return Renderer;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Renderer;
};

