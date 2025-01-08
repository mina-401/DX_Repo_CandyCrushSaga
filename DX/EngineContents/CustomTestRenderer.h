#pragma once
#include <EngineCore/Renderer.h>

struct FMyColor
{
	float4 Albedo;
};

// Ό³Έν :
class UCustomTestRenderer : public URenderer
{
public:
	// constrcuter destructer
	UCustomTestRenderer();
	~UCustomTestRenderer();

	// delete Function
	UCustomTestRenderer(const UCustomTestRenderer& _Other) = delete;
	UCustomTestRenderer(UCustomTestRenderer&& _Other) noexcept = delete;
	UCustomTestRenderer& operator=(const UCustomTestRenderer& _Other) = delete;
	UCustomTestRenderer& operator=(UCustomTestRenderer&& _Other) noexcept = delete;

protected:

private:
	FMyColor MyColor;
};

