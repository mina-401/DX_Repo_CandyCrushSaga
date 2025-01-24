#pragma once
#include <EngineCore/Actor.h>
#include "Candy.h"
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
	bool IsTransEnd = false;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;

	class ACandyManager* CandyManager;


	int MaxRow = 0;
	int MaxCol = 0;
	int MaxTransCount = 10;
	int CurTransCount = MaxTransCount;

	//bool IsGameEnd = false;

	void CandyMove(float _Delta, float _Acc, class ACandy* _SelectCandyPtr, class ACandy* _CurCandyPtr, FVector _StartPos, FVector _EndPos, float _MoveTime);

};

