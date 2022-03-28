#pragma once
#include "CGameObject.h"


enum class GROUP_CURSOR
{
	DEFAULT,
	AIM,
};

class CCursor : public CGameObject
{

	GROUP_CURSOR m_eType;
	CD2DImage* m_pImg;


public:
	CCursor();
	~CCursor();
	virtual CCursor* Clone();
	virtual void update();
	virtual void render();
	void SetCursor(GROUP_CURSOR type);

};

