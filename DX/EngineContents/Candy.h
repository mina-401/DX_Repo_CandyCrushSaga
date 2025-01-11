#pragma once
#include <EngineCore/Actor.h>
enum class SpriteType
{
	Normal,
	StripedHorizontal,
	StripedVertical,
	Wrapped
};
enum class Color
{
	Blue,
	Red,
	Orange,
	Yellow,
	Purple,
	Green,
	Choco,

};

class FCandySpriteData
{
public:
	/*SpriteType CandySpriteType;
	Color CandyColor;*/

	FVector SetPos = { 0,0 };
	int SpriteIndex = 0;
	int row = 0;
	int col = 0;

};
class ACandy : public AActor
{
public:
	// constrcuter destructer
	ACandy();
	~ACandy();

	// delete Function
	ACandy(const ACandy& _Other) = delete;
	ACandy(ACandy&& _Other) noexcept = delete;
	ACandy& operator=(const ACandy& _Other) = delete;
	ACandy& operator=(ACandy&& _Other) noexcept = delete;

	std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return Renderer;
	}
	void SetCandy(FVector RenderPos,FVector& _Pos, int _Index);


	FCandySpriteData& GetCandyData()
	{
		return CandyData;
	}
	FCandySpriteData CandyData;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;

	FVector MaxSize = { 0,0 };
	FVector CandyScale = { 50,50 };

	
	
};

