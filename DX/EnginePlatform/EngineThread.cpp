#include "PreCompile.h"
#include "EngineThread.h"
#include <EngineBase/EngineDebug.h>

UEngineThread::UEngineThread()
{
}

UEngineThread::~UEngineThread()
{
}

void UEngineThread::ThreadBaseFunction()
{
	// 쓰레드로 실행된 함수 내에서만 이름을 바꿀수가 있습니다.
}

bool UEngineThread::Start(std::string _Name, std::function<void()> _Function)
{
	// 아직 ThreadInst 지금 돌고 있는 쓰레드라거 안된다.
	if (true == ThreadInst.joinable())
	{
		return false;
	}

	if (nullptr == _Function)
	{
		MSGASSERT("함수를 세팅하지 않은 쓰레드는 start 할수 없습니다.");
		return false;
	}

	Name = _Name;
	ThreadFunction = _Function;
	ThreadInst = std::thread(ThreadBaseFunction);
	return true;
}

void UEngineThread::Join()
{

}
