#include "framework.h"
#include "CTimeManager.h"

CTimeManager::CTimeManager()
{
	m_uiFPS = 1;
	m_dDT = 1;
	m_llPrevCount = {};
	m_llCurCount = {};
	m_llFrequency = {};
}

CTimeManager::~CTimeManager()
{

}

void CTimeManager::update()
{
	static unsigned int updateCount = 0;
	static double updateOneSecond = 0;

	QueryPerformanceCounter(&m_llCurCount);
	// ���� �������� ī���ð�, ���� ������ ī���� ���� ���̸� ���Ѵ�.
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / m_llFrequency.QuadPart;
	// ���� �������� ���� ������ ī���� ������ �ִ´�.
	m_llPrevCount = m_llCurCount;

	++updateCount;
	updateOneSecond += m_dDT;
	if (updateOneSecond >= 1.0)
	{
		m_uiFPS = updateCount;

		updateOneSecond = 0;
		updateCount = 0;
	}
}

void CTimeManager::init()
{
	QueryPerformanceCounter(&m_llPrevCount);
	QueryPerformanceFrequency(&m_llFrequency);
}

unsigned int CTimeManager::GetFPS()
{
	return m_uiFPS;
}

float CTimeManager::GetfDT()
{
	return (float)m_dDT;
}

double CTimeManager::GetDT()
{
	return m_dDT;
}
