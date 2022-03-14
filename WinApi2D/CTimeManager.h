#pragma once
class CTimeManager
{
	SINGLETON(CTimeManager);

private:

	// LARGE_INTEGER : long long ������ ����ü HighPart + LowPart = QuadPart
	LARGE_INTEGER m_llCurCount;		// ���� ī��Ʈ
	LARGE_INTEGER m_llPrevCount;	// ���� ī��Ʈ
	LARGE_INTEGER m_llFrequency;	// �ʴ� ī��Ʈ Ƚ��

	unsigned int	m_uiFPS;	// FPS		: 1�ʴ� �׷��� ȭ�� ��
	double			m_dDT;		// Delta Time	: 1�����Ӵ� �ҿ�� �ð�

public:
	void update();
	void init();

	unsigned int GetFPS();
	float GetfDT();
	double GetDT();
};

