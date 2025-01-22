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

float4 CalDiffusLight(float4 _Normal, FLightData _Data)
{
	// ���� L
	float4 ResultLight = dot(_Normal, _Data.LightRevDir);
	return _Data.LightColor;

}