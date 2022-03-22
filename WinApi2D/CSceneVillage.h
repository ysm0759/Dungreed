#pragma once
#include "CScene.h"
class CSceneVillage : public CScene
{
public:
	CSceneVillage();
	virtual ~CSceneVillage();

	virtual void update();

	virtual void Enter();
	virtual void Exit();

	void CreateBackGround();

};

