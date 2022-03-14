#pragma once

class CAnimator;
class CD2DImage;

struct tAniFrm
{
	fPoint fptLT;
	fPoint fptSlice;
	fPoint fptOffset;
	float fDuration;
};

class CAnimation
{
	friend class CAnimator;

private:
	wstring			m_strName;		// �ִϸ��̼� �̸�
	CAnimator*		m_pAnimator;	// �ִϸ�����
	CD2DImage*		m_pImg;			// �ִϸ��̼� �̹���
	vector<tAniFrm> m_vecFrm;		// ��� �������� �ڸ��� ���� �� �����ð�
	int				m_iCurFrm;		// ���� �������� index
	float			m_fAccTime;		// ���� �����ӱ��� �����ð�

	bool			m_bReverse;

public:
	CAnimation();
	~CAnimation();

	void SetName(const wstring& strName);
	const wstring& GetName();

	void SetFrame(int frmIndex);
	tAniFrm& GetFrame(int frmIndex);

	void update();
	void render();	

	void Create(CD2DImage* tex, fPoint lt, fPoint slice, fPoint step, float duration, UINT frmCount);	// �ִϸ��̼� ����
};

