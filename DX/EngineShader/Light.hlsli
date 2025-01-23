// ���� ����ϱ� ���� ������ۿ� ����ü
struct FLightData
{
    float4 LightPos; // ���� ��ġ
    float4 LightDir; // ���� Forward
    float4 LightRevDir; // ���� �ݴ������ < L!!!!! <= 
    float4 LightColor;
    float4 AmbientLight;
    float4 ViewLightPos;
    float4 ViewLightDir;
    float4 ViewLightRevDir;
    float4 CameraPosition;
};

cbuffer FLightDatas : register(b11)
{
    int Count;
    FLightData LightArr[256];
};

// ��������� �����Լ��� ����� �ִ�.
// ����� ���۷����� �����Ͱ��� ������ Hlsl���������� �������� �ʴ´�.

// N���� L

float4 CalSpacularLight(float4 _ViewPos, float4 _ViewNormal, FLightData _Data)
{
    float ResultLight = 0.0f;

    float4 N = normalize(_ViewNormal);
    float4 L = normalize(_Data.ViewLightRevDir);
	
	// �ݻ� ���͸� ���Ҽ��� �ִ�.
    float3 Reflection = normalize(2.0f * N.xyz * dot(L.xyz, N.xyz) - L.xyz);
	
    float3 Eye = normalize(_ViewPos.xyz - _Data.CameraPosition.xyz);
	
	// 0~1������ ���� ���ü� �ۿ� ����.
    ResultLight = max(0.0f, dot(Reflection.xyz, Eye.xyz));
	
	// ���� �ٶ󺸴� ��������� ������ �ݻ纤�͸� ���մϴ�.
	
    ResultLight = pow(ResultLight, 30.0f);
	
	// float4 Reflection
    return ResultLight;
}

float4 CalDiffusLight(float4 _ViewNormal, FLightData _Data)
{
    float4 N = normalize(_ViewNormal);
    float4 L = normalize(_Data.ViewLightRevDir);
	// _Data.LightRevDir ������� �����ϴ� �༮�̾�� ������ �����Ѵ�.
	
	// Ratio������ ����� ��
    float ResultLight;
	
	// ������(swizzling) ���� Hlsl������ ��밡��
	// .xz
    ResultLight = dot(N, L);
	
	// ������ ���ü��� �ֱ� ������.
	// �ּҰ��� 0���� ����    �ּҰ�  �ִ밪
    ResultLight = max(0.0f, ResultLight);
	
	// ���� ����
    return ResultLight * 0.5f;

}

