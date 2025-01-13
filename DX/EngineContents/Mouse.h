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

	void TestFunction(FCandySpriteData& _a);

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

	//FCandySpriteData& SelectCandyDataRef = SelectCandyData;
	//FCandySpriteData& CurCandyDataRef = CurCandyData;

	FCandySpriteData SelectCandyData= FCandySpriteData();
	FCandySpriteData CurCandyData= FCandySpriteData();

	

};

