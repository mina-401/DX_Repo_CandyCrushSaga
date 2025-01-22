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
	int Count;
	FLightData LightArr[256];
};

// 헤더에서는 전역함수도 만들수 있다.
// 참고로 레퍼런스나 포인터같은 개념은 Hlsl문법에서는 존재하지 않는다.

// N내적 L

float4 CalDiffusLight(float4 _Normal, FLightData _Data)
{
	// 내적 L
	float4 ResultLight = dot(_Normal, _Data.LightRevDir);
	return _Data.LightColor;

}