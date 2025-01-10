#pragma once
#include <EngineCore/Actor.h>
// Ό³Έν :


class AMouse : public AActor
{

public:
	// constrcuter destructer
	AMouse();
	~AMouse();

	// delete Function
	AMouse(const AMouse& _Other) = delete;
	AMouse(AMouse&& _Other) noexcept = delete;
	AMouse& operator=(const AMouse& _Other) = delete;
	AMouse& operator=(AMouse&& _Other) noexcept = delete;

	//void CollisionEnter(UCollision* _This, UCollision* _Other);
	class ACandy* SelectCandy = nullptr;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;

	std::shared_ptr<class ACandyManager> CandyManager;


	int MaxRow = 0;
	int MaxCol = 0;
};

