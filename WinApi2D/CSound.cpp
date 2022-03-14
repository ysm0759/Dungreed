#include "framework.h"
#include "CSound.h"

CSound::CSound()
{
	m_pSound = nullptr;
	m_pChannel = nullptr;
}

CSound::~CSound()
{
	Stop();
	if (nullptr != m_pSound)
	{
		m_pSound->release();
	}
}

void CSound::Load(const wstring& strFilePath, bool bgm)
{
	char str[255];
	wcstombs_s(nullptr, str, strFilePath.c_str(), 255);

	if (bgm)
	{
		CSoundManager::getInst()->GetSystem()->createStream(str, FMOD_LOOP_NORMAL, 0, &m_pSound);
	}
	else
	{
		CSoundManager::getInst()->GetSystem()->createSound(str, FMOD_LOOP_OFF, 0, &m_pSound);
	}
}

void CSound::Play()
{
	CSoundManager::getInst()->GetSystem()->playSound(m_pSound, 0, false, &m_pChannel);
	assert(m_pChannel);
}

void CSound::Pause()
{
	
	assert(m_pChannel);
	m_pChannel->setPaused(true);
}

void CSound::Stop()
{
	assert(m_pChannel); 
	m_pChannel->stop();
}

void CSound::Resume()
{
	assert(m_pChannel); 
	m_pChannel->setPaused(true);
}

bool CSound::IsPlaying()
{
	bool playing = false;
	assert(m_pChannel); 
	m_pChannel->isPlaying(&playing);
	return playing;
}

bool CSound::IsPaused()
{
	bool paused = false;
	assert(m_pChannel); 
	m_pChannel->getPaused(&paused);
	return paused;
}

void CSound::SetLoop(bool loop)
{
	if (loop)
	{
		m_pSound->setMode(FMOD_LOOP_NORMAL);
	}
	else
	{
		m_pSound->setMode(FMOD_LOOP_OFF);
	}
}