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
	// ������� ����� �Լ� �������� �̸��� �ٲܼ��� �ֽ��ϴ�.
}

bool UEngineThread::Start(std::string _Name, std::function<void()> _Function)
{
	// ���� ThreadInst ���� ���� �ִ� �������� �ȵȴ�.
	if (true == ThreadInst.joinable())
	{
		return false;
	}

	if (nullptr == _Function)
	{
		MSGASSERT("�Լ��� �������� ���� ������� start �Ҽ� �����ϴ�.");
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
