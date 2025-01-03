#include "PreCompile.h"
#include "CustomTestRenderer.h"

CustomTestRenderer::CustomTestRenderer()
{
	CreateRenderUnit();
	SetMesh("Rect");
	SetMaterial("MyTestMaterial");
	MyColor.Albedo = float4(1.0f, 1.0f, 1.0f, 1.0f);
	GetRenderUnit().ConstantBufferLinkData("FMyColor", MyColor);
}

CustomTestRenderer::~CustomTestRenderer()
{
}

