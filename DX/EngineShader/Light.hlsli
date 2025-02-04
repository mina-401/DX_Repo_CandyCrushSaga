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
    int LightCount;
    FLightData LightArr[256];
};

// ��������� �����Լ��� ����� �ִ�.
// ����� ���۷����� �����Ͱ��� ������ Hlsl���������� �������� �ʴ´�.

// N���� L

float4 CalSpacularLight(float4 _ViewPos, float4 _ViewNormal, FLightData _Data)
{
    float4 ResultRatio = 0.0f;
    
    float3 N = normalize(_ViewNormal.xyz);
    float3 L = normalize(_Data.ViewLightRevDir.xyz);
    
    float3 ReflectionN = normalize(2.0f * dot(N.xyz, L.xyz) * _ViewNormal.xyz - L.xyz);
    ReflectionN = normalize(ReflectionN);
    
    float3 EyeL = normalize(_Data.CameraPosition.xyz - _ViewPos.xyz);
    
    float Result = max(0.0f, dot(EyeL.xyz, ReflectionN.xyz));
    ResultRatio.xyzw = pow(Result, 30.0f);
    
    return ResultRatio;
}

float4 CalDiffusLight(float4 _ViewNormal, FLightData _Data)
{
    float3 N = normalize(_ViewNormal.xyz);
    float3 L = normalize(_Data.ViewLightRevDir.xyz);
	// _Data.LightRevDir ������� �����ϴ� �༮�̾�� ������ �����Ѵ�.
	
	// Ratio������ ����� ��
    float ResultLight = 0.0f;
	
	// ������(swizzling) ���� Hlsl������ ��밡��
	// .xz
    ResultLight = saturate(dot(N.xyz, L.xyz));
	
	// ���� ����
    return ResultLight * 0.5f;

}

