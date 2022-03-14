#pragma once
#include "FMOD/inc/fmod.hpp"
#include "CResource.h"
#pragma comment(lib,"FMOD/lib/fmod_vc.lib")

using namespace FMOD;

class CSound : public CResource
{
private:

	Sound*		m_pSound;
	Channel*	m_pChannel;

public:
	CSound();
	~CSound();

	void Play();
	void Stop();
	void Pause();
	void Resume();

	bool IsPlaying();
	bool IsPaused();

	void SetLoop(bool loop);

	void Load(const wstring& strRelativePath, bool bgm);
};

