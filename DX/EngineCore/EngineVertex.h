#pragma once
#include <EngineBase/EngineMath.h>
#include "EngineInputLayOutInfo.h"

// ����ȭ�� ���ؼ��� �پ��� ���ؽ��� ����°� ����.
// 
struct FEngineVertex
{
	// ��� ���ؽ��� �ڽ��� ���̾ƿ� ������ ������ �־�� �Ѵ�.
	friend class EngineVertexInit;
	static UEngineInputLayOutInfo Info;

	ENGINEAPI static UEngineInputLayOutInfo& GetInfo();

	float4 POSITION;
	float4 TEXCOORD; // UV���̶�� �Ҹ��� ����� �ؽ�ó�� ���εǴ� ������ �������ݴϴ�.
	float4 COLOR;
	float4 NORMAL; // ���� ���� ���Ͱ� �ʿ��ϴ�.
	float4 BINORMAL; // ���� ������ ���� �����Ͱ� ź��Ʈ ������ ����� ���Ѱ�.
	float4 TANGENT; // ���� ������ ���� �����Ͱ� ź��Ʈ ������ ����� ���Ѱ�.
	//float4 WEIGHT; // �ִϸ��̼� ����ġ
	//int BLENDINDICES[4]; // �ִϸ��̼� �ε���
	// ���� ������ ���� �������� �⺻�̱⵵ �ϰ�.
	// �Ⱦ��°� ���� �ȵȴ�.
};


