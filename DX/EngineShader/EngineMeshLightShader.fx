#include "Light.hlsli"
#include "Transform.hlsli"

struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD; // UV���̶�� �Ҹ��� ����� �ؽ�ó�� ���εǴ� ������ �������ݴϴ�.
    float4 COLOR : COLOR;
    float4 NORMAL : NORMAL; // ���� ���� ���Ͱ� �ʿ��ϴ�.
    float4 BINORMAL : BINORMAL; // ���� ������ ���� �����Ͱ� ź��Ʈ ������ ����� ���Ѱ�.
    float4 TANGENT : TANGENT; // ���� ������ ���� �����Ͱ� ź��Ʈ ������ ����� ���Ѱ�.
};

// ���ؽ� ���̴��� ������ ���ϰ��� �־�� �մϴ�.
// ��ǲ�����2�� �ѱ� ���� ����������ϴµ�.
// �̶��� ��Ģ�� �ֽ��ϴ�.

struct VertexShaderOutPut
{
	// ������ ���������λ� ViewPort ����� ��������
    float4 SVPOSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 COLOR : COLOR;
	
    float4 VIEWPOS : POSITION;
    float4 NORMAL : NORMAL;
    float4 BINORMAL : BINORMAL;
    float4 TANGENT : TANGENT;
};




VertexShaderOutPut MeshLight_VS(EngineVertex _Vertex /*, int _DataIndex*/)
{
    VertexShaderOutPut OutPut;
	
	// ����Ͱ��� �� �������� �ȴ�.
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
    OutPut.TEXCOORD = _Vertex.TEXCOORD;
    OutPut.COLOR = _Vertex.COLOR;
	// ���� �Ϲ������� ��������� ����մϴ�.
	// ��������� �븻�� ���¾�
	
	// ��������� ���� �������� �˴ϴ�.
    OutPut.VIEWPOS = mul(_Vertex.POSITION, World * View);
	
	// �Ǽ��� w�� 1�� ���� �̵����� ����ް� �ȴ�.
	// �׷��Ƿ� �̵����� ����Ǵ°��� Ȯ���ϰ� �����ϱ� ���ؼ� w�� �Ű���ִ°� ����.
    _Vertex.NORMAL.w = 0.0f;
    OutPut.NORMAL = mul(_Vertex.NORMAL, World * View);
	
    _Vertex.BINORMAL.w = 0.0f;
    OutPut.BINORMAL = mul(_Vertex.BINORMAL, World * View);
	
    _Vertex.TANGENT.w = 0.0f;
    OutPut.TANGENT = mul(_Vertex.TANGENT, World * View);
	
	// �� �������� ���⿡�� �ع����� �ѱ�� ��ν��̵��̶�� �Ѵ�.
	// OutPut.LIGHTCOLOR = 
	
    return OutPut;
}

cbuffer MeshColor : register(b0)
{
    float4 SettingColor;
};

float4 MeshLight_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
    float4 ResultColor;
    ResultColor = SettingColor;
	
	// ���⼭ 
    float4 DiffuseColor = CalDiffusLight(_Vertex.NORMAL, LightArr[0]);
    float4 SpacularLight = CalSpacularLight(_Vertex.VIEWPOS, _Vertex.NORMAL, LightArr[0]);
	
    ResultColor.xyz *= (DiffuseColor + SpacularLight);
    ResultColor.a = 1.0f;
	
    return ResultColor;
	// return float4(1.0f, 0.0f, 0.0f, 1.0f);
};

