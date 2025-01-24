#include "PreCompile.h"
#include "CustomCandyRenderer.h"
#include <EngineCore/EngineCamera.h>
#include <EngineBase/EngineDebug.h>

UCustomCandyRenderer::UCustomCandyRenderer()
{
	CreateRenderUnit();
	SetMesh("Rect");
	SetMaterial("CandyMaterial");
	SpriteData.CuttingPos = { 0.0f, 0.0f };
	SpriteData.CuttingSize = { 1.0f, 1.0f };
	SpriteData.Pivot = { 0.5f, 0.5f };
	GetRenderUnit().ConstantBufferLinkData("FSpriteData", SpriteData);
}

UCustomCandyRenderer::~UCustomCandyRenderer()
{
}

void UCustomCandyRenderer::SetSprite(std::string_view _Name, UINT _Index)
{
	Sprite = UEngineSprite::Find<UEngineSprite>(_Name).get();

	GetRenderUnit().SetTexture("ImageTexture", Sprite->GetTexture(_Index)->GetName());
	SpriteData = Sprite->GetSpriteData(_Index);

	CurIndex = _Index;
}

void UCustomCandyRenderer::SetTexture(std::string_view _Name, bool AutoScale /*= false*/, float _Ratio /*= 1.0f*/)
{
	std::shared_ptr<UEngineTexture> Texture = UEngineTexture::Find<UEngineTexture>(_Name);

	if (nullptr == Texture)
	{
		MSGASSERT("로드하지 않은 텍스처를 사용하려고 했습니다.");
	}

	GetRenderUnit().SetTexture("ImageTexture", _Name);

	if (true == AutoScale)
	{
		SetRelativeScale3D(Texture->GetTextureSize() * _Ratio);
	}
}

void UCustomCandyRenderer::BeginPlay()
{
	URenderer::BeginPlay();

}
void UCustomCandyRenderer::Render(UEngineCamera* _Camera, float _DeltaTime)
{
	

	if (true == IsAutoScale && nullptr != Sprite)
	{
		FVector Scale = Sprite->GetSpriteScaleToReal(CurIndex);
		Scale.Z = 1.0f;
		SetRelativeScale3D(Scale * AutoScaleRatio);
	}

	URenderer::Render(_Camera, _DeltaTime);

}
void UCustomCandyRenderer::ComponentTick(float _DeltaTime)
{
	URenderer::ComponentTick(_DeltaTime);


}

void UCustomCandyRenderer::CameraTransUpdate(UEngineCamera* _Camera)
{
	FTransform& CameraTrans = _Camera->GetTransformRef();
	FTransform& RendererTrans = GetTransformRef();

	RendererTrans.View = CameraTrans.View;
	FMatrix CurWorld = RendererTrans.World;


	RendererTrans.Projection = CameraTrans.Projection;
	RendererTrans.WVP = CurWorld * RendererTrans.View * RendererTrans.Projection;
}
void UCustomCandyRenderer::SetSprite(UEngineSprite* _Sprite)
{
	Sprite = _Sprite;

	if (nullptr == Sprite)
	{
		MSGASSERT("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}
}