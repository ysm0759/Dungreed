#pragma once
#include "CGameObject.h"

class CBackGround : public CGameObject
{

private:
	CD2DImage* m_pImg;
	float m_fSpeed; // �������̴� �ӵ�
	bool m_isFix;	  // ����
	bool m_isAuto;	  // �ڵ����� �����̴� ������ �ƴ���
	bool m_isDirLeft; // ���ʹ������� �⺻�� ����
public:
	CBackGround();
	CBackGround( float fSpeed , bool isAuto ,bool isDirLeft = true); // ���ǵ带 �Է��ϸ� �̵��ϴ¸� 
	~CBackGround();

	virtual CBackGround* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

