#include "PreCompile.h"
#include "EngineStructuredBuffer.h"
#include "EngineCore.h"

std::map<int, std::map<std::string, std::shared_ptr<UEngineStructuredBuffer>>> UEngineStructuredBuffer::BufferMap;

void UEngineStructuredBuffer::Release()
{
	BufferMap.clear();
}

UEngineStructuredBuffer::UEngineStructuredBuffer()
{
}

UEngineStructuredBuffer::~UEngineStructuredBuffer()
{
}

std::shared_ptr<UEngineStructuredBuffer> UEngineStructuredBuffer::CreateOrFind(UINT _Byte, const std::string_view& _Name)
{
	if (0 == _Byte)
	{
		MSGASSERT("0바이트 상수버퍼가 만들어지려고 했습니다.");
	}

	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == BufferMap.contains(_Byte))
	{
		if (true == BufferMap[_Byte].contains(UpperName))
		{
			return BufferMap[_Byte][UpperName];
		}
	}

	// 최초로 만들어지는 순간이다.
	std::shared_ptr<UEngineStructuredBuffer> NewRes = std::make_shared<UEngineStructuredBuffer>();
	NewRes->SetName(UpperName);
	NewRes->ResCreate(_Byte, 1);
	BufferMap[_Byte][UpperName] = NewRes;

	return NewRes;
}

void UEngineStructuredBuffer::ResCreate(UINT _DataSize, UINT _DataCount)
{
	// 20 30 40 50 60 
	// _BindIndex 여기가 계속 바뀌어서 들어올수 있다.
	// 프로그래밍에서 최악의 선택이기 때문이다.
	// 이번에 comptr을 사용했다.

	Buffer = nullptr;

	{
		DataCount = _DataCount;
		DataSize = _DataSize;
		BufferInfo.ByteWidth = _DataCount * _DataSize;
		// 텍스처로 보기 대문에
		BufferInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		BufferInfo.Usage = D3D11_USAGE_DYNAMIC;
		BufferInfo.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 스트럭처드 버처
		BufferInfo.StructureByteStride = _DataSize; // 1개의 데이터 크기가 얼마인지 알려줘야 한다.

		if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
		{
			MSGASSERT("스트럭처드 버퍼 생성에 실패했습니다..");
			return;
		}

		// SRV 정보체를 넣어줘야 합니다.
		// Texture랑 다르다.
		// Texture는 SRV를 그냥만들어 줄수 있지만
		// 지금처럼 버퍼에서 얻어내는건 달라요.

		D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
		// directx에서는 texture에 배열을걸수가 있다.
		// 그 배열을 달려달라는 것이다. 
		// 애니는 텍스처가 아니다.BUFFER 에서부터 탄생한 SRV라는 것을 알려주는것.
		tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
		tSRVDesc.Format = DXGI_FORMAT_UNKNOWN;
		// 버퍼의 어디서 부터 쓸거냐.
		tSRVDesc.BufferEx.FirstElement = 0;
		// Flage
		tSRVDesc.BufferEx.Flags = 0;
		// 배열의 카운트
		tSRVDesc.BufferEx.NumElements = DataCount; 

		if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateShaderResourceView(Buffer.Get(), &tSRVDesc, &SRV))
		{
			MSGASSERT("스트럭처드 버퍼 생성에 실패했습니다..");
			return;
		}


	}
}

void UEngineStructuredBuffer::ChangeData(void* _Data, UINT _Size)
{
	if (_Size != BufferInfo.ByteWidth)
	{
		MSGASSERT("바이트 크기가 다르게 세팅되었습니다" + GetName());
		return;
	}

	// FTransform& RendererTrans = GetTransformRef();
	D3D11_MAPPED_SUBRESOURCE Data = {};
	// 이 데이터를 사용하는 랜더링 랜더링 잠깐 정지
	// 잠깐 그래픽카드야 멈 그래픽카드에 있는 상수버퍼 수정해야 해.
	UEngineCore::GetDevice().GetContext()->Map(Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	// Data.pData 그래픽카드와 연결된 주소값.
	if (nullptr == Data.pData)
	{
		MSGASSERT("그래픽카드가 수정을 거부했습니다.");
	}
	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);
	UEngineCore::GetDevice().GetContext()->Unmap(Buffer.Get(), 0);
}

void UEngineStructuredBuffer::Setting(EShaderType _Type, UINT _BindIndex)
{
	// 같은 상수버퍼를 
	ID3D11Buffer* ArrPtr[1] = { Buffer.Get() };

	switch (_Type)
	{
	case EShaderType::VS:
		UEngineCore::GetDevice().GetContext()->VSSetShaderResources(_BindIndex, 1, &SRV);
		break;
	case EShaderType::PS:
		UEngineCore::GetDevice().GetContext()->PSSetShaderResources(_BindIndex, 1, &SRV);
		break;
	case EShaderType::HS:
	case EShaderType::DS:
	case EShaderType::GS:
	case EShaderType::CS:
	default:
		MSGASSERT("아직 존재하지 않는 쉐이더에 세팅하려고 했습니다.");
		break;
	}
}
