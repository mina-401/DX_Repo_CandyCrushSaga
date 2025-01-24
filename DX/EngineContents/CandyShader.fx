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

cbuffer FSpriteData : register(b1)
{
    float4 CuttingPos;
    float4 CuttingSize;
    float4 Pivot; // 0.5 0.0f
};

// ���ؽ����̴��� �� �������.
VertexShaderOutPut CandySpriteRender_VS(EngineVertex _Vertex)
{
    VertexShaderOutPut OutPut;
	
	
    _Vertex.POSITION.x += (1.0f - Pivot.x) - 0.5f;
    _Vertex.POSITION.y += (1.0f - Pivot.y) - 0.5f;
	
    OutPut.SVPOSITION = mul(_Vertex.POSITION, WVP);
	
    OutPut.UV = _Vertex.UV;
    OutPut.UV.x = (_Vertex.UV.x * CuttingSize.x) + CuttingPos.x;
    OutPut.UV.y = (_Vertex.UV.y * CuttingSize.y) + CuttingPos.y;
	
    //_Vertex.COLOR.z = 1.0f;
    OutPut.COLOR = _Vertex.COLOR;
	
    return OutPut;
}


Texture2D ImageTexture : register(t0);
// ���÷� 1���� �ʿ��մϴ�.
SamplerState ImageSampler : register(s0);


// �̹����� ���ø��ؼ� �̹����� ���̰� �����
float4 CandySpriteRender_PS(VertexShaderOutPut _Vertex) : SV_Target0
{
	
    float4 Color = ImageTexture.Sample(ImageSampler, _Vertex.UV.xy);
	
    if (0.95f >= Color.a)
    {
        //Color.a = 0.1f;
		// �ȼ����̴����� �ƿ�ǲ ������ �ѱ��� �ʴ´�.
        clip(-1);
    }
    return Color;
};
