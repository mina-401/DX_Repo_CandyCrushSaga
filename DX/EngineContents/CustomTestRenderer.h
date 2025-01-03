#pragma once
#include <EngineCore/Renderer.h>

struct FMyColor
{
	float4 Albedo;
};

// Ό³Έν :
class CustomTestRenderer : public URenderer
{
public:
	// constrcuter destructer
	CustomTestRenderer();
	~CustomTestRenderer();

	// delete Function
	CustomTestRenderer(const CustomTestRenderer& _Other) = delete;
	CustomTestRenderer(CustomTestRenderer&& _Other) noexcept = delete;
	CustomTestRenderer& operator=(const CustomTestRenderer& _Other) = delete;
	CustomTestRenderer& operator=(CustomTestRenderer&& _Other) noexcept = delete;

protected:

private:
	FMyColor MyColor;
};

