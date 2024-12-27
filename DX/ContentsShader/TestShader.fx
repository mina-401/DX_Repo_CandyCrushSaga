struct EngineVertex
{
    float4 POSITION : POSITION;
    float4 COLOR : COLOR;
};

struct VertexShaderOutPut
{
    float4 SVPOSITION : SV_POSITION; // ����Ʈ����� �������� �������Դϴ�.
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

VertexShaderOutPut TestToVertex(EngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
    OutPut.COLOR = _Vertex.COLOR;
    return OutPut;
}

float4 TestToPixel(VertexShaderOutPut _Vertex) : SV_Target0
{
    return float4(1.0f, 0.0f, 0.0f, 1.0f);
}