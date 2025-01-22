#pragma once
#include <EngineCore/Actor.h>
#include "CCSEnums.h"

class FCandySpriteData
{
public:

	//FIntPoint TargetIndex = { -1,-1 };
	//EComboVector ComboVectpr;
	ESpriteType CandySpriteType;
	EColor CandyColor;

	FVector SetPos = { 0,0 };
	int SpriteIndex = 0;
	int row = 0;
	int col = 0;

	void SetCandyColor(EColor _Color)
	{
		CandyColor = _Color;
	}

	void SetCandySprite(ESpriteType _Type)
	{
		CandySpriteType = _Type;
	}

	void SetSpriteColor(int _index)
	{
		if (0 == _index)
		{
			SetCandyColor(EColor::None);
		}
		else if (1 <= _index && _index < 10)
		{
			SetCandyColor(EColor::Blue);
		}
		else if (10 <= _index && _index < 19)
		{
			SetCandyColor(EColor::Green);
		}

		else if (19 <= _index && _index < 28)
		{
			SetCandyColor(EColor::Orange);
		}
		else if (28 <= _index && _index < 37)
		{
			SetCandyColor(EColor::Purple);
		}
		else if (37 <= _index && _index < 46)
		{
			SetCandyColor(EColor::Red);
		}
		else if (46 <= _index && _index < 55)
		{
			SetCandyColor(EColor::Yellow);
		}
		else if (55 == _index)
		{
			SetCandyColor(EColor::Choco);
		}

	}
	void SetSpriteType(int _index)
	{
		int idx = _index % 9;

		if (0 == _index || 55 == _index)
		{
			SetCandySprite(ESpriteType::None);
		}
		else if (1 == idx) {
			SetCandySprite(ESpriteType::StripedHorizontal);
		}
		else if (2 == idx)
		{
			SetCandySprite(ESpriteType::StripedVertical);
		}
		else if (3 == idx)
		{
			SetCandySprite(ESpriteType::Wrapped);
		}
		else
		{
			SetCandySprite(ESpriteType::Normal);

		}

	}
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
	void SetCandy(FIntPoint RenderPos, FVector _Pos, int _Index);
	void SetPos(int X, int Y);
	/*void SetSpriteColor(int _index)
	{
		if (0 == _index)
		{
			CandyData.SetCandyColor(EColor::None);
		}
		else if (1 <= _index && _index < 10)
		{
			CandyData.SetCandyColor(EColor::Blue);
		}
		else if (10 <= _index && _index < 19)
		{
			CandyData.SetCandyColor(EColor::Green);
		}

		else if (19 <= _index && _index < 28)
		{
			CandyData.SetCandyColor(EColor::Orange);
		}
		else if (28 <= _index && _index < 36)
		{
			CandyData.SetCandyColor(EColor::Purple);
		}
		else if (36 <= _index && _index < 46)
		{
			CandyData.SetCandyColor(EColor::Red);
		}
		else if (46 <= _index && _index < 54)
		{
			CandyData.SetCandyColor(EColor::Yellow);
		}
		else if (55 == _index)
		{
			CandyData.SetCandyColor(EColor::Choco);
		}

	}*/

	/*void SetSpriteType(int _index)
	{
		int idx = _index % 9;

		if (0 == _index || 55 == _index)
		{
			CandyData.SetCandySprite(ESpriteType::None);
		}
		else if (7 == idx) {
			CandyData.SetCandySprite(ESpriteType::StripedHorizontal);
		}
		else if (8 == idx)
		{
			CandyData.SetCandySprite(ESpriteType::StripedVertical);
		}
		else if (0 == idx)
		{
			CandyData.SetCandySprite(ESpriteType::Wrapped);

		}
		
		else
		{
			CandyData.SetCandySprite(ESpriteType::Normal);

		}

	}*/
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

