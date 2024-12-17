#pragma once
#include <Windows.h>
#include <assert.h>


#define MSGASSERT(VALUE) std::string ErrorText = VALUE; MessageBoxA(nullptr, ErrorText.c_str(), "ġ���� ����", MB_OK); assert(false);

namespace UEngineDebug
{

	ENGINEAPI void LeakCheck();
	// �и��ؾ� �ϰڳ׿�
	ENGINEAPI void OutPutString(const std::string& Text);

	ENGINEAPI void StartConsole();

	ENGINEAPI void EndConsole();
}
