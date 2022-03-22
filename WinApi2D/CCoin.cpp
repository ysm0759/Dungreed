#include "framework.h"
#include "CCoin.h"
#include "CAnimator.h"
#include "CStatu.h"
#include "CCollider.h"

CCoin::CCoin(GROUP_COIN type)
{
	this->m_eCoinType = type;
	int randDir = rand() % 2;

	if (randDir == 0)
		GetStatu()->SetForceDir(fPoint(-rand(), -rand()));
	else
		GetStatu()->SetForceDir(fPoint(rand(), -rand()));

	GetStatu()->SetForce(rand() %100 + 50 * 10);
	SetDrop();
	switch (m_eCoinType)
	{
	case GROUP_COIN::GOLD_SMALL:
	{
	}
		GetCollider()->SetScale(fPoint(10, 10));
		GetCollider()->SetOffsetPos(fPoint(0, 3));
		break;
	case GROUP_COIN::GOLD_BIG:
		GetCollider()->SetScale(fPoint(30,15));
		GetCollider()->SetOffsetPos(fPoint(0, 3));
		break;
	}

	StatuSet(GROUP_OBJECT_STATU::FORCE);
	StatuRemove(GROUP_OBJECT_STATU::GROUND);
}
CCoin::~CCoin()
{

};


void CCoin::DropRender()
{
	switch (m_eCoinType)
	{
	case GROUP_COIN::GOLD_SMALL:
		GetAnimator()->Play(L"GoldSmall", fPoint(20, 20), StatuGet(GROUP_OBJECT_STATU::LOOK));
		break;
	case GROUP_COIN::GOLD_BIG:
		GetAnimator()->Play(L"GoldBig", fPoint(20, 20), StatuGet(GROUP_OBJECT_STATU::LOOK));
		break;
	} 
	component_render();
}

void CCoin::DropUpdate()
{

	GetAnimator()->update();
}
