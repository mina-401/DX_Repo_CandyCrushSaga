struct EngineVertex
{
	float4 POSITION : POSITION;
	float4 UV : TEXCOORD;
	float4 COLOR : COLOR;
};

// ���ؽ� ���̴��� ������ ���ϰ��� �־�� �մϴ�.
// ��ǲ�������2�� �ѱ� ���� ����������ϴµ�.
// �̶��� ��Ģ�� �ֽ��ϴ�.

struct VertexShaderOutPut
{
	float4 SVPOSITION : SV_POSITION; // ����Ʈ����� �������� �������Դϴ�.
	float4 UV : TEXCOORD; // 
	float4 COLOR : COLOR;
};

// ������۸� ����ϰڴ�.
cbuffer FTransform : register(b0)
{
	// transformupdate�� 
	// �Ʒ��� ������ �� �����ؼ�
	// WVP�� ������ �Լ��̴�.
	// ��ȯ�� ����
	float4 Scale;
	float4 Rotation;
	float4 Qut;
	float4 Location;

	// ������Ƽ�� ����
	float4 RelativeScale;
	float4 RelativeRotation;
	float4 RelativeQut;
	float4 RelativeLocation;

	// ����
	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldQuat;
	float4 WorldLocation;

	float4x4 ScaleMat;
	float4x4 RotationMat;
	float4x4 LocationMat;
	float4x4 RevolveMat;
	float4x4 ParentMat;
	float4x4 LocalWorld;
	float4x4 World;
	float4x4 View;
	float4x4 Projection;
	float4x4 WVP;
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

// ���ؽ� ���̴����� ������ _VS
VertexShaderOutPut VertexToWorld_VS(EngineVertex _Vertex)
{
	// CPU���� ����� ���� ���̴����� �ѱ�� ����� �˾ƾ� �ϴµ�
	// ������۶�� �θ��ϴ�.
	// ���߿��� ���� �⺻���� ���� ������۸� 
	
	// float4x4 WVP;
	VertexShaderOutPut OutPut;
	
	
	// Pivot.x = '0.5f' => 0.0f
	// Pivot.y = '0.0f' => 0.5f
	
	// Pivot.x = '0.5f' => 0.0f
	// Pivot.y = '0.5f' => 0.0f
	
	//                     1.0f - 0.5           
	_Vertex.POSITION.x += (1.0f - Pivot.x) - 0.5f;
	_Vertex.POSITION.y += (1.0f - Pivot.y) - 0.5f;
	
	OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
	
	OutPut.UV.x = (_Vertex.UV.x * CuttingSize.x) + CuttingPos.x;
	OutPut.UV.y = (_Vertex.UV.y * CuttingSize.y) + CuttingPos.y;
	OutPut.UV.x += PlusUVValue.x;
	OutPut.UV.y += PlusUVValue.y;
	
	
	OutPut.COLOR = _Vertex.COLOR;
	return OutPut;
}

// ������۴� �ƹ��͵� ���������� ������ �⺻���� 0���� ä�����ϴ�.
cbuffer MatColor : register(b1)
{
	float4 Albedo;
};


struct OutTargetColor
{
	float4 Target0 : SV_Target0; // ����Ʈ����� �������� �������Դϴ�.
	float4 Target1 : SV_Target1; // ����Ʈ����� �������� �������Դϴ�.
	float4 Target2 : SV_Target2; // ����Ʈ����� �������� �������Դϴ�.
	float4 Target3 : SV_Target3; // ����Ʈ����� �������� �������Դϴ�.
	float4 Target4 : SV_Target4; // ����Ʈ����� �������� �������Դϴ�.
	float4 Target5 : SV_Target5; // ����Ʈ����� �������� �������Դϴ�.
	float4 Target6 : SV_Target6; // ����Ʈ����� �������� �������Դϴ�.
	float4 Target7 : SV_Target7; // ����Ʈ����� �������� �������Դϴ�.
};


// �ؽ�ó 1��� 
Texture2D ImageTexture : register(t0);
// ���÷� 1���� �ʿ��մϴ�.
SamplerState ImageSampler : register(s0);

// �̹����� ���ø��ؼ� �̹����� ���̰� �����
float4 PixelToWorld_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
	
	// ImageTexture.Load({0,0));
	float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
	return Color;
	
	// return float4(1.0f, 0.0f, 0.0f, 1.0f);
};