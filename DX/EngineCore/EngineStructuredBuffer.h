#pragma once
#include "EngineResources.h"
#include "EngineDeviceBuffer.h"
#include "EngineEnums.h"

// 타일맵이 2개라고 합니다.
// 300바이트짜리 100개 짜리 타일맵이 있고
// 300바이트짜리 80개 짜리 타일맵이 있다.


	// 설명 :
class UEngineStructuredBuffer : public UEngineResources, public UEngineDeviceBuffer
{
	friend class UEngineShaderResources;

public:
	// constrcuter destructer
	UEngineStructuredBuffer();
	~UEngineStructuredBuffer();

	// delete Function
	UEngineStructuredBuffer(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer(UEngineStructuredBuffer&& _Other) noexcept = delete;
	UEngineStructuredBuffer& operator=(const UEngineStructuredBuffer& _Other) = delete;
	UEngineStructuredBuffer& operator=(UEngineStructuredBuffer&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineStructuredBuffer> CreateOrFind(UINT _Byte, const std::string_view& _Name);

	void ChangeData(void* _Data, UINT _Size);
	void Setting(EShaderType _Type, UINT _BindIndex);

	static void Release();

protected:

private:
	static std::map<int, std::map<std::string, std::shared_ptr<UEngineStructuredBuffer>>> BufferMap;

	// 카운트 스트럭처드 버퍼는 그래픽카드가 허용하는 어마어마한 크기의 상수버퍼를 만들수가 있다.
	// 100 바이트 짜리 어떤 데이터는 10000개 만들어줘
	void ResCreate(UINT _DataSize, UINT _DataCount);

	UINT DataSize = 0;
	UINT DataCount = 0;

	// 대용량 데이터는 텍스처와 슬롯 공유한다.
	// regaster(t0)
	// 세팅하기 위해서 SRV
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> SRV = nullptr;
};

