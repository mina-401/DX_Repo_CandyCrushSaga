
#include <EngineBase/EngineMath.h>
#include <EngineCore/EngineCore.h>

#pragma comment(lib, "EngineBase.lib")
#pragma comment(lib, "EnginePlatform.lib")
#pragma comment(lib, "EngineCore.lib")
int APIENTRY wWinMain(_In_ HINSTANCE _hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 동적 연결을 위한 "EngineContents" dll이름 넣기
	UEngineCore::EngineStart(_hInstance, "CandyCrushSaga.dll");
	return 0;
}  