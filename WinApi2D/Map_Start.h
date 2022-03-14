#pragma once
#include "CGameObject.h"

class CD2DImage;

class Map_Start : public CGameObject
{
public:
	CD2DImage* pimg;

	Map_Start();
	~Map_Start();

	virtual Map_Start* Clone();
	virtual void update();
	virtual void render();
};

