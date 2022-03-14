#pragma once
class CTimeManager
{
	SINGLETON(CTimeManager);

private:

	// LARGE_INTEGER : long long 변수의 공용체 HighPart + LowPart = QuadPart
	LARGE_INTEGER m_llCurCount;		// 현재 카운트
	LARGE_INTEGER m_llPrevCount;	// 이전 카운트
	LARGE_INTEGER m_llFrequency;	// 초당 카운트 횟수

	unsigned int	m_uiFPS;	// FPS		: 1초당 그려진 화면 수
	double			m_dDT;		// Delta Time	: 1프레임당 소요된 시간

public:
	void update();
	void init();

	unsigned int GetFPS();
	float GetfDT();
	double GetDT();
};

