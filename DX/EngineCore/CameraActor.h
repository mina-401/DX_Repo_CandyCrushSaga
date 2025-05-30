#pragma once
#include "Actor.h"
#include "EngineEnums.h"

// 설명 :
class ACameraActor : public AActor
{
	friend class ULevel;

public:
	// constrcuter destructer
	ACameraActor();
	~ACameraActor();

	// delete Function
	ACameraActor(const ACameraActor& _Other) = delete;
	ACameraActor(ACameraActor&& _Other) noexcept = delete;
	ACameraActor& operator=(const ACameraActor& _Other) = delete;
	ACameraActor& operator=(ACameraActor&& _Other) noexcept = delete;

	ENGINEAPI std::shared_ptr<class UEngineCamera> GetCameraComponent()
	{
		return CameraComponent;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime);

	ENGINEAPI FVector ScreenMousePosToWorldPosWithOutPos(float _PosZ);

	ENGINEAPI FVector ScreenPosToWorldPosWithOutPos(FVector _Pos, float _PosZ);

	ENGINEAPI FVector ScreenMousePosToWorldPos();

	// 항상 중심을 0,0 으로 보는 마우스 포스 얻는법
	ENGINEAPI FVector ScreenMousePosToWorldPosWithOutPos();

	ENGINEAPI FVector ScreenPosToWorldPos(FVector _Pos);

	ENGINEAPI FVector WorldPosToScreenPos(FVector _Pos);

	ENGINEAPI inline bool IsFreeCamera()
	{
		return IsFreeCameraValue;
	}

	ENGINEAPI void FreeCameraOn();

	ENGINEAPI void FreeCameraOff();

	ENGINEAPI void FreeCameraSwitch();

	ENGINEAPI void EngineFreeCameraUpdate(float _DeltaTime);


	// #ifdef _DEBUG
	void SetFreeCameraSpeed(float _Speed)
	{
		FreeSpeed = _Speed;
	}

	void SetFreeCameraRotSpeed(float _Speed)
	{
		RotSpeed = _Speed;
	}
	// #endif


protected:

private:
	std::shared_ptr<class UEngineCamera> CameraComponent = nullptr;
	bool IsFreeCameraValue = false;
	ENGINEAPI void FreeCameraCheck();

	FTransform PrevTrans;
	EProjectionType PrevProjectionType = EProjectionType::Orthographic;
	float FreeSpeed = 500.0f;

	FVector ScreenPos;
	FVector PrevScreenPos;
	float RotSpeed = 360.0f;
};

