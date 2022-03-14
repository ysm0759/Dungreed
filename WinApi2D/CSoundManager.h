#pragma once
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib,"FMOD/lib/fmod_vc.lib")

using namespace FMOD;

class CSoundManager
{
	SINGLETON(CSoundManager);

private:
	map<wstring, CSound*> m_mapSound;	// 사운드들을 관리하기 위한 자료구조

	System* m_pSystem;					// 사운드 시스템

public:
	System* GetSystem();

	void init();
	void update();

	void AddSound(wstring keyName, wstring filePath, bool bgm = false, bool loop = false);
	void Play(wstring keyName);
	void Stop(wstring keyName);
	void Pause(wstring keyName);
	void Resume(wstring keyName);

	bool IsPlaySound(wstring keyName);
	bool IsPauseSound(wstring keyName);
};

