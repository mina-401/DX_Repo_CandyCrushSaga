#include "PreCompile.h"
#include "TileMapRenderer.h"
#include "EngineCamera.h"
#include "EngineSprite.h"


UTileMapRenderer::UTileMapRenderer()
{
	CreateRenderUnit();
	SetMesh("Rect");
	SetMaterial("TileMap");

	//GetRenderUnit().ConstantBufferLinkData("ResultColor", ColorData);
	//GetRenderUnit().ConstantBufferLinkData("FSpriteData", SpriteData);
	//GetRenderUnit().ConstantBufferLinkData("FUVValue", UVValue);



}

UTileMapRenderer::~UTileMapRenderer()
{
}

void UTileMapRenderer::SetTileSetting(ETileMapType _Type, std::string_view _Name, FVector _TileSize, FVector _ImageSize, FVector _Pivot)
{
	Sprite = UEngineSprite::Find<UEngineSprite>(_Name).get();

	TileMapType = _Type;
	TileSize = _TileSize;
	ImageSize = _ImageSize;
	TilePivot = _Pivot;
}

void UTileMapRenderer::BeginPlay()
{
	URenderer::BeginPlay();

}

FTileIndex UTileMapRenderer::WorldPosToTileIndex(FVector _Pos)
{
	FTileIndex Result = FTileIndex();
	switch (TileMapType)
	{
	case Rect:
	{
		FVector ConvertVector = _Pos /= TileSize;
		Result.X = ConvertVector.iX();
		Result.Y = ConvertVector.iY();
		break;
	}
	case Iso:
	{
		Result.X = static_cast<int>((_Pos.X / TileSize.hX() + _Pos.Y / TileSize.hY()) / 2.0f);
		Result.Y = static_cast<int>((_Pos.Y / TileSize.hY() - _Pos.X / TileSize.hX()) / 2.0f);
		break;
	}
	default:
		break;
	}

	return Result;
}

FVector UTileMapRenderer::TileIndexToWorldPos(FTileIndex _Index)
{
	FVector Result;
	switch (TileMapType)
	{
	case Rect:
		Result.X = _Index.X * TileSize.X;
		Result.Y = _Index.Y * TileSize.X;
		break;
	case Iso:
	{
		Result.X = (_Index.X - _Index.Y) * TileSize.hX();
		Result.Y = (_Index.X + _Index.Y) * TileSize.hY();
		break;
	}
	default:
		break;
	}

	return Result;
}

void UTileMapRenderer::Render(UEngineCamera* _Camera, float _DeltaTime)
{

	switch (TileMapRenderMove)
	{
	case Normal:
		RenderNormal(_Camera, _DeltaTime);
		break;
	case Instancing:
		RenderInstancing(_Camera, _DeltaTime);
		break;
	default:
		break;
	}
}

void UTileMapRenderer::SetTile(FVector _Pos, int _Spriteindex)
{
	// 이공식이?????
	FTileIndex Index = WorldPosToTileIndex(_Pos);

	SetTile(Index.X, Index.Y, _Spriteindex);
}

void UTileMapRenderer::RemoveTile(FVector _Pos)
{
	FTileIndex Index = WorldPosToTileIndex(_Pos);

	RemoveTile(Index.X, Index.Y);
}

