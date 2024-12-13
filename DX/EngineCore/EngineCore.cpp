#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>

UEngineCore::UEngineCore()
{
}

UEngineCore::~UEngineCore()
{
}

void UEngineCore::EngineStart(HINSTANCE _Instance)
{
	UEngineDebug::LeakCheck();
	//게임 엔진 시작.
	//윈도우창 엔진이 띄움
	UEngineWindow::EngineWindowInit(_Instance);
	//window 띄운다. - engine window

	UEngineWindow MainWindow;

	MainWindow.Open("MainWindow");
	UEngineWindow::WindowMessageLoop(
		[]()
		{
			// 시작할때 하고 싶은것
			// 1. 윈도우창 크기 바꾸고 싶다.
		},
		[]()
		{
			// 엔진이 돌아갈때 하고 싶은것
		},
		[]()
		{
			// 엔진이 끝났을때 하고 싶은것.
		});



	/*UEngineDebug::OutPutString("sadasdf");*/
}

