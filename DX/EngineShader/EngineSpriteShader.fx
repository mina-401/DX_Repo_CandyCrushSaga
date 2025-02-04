#include "Transform.hlsli"

struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 UV : TEXCOORD;
    float4 COLOR : COLOR;
};

// ���ؽ� ���̴��� ������ ���ϰ��� �־�� �մϴ�.
// ��ǲ�����2�� �ѱ� ���� ����������ϴµ�.
// �̶��� ��Ģ�� �ֽ��ϴ�.

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION; // ����Ʈ����� �������� �������Դϴ�.
    float4 UV : TEXCOORD; // 
    float4 COLOR : COLOR;
};

// ������۴� �ƹ��͵� ���������� ������ �⺻���� 0���� ä�����ϴ�.
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

// ���ؽ����̴��� �� �������.
VertexShaderOutPut SpriteRender_VS(EngineVertex _Vertex)
{
	// CPU���� ����� ���� ���̴����� �ѱ�� ����� �˾ƾ� �ϴµ�
	// ������۶�� �θ��ϴ�.
	// ���߿��� ���� �⺻���� ���� ������۸� 
	
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
// ���÷� 1���� �ʿ��մϴ�.
SamplerState ImageSampler : register(s0);

// ���̴������� ������� �ε��� ���ĵ� ��� ����.
// ex) ���ؽ����̴����� 0�� ������۸� ��
// ex) �ȼ����̴������� 0�� �� ���� �ִ�.
cbuffer ResultColor : register(b0)
{
    float4 PlusColor;
    float4 MulColor;
};

// �̹����� ���ø��ؼ� �̹����� ���̰� �����
float4 SpriteRender_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
	
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
	
    if (0.0f >= Color.a)
    {
		// �ȼ����̴����� �ƿ�ǲ ������ �ѱ��� �ʴ´�.
        clip(-1);
    }
	
    Color += PlusColor;
    Color *= MulColor;
    return Color;
};
