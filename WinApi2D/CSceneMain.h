#pragma once
#include "CScene.h"

class CSceneMain : public CScene
{
public:
	CSceneMain();
	virtual ~CSceneMain();

	virtual void update();

	virtual void Enter();
	virtual void Exit();

};
