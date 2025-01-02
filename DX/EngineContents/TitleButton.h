#pragma once

// Ό³Έν :
class TitleButton
{
public:
	// constrcuter destructer
	TitleButton();
	~TitleButton();

	// delete Function
	TitleButton(const TitleButton& _Other) = delete;
	TitleButton(TitleButton&& _Other) noexcept = delete;
	TitleButton& operator=(const TitleButton& _Other) = delete;
	TitleButton& operator=(TitleButton&& _Other) noexcept = delete;

protected:

private:

};

