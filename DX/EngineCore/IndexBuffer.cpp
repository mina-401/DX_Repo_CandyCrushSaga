#include "PreCompile.h"
#include "IndexBuffer.h"
#include "EngineCore.h"

UIndexBuffer::UIndexBuffer()
{
}

UIndexBuffer::~UIndexBuffer()
{
}

std::shared_ptr<UIndexBuffer> UIndexBuffer::Create(std::string_view _Name, const void* _InitData, size_t _VertexSize, size_t _VertexCount)
{
	std::string UpperName = ToUpperName(_Name);

	if (true == Contains(UpperName))
	{
		MSGASSERT("이미 로드한 텍스처를 도 로드하려고 했습니다." + UpperName);
		return nullptr;
	}

	std::shared_ptr<UIndexBuffer> NewRes = std::make_shared<UIndexBuffer>();
	PushRes<UIndexBuffer>(NewRes, _Name, "");
	NewRes->ResCreate(_InitData, _VertexSize, _VertexCount);

	return NewRes;
}

void UIndexBuffer::ResCreate(const void* _InitData, size_t _Size, size_t _Count)
{
	IndexSize = static_cast<UINT>(_Size);
	IndexCount = static_cast<UINT>(_Count);

	if (4 == IndexSize) // 42억
	{
		Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
	}
	else if (2 == IndexSize) // 65536
	{
		Format = DXGI_FORMAT::DXGI_FORMAT_R16_UINT;
	}
	else
	{
		MSGASSERT("이런 인덱스 포맷은 지원하지 않습니다.");
	}

	BufferInfo.ByteWidth = static_cast<UINT>(_Size * _Count);
	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data; // 초기값 넣어주는 용도의 구조체
	Data.pSysMem = _InitData;

	if (S_OK != UEngineCore::GetDevice().GetDevice()->CreateBuffer(&BufferInfo, &Data, &IndexBuffer))
	{
		MSGASSERT("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void UIndexBuffer::Setting()
{
	int Offset = 0;
	UEngineCore::GetDevice().GetContext()->IASetIndexBuffer(IndexBuffer.Get(), Format, Offset);
}