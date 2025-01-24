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
		else if (1 <= _index && _index < 14)
		{
			SetCandyColor(EColor::Blue);
		}
		else if (14 <= _index && _index < 27)
		{
			SetCandyColor(EColor::Green);
		}

		else if (27 <= _index && _index < 40)
		{
			SetCandyColor(EColor::Orange);
		}
		else if (40 <= _index && _index < 53)
		{
			SetCandyColor(EColor::Purple);
		}
		else if (53 <= _index && _index < 66)
		{
			SetCandyColor(EColor::Red);
		}
		else if (66 <= _index && _index < 79)
		{
			SetCandyColor(EColor::Yellow);
		}
		else if (79 == _index)
		{
			SetCandyColor(EColor::Choco);
		}

	}
	void SetSpriteType(int _index)
	{
		int idx = _index % 13;

		if (0 == _index || 79 == _index)
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

	/*std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return Renderer;
	}*/
	std::shared_ptr<class UCustomCandyRenderer> GetRenderer()
	{
		return Renderer;
	}
	void SetCandy(FIntPoint RenderPos, FVector _Pos, int _Index);
	void SetPos(int X, int Y);
	
	FCandySpriteData& GetCandyData()
	{
		return CandyData;
	}
	FCandySpriteData CandyData;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	//std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class UCustomCandyRenderer> Renderer;
	std::shared_ptr<class UCollision> Collision;

	FVector MaxSize = { 0,0 };
	FVector CandyScale = { 50,50 };

	
	
};

