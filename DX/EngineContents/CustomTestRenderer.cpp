#include "PreCompile.h"
#include "CustomTestRenderer.h"

UCustomTestRenderer::UCustomTestRenderer()
{
	CreateRenderUnit();
	SetMesh("Rect");
	SetMaterial("CandyBackgroundMaterial");
	MyColor.Albedo = float4(1.0f, 1.0f, 1.0f, 1.0f);
	GetRenderUnit().ConstantBufferLinkData("FMyColor", MyColor);
}

UCustomTestRenderer::~UCustomTestRenderer()
{
}

