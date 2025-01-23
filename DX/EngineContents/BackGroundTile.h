#pragma once

#include <EngineCore/Actor.h>
 
class ABackGroundTile : public AActor
{
public:
	// constrcuter destructer
	ABackGroundTile();
	~ABackGroundTile();

	// delete Function
	ABackGroundTile(const ABackGroundTile& _Other) = delete;
	ABackGroundTile(ABackGroundTile&& _Other) noexcept = delete;
	ABackGroundTile& operator=(const ABackGroundTile& _Other) = delete;
	ABackGroundTile& operator=(ABackGroundTile&& _Other) noexcept = delete;

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

