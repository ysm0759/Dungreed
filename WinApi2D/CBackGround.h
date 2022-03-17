#pragma once
#include "CGameObject.h"


class CBackGround : public CGameObject
{

private:
	CD2DImage* m_pImg;
	float m_fAutoSpeed;			// �������̴� �ӵ�
	float m_fDependOnSpeed;     // �÷��̾ ���� �����̴� ��� �ӵ�
	float m_fScale;				// ���������� ����									default = 4
	float m_fRepeatGap;			// ����� ���� �ݺ��ɶ� �ݺ��� �Ÿ�					default = 0;
	float m_fAlpha;				// ����� ����										default = 1;
	bool m_isFix;			    // true = ���� ,  false = �ƹ��ൿ ���ص������̴� ���  default = true ����
	bool m_isDirLeft;		    // true = ���� ,  false = ������					   default = true ����
	bool m_isDependOnPlayer;    // �÷��̾���ġ������ ���� ������					   default = flase ����
	bool m_isRepeat;			// �ݺ��Ǵ� �������
	
public:
	CBackGround();
	~CBackGround();

	void SetBackScale(float scale);

	void SetFix();
	void SetAuto(float autoSpeed);

	void SetDependOnPlayer(float dependOnSpeed);
	void SetIndependentOnPlayer();

	void SetLeft();
	void SetRight();
	void SetRepeat(float repeatGap = 0);
	void SetAlpha(float Alpha = 1.f);

	virtual CBackGround* Clone();
	virtual void update();
	virtual void render();



	void Load(wstring strKey, wstring strPath);
};


