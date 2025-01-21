#pragma once
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineWinImage.h>
#include <EngineCore/Actor.h>

// ���� :
class AMeshActor : public AActor
{
public:
	// constrcuter destructer
	AMeshActor();
	~AMeshActor();

	// delete Function
	AMeshActor(const AMeshActor& _Other) = delete;
	AMeshActor(AMeshActor&& _Other) noexcept = delete;
	AMeshActor& operator=(const AMeshActor& _Other) = delete;
	AMeshActor& operator=(AMeshActor&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


private:
};

