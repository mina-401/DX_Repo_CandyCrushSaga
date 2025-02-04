#include "Transform.hlsli"

struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

// 버텍스 쉐이더는 무조건 리턴값이 있어야 합니다.
// 인풋어셈블러2로 넘길 값을 리턴해줘야하는데.
// 이때도 규칙이 있습니다.

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 UV : TEXCOORD; // 
    float4 COLOR : COLOR;
};

// 상수버퍼는 아무것도 세팅해주지 않으면 기본값이 0으로 채워집니다.
cbuffer FSpriteData : register(b1)
{
    float4 CuttingPos;
    float4 CuttingSize;
    float4 Pivot; // 0.5 0.0f
};

cbuffer FUVValue : register(b2)
{
    float4 PlusUVValue;
};

// 버텍스쉐이더를 다 만들었다.
VertexShaderOutPut SpriteRender_VS(EngineVertex _Vertex)
{
	// CPU에서 계산한 값을 쉐이더에게 넘기는 방법을 알아야 하는데
	// 상수버퍼라고 부릅니다.
	// 그중에서 가장 기본적인 것은 상수버퍼를 
	
	// float4x4 WVP;
	
    VertexShaderOutPut OutPut;
	
	
    _Vertex.POSITION.x += (1.0f - Pivot.x) - 0.5f;
    _Vertex.POSITION.y += (1.0f - Pivot.y) - 0.5f;
	
    _Vertex.POSITION.w = 1.0f;
	
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
	
    OutPut.UV = _Vertex.UV;
    OutPut.UV.x = (_Vertex.UV.x * CuttingSize.x) + CuttingPos.x;
    OutPut.UV.y = (_Vertex.UV.y * CuttingSize.y) + CuttingPos.y;
    OutPut.UV.x += PlusUVValue.x;
    OutPut.UV.y += PlusUVValue.y;
	
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}


Texture2D ImageTexture : register(t0);
// 샘플러 1개가 필요합니다.
SamplerState ImageSampler : register(s0);

// 쉐이더끼리는 상수버퍼 인덱스 겹쳐도 상관 없다.
// ex) 버텍스쉐이더에서 0번 상수버퍼를 썼어도
// ex) 픽셀쉐이더에서는 0번 을 쓸수 있다.
cbuffer ResultColor : register(b0)
{
    float4 PlusColor;
    float4 MulColor;
};

// 이미지를 샘플링해서 이미지를 보이게 만들고
float4 SpriteRender_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
	
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
	
    if (0.0f >= Color.a)
    {
		// 픽셀쉐이더에서 아웃풋 머저로 넘기지 않는다.
        clip(-1);
    }
	
    Color += PlusColor;
    Color *= MulColor;
    return Color;
};
