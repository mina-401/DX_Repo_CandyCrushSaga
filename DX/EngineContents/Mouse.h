#pragma once
#include <EngineCore/Actor.h>
#include "Candy.h"
// ���� :


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

	void TestFunction(FCandySpriteData& _a);
	void CandyChange(ACandy* SelectCandy, ACandy* CurCandy);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class UTimeEventComponent> TimeEventComponent;
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;

	std::shared_ptr<class ACandyManager> CandyManager;


	int MaxRow = 0;
	int MaxCol = 0;


	void CandyMove(float _Delta, float _Acc, class ACandy* _SelectCandyPtr, class ACandy* _CurCandyPtr, FVector _StartPos, FVector _EndPos, float _MoveTime);

};

