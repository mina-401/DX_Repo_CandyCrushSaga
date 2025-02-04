// 빛을 계산하기 위한 상수버퍼용 구조체
struct FLightData
{
    float4 LightPos; // 빛의 위치
    float4 LightDir; // 빛의 Forward
    float4 LightRevDir; // 빛의 반대방향이 < L!!!!! <= 
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

// 헤더에서는 전역함수도 만들수 있다.
// 참고로 레퍼런스나 포인터같은 개념은 Hlsl문법에서는 존재하지 않는다.

// N내적 L

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
	// _Data.LightRevDir 뷰공간에 존재하는 녀석이어야 공식이 성립한다.
	
	// Ratio비율에 가까운 값
    float ResultLight = 0.0f;
	
	// 스위즐링(swizzling) 문법 Hlsl에서만 사용가능
	// .xz
    ResultLight = saturate(dot(N.xyz, L.xyz));
	
	// 빛의 강도
    return ResultLight * 0.5f;

}

