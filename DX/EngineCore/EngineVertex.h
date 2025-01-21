#pragma once
#include <EngineBase/EngineMath.h>
#include "EngineInputLayOutInfo.h"

// 최적화를 위해서는 다양한 버텍스를 만드는게 좋다.
// 
struct FEngineVertex
{
	// 모든 버텍스는 자신의 레이아웃 정보를 가지고 있어야 한다.
	friend class EngineVertexInit;
	static UEngineInputLayOutInfo Info;

	ENGINEAPI static UEngineInputLayOutInfo& GetInfo();

	float4 POSITION;
	float4 TEXCOORD; // UV값이라고 불리는 존재로 텍스처가 매핑되는 비율을 지정해줍니다.
	float4 COLOR;
	float4 NORMAL; // 면의 법선 백터가 필요하다.
	float4 BINORMAL; // 범프 매핑을 위한 데이터가 탄젠트 공간을 만들기 위한것.
	float4 TANGENT; // 범프 매핑을 위한 데이터가 탄젠트 공간을 만들기 위한것.
	//float4 WEIGHT; // 애니메이션 가중치
	//int BLENDINDICES[4]; // 애니메이션 인덱스
	// 범프 매핑은 현대 랜더링의 기본이기도 하고.
	// 안쓰는게 말이 안된다.
};


