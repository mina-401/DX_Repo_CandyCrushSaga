#pragma once
#include <EngineCore/IContentsCore.h>

// 규칙을 만드는 수밖에 없다.

// 설명 :
class UCandyCrushSaga : public IContentsCore
{
public:
	// constrcuter destructer
	UCandyCrushSaga();
	~UCandyCrushSaga();

	// delete Function
	UCandyCrushSaga(const UCandyCrushSaga& _Other) = delete;
	UCandyCrushSaga(UCandyCrushSaga&& _Other) noexcept = delete;
	UCandyCrushSaga& operator=(const UCandyCrushSaga& _Other) = delete;
	UCandyCrushSaga& operator=(UCandyCrushSaga&& _Other) noexcept = delete;

protected:
	void EngineStart(UEngineInitData& _Data);
	void EngineTick(float _DeltaTime);
	void EngineEnd();

private:
	void CandyGSetting();
};

