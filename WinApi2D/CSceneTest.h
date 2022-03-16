#pragma once
#include "CScene.h"

class CSceneTest : public CScene
{
public:
	CSceneTest();
	virtual ~CSceneTest();

	virtual void update();

	virtual void Enter();
	virtual void Exit();
};

