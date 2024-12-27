#pragma once
#include <EngineCore/Renderer.h>

// ���� :
class MyRenderer : public URenderer
{
public:
	// constrcuter destructer
	MyRenderer();
	~MyRenderer();

	// delete Function
	MyRenderer(const MyRenderer& _Other) = delete;
	MyRenderer(MyRenderer&& _Other) noexcept = delete;
	MyRenderer& operator=(const MyRenderer& _Other) = delete;
	MyRenderer& operator=(MyRenderer&& _Other) noexcept = delete;

protected:

private:

};

