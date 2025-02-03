#include <../EngineShader/RenderBaseData.hlsli>

struct FEngineVertex
{
    float4 POSITION : POSITION;
    float4 UV : TEXCOORD;
};

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION; // 뷰포트행렬이 곱해지는 포지션입니다.
    float4 UV : TEXCOORD; // 
};

// 버텍스쉐이더를 다 만들었다.
VertexShaderOutPut Effect_VS(FEngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;
    OutPut.SVPOSITION = _Vertex.POSITION;
    OutPut.UV = _Vertex.UV;
	
    //OutPut.UV.xy += AccTime + 1.0f;
    return OutPut;
}

Texture2D ImageTexture : register(t1);
SamplerState ImageSampler : register(s1);
// 이미지를 샘플링해서 이미지를 보이게 만들고
float4 Effect_PS(VertexShaderOutPut _Vertex) : SV_Target0
{

    return float4(1.0f, 0.0f, 0.0f, 1.0f);
};
