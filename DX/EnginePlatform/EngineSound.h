#pragma once
#include <map>

#include <EnginePlatform/ThirdParty/FMOD/inc/fmod.hpp>

#include "math.h"

// 사운드 플레이어
// 재생하는 사운드에 대한 볼륨및 
// 시간에 의해서 해야하는건 못해.
class USoundPlayer 
{
public:
	friend class UEngineSound;

	ENGINEAPI USoundPlayer();
	ENGINEAPI ~USoundPlayer();

	ENGINEAPI void On();

	ENGINEAPI void Off();
	ENGINEAPI void Stop();
	ENGINEAPI bool IsPlaying();
	ENGINEAPI void SetVolume(float _Volume);
	ENGINEAPI void OnOffSwtich();
	ENGINEAPI void SetPosition(unsigned int _Value);
	ENGINEAPI void Loop(int Count = -1);
	ENGINEAPI void ReStart();
	ENGINEAPI unsigned int LengthMs();

private:
	// 채널이 곧 사운드 재생방식에 대한 권한을 가집니다.
	FMOD::Channel* Control = nullptr;
	FMOD::Sound* SoundHandle = nullptr;;
};

// 설명 : 관리 선생님의 본스타일로 짜겠습니다.
class UEngineSound 
{
public:
	// constrcuter destructer
	ENGINEAPI UEngineSound();
	ENGINEAPI ~UEngineSound();

	// delete Function
	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	// 동시재생 사운드기능을 제대로 이용하려면
	// FMOD도 system업데이트 해줘야 합니다.
	// 우리가 실제 돌려주는것과 같이.

	ENGINEAPI static void Load(std::string_view _Path);
	ENGINEAPI static void Load(std::string_view _Name, std::string_view _Path);
	ENGINEAPI static USoundPlayer Play(std::string_view _Name);
	ENGINEAPI static UEngineSound* Find(std::string_view _Name);
	ENGINEAPI static void Release();

	ENGINEAPI static void Update();

	ENGINEAPI static void AllSoundStop();
	ENGINEAPI static void AllSoundOff();
	ENGINEAPI static void AllSoundOn();
	ENGINEAPI static void Init();

protected:

private:
	ENGINEAPI static std::map<std::string, UEngineSound*> Sounds;
	ENGINEAPI static std::list<USoundPlayer> Players;

	FMOD::Sound* SoundHandle;

	ENGINEAPI bool ResLoad(std::string_view _Path);
};

