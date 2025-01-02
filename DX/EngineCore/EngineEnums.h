#pragma once

// 1바이트 정수 로 쉐이더를 만들고 싶으면 아래와 같이 하면 됩니다.
enum class EShaderType : __int8
{
	VS, // 버텍스
	HS, // 
	DS,
	GS,
	PS,
	CS,
};