void UTileMapRenderer::SetTile(int _X, int _Y, int _Spriteindex)
{
	FTileIndex Index = { _X,  _Y };

	FTileData& NewTile = Tiles[Index.Key];

	NewTile.Index = Index;
	NewTile.SpriteIndex = _Spriteindex;
	NewTile.SpriteData.CuttingPos = { 0.0f, 0.0f };
	NewTile.SpriteData.CuttingSize = { 1.0f, 1.0f };
	NewTile.SpriteData.Pivot = { 0.5f, 0.5f };
	NewTile.ColorData.PlusColor = { 0.0f, 0.0f, 0.0f, 0.0f };
	NewTile.ColorData.MulColor = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void UTileMapRenderer::RemoveTile(int _X, int _Y)
{
	FTileIndex Index = { _X,  _Y };

	if (false == Tiles.contains(Index.Key))
	{
		return;
	}

	Tiles.erase(Index.Key);
}


void UTileMapRenderer::ComponentTick(float _DeltaTime)
{
	URenderer::ComponentTick(_DeltaTime);
}


void UTileMapRenderer::Serialize(UEngineSerializer& _Ser)
{
	_Ser << static_cast<int>(TileMapType);
	_Ser << TileSize;
	_Ser << ImageSize;
	_Ser << TilePivot;
	std::string Name = Sprite->GetName();
	_Ser << Name;

	_Ser << static_cast<int>(Tiles.size());
	for (std::pair<const __int64, FTileData>& Pair : Tiles)
	{
		_Ser.Write(&Pair.second, sizeof(FTileData));
	}
}
// 데이터를 복구(할때)
void UTileMapRenderer::DeSerialize(UEngineSerializer& _Ser)
{
	Tiles.clear();

	_Ser.Read(&TileMapType, sizeof(int));
	_Ser >> TileSize;
	_Ser >> ImageSize;
	_Ser >> TilePivot;
	std::string Name;
	_Ser >> Name;


	int Count = 0;
	_Ser >> Count;
	for (size_t i = 0; i < Count; i++)
	{
		FTileData TileData;
		_Ser.Read(&TileData, sizeof(TileData));
		Tiles.insert({ TileData.Index.Key, TileData });
	}
}

void UTileMapRenderer::RenderNormal(class UEngineCamera* _Camera, float _DeltaTime)
{
	// URenderer::Render(_Camera, _DeltaTime);
	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();
	//	// 랜더러는 월드 뷰 프로젝트를 다 세팅받았고
	RendererTrans.View = CameraTrans.View;
	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;


	if (0 == Tiles.size())
	{
		return;
	}

	URenderUnit& Unit = GetRenderUnit();

	FTransform Trans;
	FMatrix Scale;
	FMatrix Pos;

	Scale.Scale(ImageSize);


	for (std::pair<const __int64, FTileData>& TilePair : Tiles)
	{
		//if (화면 바깥에 나간 타일은)
		//{
		//	continue;
		//}

		FTileData& Tile = TilePair.second;
		FTileIndex Index;

		GetRenderUnit().SetTexture("TileMapTex", Sprite->GetTexture(Tile.SpriteIndex));
		Tile.SpriteData = Sprite->GetSpriteData(Tile.SpriteIndex);
		Tile.SpriteData.Pivot = { 0.0f, 0.0f };

		Index.Key = TilePair.first;

		FVector ConvertPos = TileIndexToWorldPos(Index);

		Pos.Position({ ConvertPos.X, ConvertPos.Y, 0.0f });

		Trans.WVP = Scale * Pos * RendererTrans.View * RendererTrans.Projection;
		// 직교 투영이라는 것을 전제로 하고
		// -1 ~ 1사이의 값이 된다.

		// 직교투영일대의 스크린 out
		float OrthX = abs(Trans.WVP.ArrVector[3].Y);
		float OrthY = abs(Trans.WVP.ArrVector[3].X);

		if (1.0f <= OrthX || 1.0f <= OrthY)
		{
			continue;
		}

		GetRenderUnit().ConstantBufferLinkData("FTransform", Trans);

		GetRenderUnit().ConstantBufferLinkData("ResultColor", Tile.ColorData);
		GetRenderUnit().ConstantBufferLinkData("FSpriteData", Tile.SpriteData);

		// 한번한번 랜더유니트가 드로우 콜을 돌리는 구조가 된다.
		Unit.Render(_Camera, _DeltaTime);
	}
}

void UTileMapRenderer::RenderInstancing(class UEngineCamera* _Camera, float _DeltaTime)
{
	// URenderer::Render(_Camera, _DeltaTime);
	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();
	//	// 랜더러는 월드 뷰 프로젝트를 다 세팅받았고
	RendererTrans.View = CameraTrans.View;
	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = RendererTrans.World * RendererTrans.View * RendererTrans.Projection;


	if (0 == Tiles.size())
	{
		return;
	}

	URenderUnit& Unit = GetRenderUnit();

	FTransform Trans;
	FMatrix Scale;
	FMatrix Pos;

	Scale.Scale(ImageSize);

	// 메모리적 리사이즈가 발생하지 않는다.
	InstTransform.resize(Tiles.size());
	InstTransform.resize(InstColorData.size());
	InstTransform.resize(InstSpriteData.size());

	for (std::pair<const __int64, FTileData>& TilePair : Tiles)
	{
		FTileData& Tile = TilePair.second;
		FTileIndex Index;

		GetRenderUnit().SetTexture("TileMapTex", Sprite->GetTexture(Tile.SpriteIndex));
		Tile.SpriteData = Sprite->GetSpriteData(Tile.SpriteIndex);
		Tile.SpriteData.Pivot = { 0.0f, 0.0f };

		Index.Key = TilePair.first;

		FVector ConvertPos = TileIndexToWorldPos(Index);

		Pos.Position({ ConvertPos.X, ConvertPos.Y, 0.0f });

		Trans.WVP = Scale * Pos * RendererTrans.View * RendererTrans.Projection;
		// 직교 투영이라는 것을 전제로 하고
		// -1 ~ 1사이의 값이 된다.

		// 직교투영일대의 스크린 out
		float OrthX = abs(Trans.WVP.ArrVector[3].Y);
		float OrthY = abs(Trans.WVP.ArrVector[3].X);

		if (1.0f <= OrthX || 1.0f <= OrthY)
		{
			continue;
		}

		// 데이터를 수집하는 비용이 발생하기 때문에
		// 어떤때는 더 느려질수도 있다.
		// 그리고 여러분들 생각보다 더 20~30% 효율을 보입니다.
		// 컴퓨트까지 가야 합니다.
		// 데이터 수집도 그래픽 카드에 맡기면 쫌더 빨라짐.
		InstTransform.push_back(Trans);
		InstColorData.push_back(Tile.ColorData);
		InstSpriteData.push_back(Tile.SpriteData);
	}

	// 랜더링 1번 되니
	// GetRenderUnit().ConstantBufferLinkData("FTransform", Trans);
	// GetRenderUnit().ConstantBufferLinkData("ResultColor", Tile.ColorData);
	// GetRenderUnit().ConstantBufferLinkData("FSpriteData", Tile.SpriteData);
	// 한번 딱 랜더하는 구조가 될 것입니다.
	// Unit.Render(_Camera, _DeltaTime);
}