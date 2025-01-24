#include <../EngineShader/RenderBaseData.hlsli>

struct FEngineVertex
{
    float4 POSITION : POSITION;
    float4 UV : TEXCOORD;
};

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION; // ����Ʈ����� �������� �������Դϴ�.
    float4 UV : TEXCOORD; // 
};

// ���ؽ����̴��� �� �������.
VertexShaderOutPut Effect_VS(FEngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;
    OutPut.SVPOSITION = _Vertex.POSITION;
    OutPut.UV = _Vertex.UV;
	
    OutPut.UV.xy += AccTime + 1.0f;
    return OutPut;
}


// �̹����� ���ø��ؼ� �̹����� ���̰� �����
float4 Effect_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
    if (_Vertex.UV.x < 0)
    {
        return float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
	
    if (_Vertex.UV.y < 0)
    {
        return float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
	
    if (_Vertex.UV.x > 1.0f)
    {
        return float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
	
    if (_Vertex.UV.y > 1.0f)
    {
        return float4(0.0f, 0.0f, 0.0f, 1.0f);
    }
	
	
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
};
