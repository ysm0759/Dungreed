#include "framework.h"
#include "CSoundManager.h"
#include "CSound.h"

CSoundManager::CSoundManager()
{
	m_pSystem = nullptr;
}

CSoundManager::~CSoundManager()
{
	m_pSystem->release();
	m_pSystem->close();
}

System* CSoundManager::GetSystem()
{
	return m_pSystem;
}

void CSoundManager::init()
{
	// 사운드 시스템 생성
	System_Create(&m_pSystem);
	assert(m_pSystem);
	m_pSystem->init(32, FMOD_INIT_NORMAL, nullptr);
}

void CSoundManager::update()
{
	m_pSystem->update();		// 반드시 매 프레임마다 업데이트 되어야 함. fmod에서 하래
}

void CSoundManager::AddSound(wstring keyName, wstring filePath, bool bgm, bool loop)
{
	CSound* pSound;
	if (bgm)
	{
		pSound = CResourceManager::getInst()->LoadBGM(keyName, filePath);
	}
	else
	{
		pSound = CResourceManager::getInst()->LoadSound(keyName, filePath);
	}
	m_mapSound.insert(make_pair(keyName, pSound));
}

void CSoundManager::Play(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		iter->second->Play();
}

void CSoundManager::Stop(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		iter->second->Stop();
}

void CSoundManager::Pause(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		iter->second->Pause();
}

void CSoundManager::Resume(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		iter->second->Resume();
}

bool CSoundManager::IsPlaySound(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		return iter->second->IsPlaying();
	return false;
}

bool CSoundManager::IsPauseSound(wstring keyName)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(keyName);
	if (iter != m_mapSound.end())
		return iter->second->IsPaused();
	return false;
}
