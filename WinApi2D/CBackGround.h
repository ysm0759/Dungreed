#pragma once
#include "CGameObject.h"

class CBackGround : public CGameObject
{

private:
	CD2DImage* m_pImg;
	float m_fSpeed; // �������̴� �ӵ�
	bool m_isFix;
public:
	CBackGround();
	CBackGround( float fSpeed ); // ���ǵ带 �Է��ϸ� �̵��ϴ¸� 
	~CBackGround();

	virtual CBackGround* Clone();
	virtual void update();
	virtual void render();

	void Load(wstring strKey, wstring strPath);
};

