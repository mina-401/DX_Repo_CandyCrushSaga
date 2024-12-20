#include "PreCompile.h"
#include "ContentsCore.h"
#include <EngineCore/EngineCore.h>
#include "TitleGameMode.h"
#include <EngineCore/Pawn.h>


CreateContentsCoreDefine(UContentsCore);
UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}

void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };
	UEngineCore::CreateLevel<ATitleGameMode, APawn>("Titlelevel");
	UEngineCore::OpenLevel("Titlelevel");
	// ������ ũ�� ����
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}