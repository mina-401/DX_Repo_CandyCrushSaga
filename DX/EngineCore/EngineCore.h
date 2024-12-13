#pragma once
#include <EngineBase/EngineDefine.h>

// 설명 :
class UEngineCore
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineCore();
	ENGINEAPI virtual ~UEngineCore() =0; //엔진코어 인스턴스 사용 안함

	ENGINEAPI static void EngineStart(HINSTANCE _Instance);

	// delete Function
	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

protected:

private:

};

