#pragma once

// Ό³Έν :
class UEngineRasterizerState
{
public:
	// constrcuter destructer
	UEngineRasterizerState();
	~UEngineRasterizerState();

	// delete Function
	UEngineRasterizerState(const UEngineRasterizerState& _Other) = delete;
	UEngineRasterizerState(UEngineRasterizerState&& _Other) noexcept = delete;
	UEngineRasterizerState& operator=(const UEngineRasterizerState& _Other) = delete;
	UEngineRasterizerState& operator=(UEngineRasterizerState&& _Other) noexcept = delete;

protected:

private:

};

