#pragma once
#include "CGameObject.h"


class CBackGround : public CGameObject
{

private:
	CD2DImage* m_pImg;
	float m_fAutoSpeed;			// �������̴� �ӵ�
	float m_fDependOnSpeed;     // �÷��̾ ���� �����̴� ��� �ӵ�

	bool m_isFix;			  // true = ���� ,  false = �ƹ��ൿ ���ص������̴� ���  default = true ����
	bool m_isDirLeft;		  // true = ���� ,  false = ������					   default = true ����
	bool m_isDependOnPlayer;   // �÷��̾���ġ������ ���� ������					   default = flase ����

public:
	CBackGround();
	~CBackGround();


	void SetFix();
	void SetAuto(float autoSpeed);

	void SetDependOnPlayer(float dependOnSpeed);
	void SetIndependentOnPlayer();

	void SetLeft();
	void SetRight();

	virtual CBackGround* Clone();
	virtual void update();
	virtual void render();



	void Load(wstring strKey, wstring strPath);
};


