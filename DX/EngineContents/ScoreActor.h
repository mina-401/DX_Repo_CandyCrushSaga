#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AScoreActor : public AActor
{
public:
	// constrcuter destructer
	AScoreActor();
	~AScoreActor();

	void SetSprite(int index);

	// delete Function
	AScoreActor(const AScoreActor& _Other) = delete;
	AScoreActor(AScoreActor&& _Other) noexcept = delete;
	AScoreActor& operator=(const AScoreActor& _Other) = delete;
	AScoreActor& operator=(AScoreActor&& _Other) noexcept = delete;

	class USpriteRenderer* GetRenderer()
	{
		return Renderer;
	}
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

	class USpriteRenderer* Renderer = nullptr;
};

