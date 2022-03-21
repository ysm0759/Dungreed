#include "framework.h"
#include "CCoin.h"
#include "CAnimator.h"
#include "CStatu.h"
#include "CCollider.h"
CCoin::CCoin()
{

};

CCoin::CCoin(GROUP_COIN type)
{
	this->m_eCoinType = type;
	switch (m_eCoinType)
	{
	case GROUP_COIN::GOLD_SMALL:
		SetScale(fPoint(15, 15));
		CreateCollider();
		GetCollider()->SetScale(GetScale());
		break;
	case GROUP_COIN::GOLD_BIG:
		SetScale(fPoint(2000, 2000));
		break;
	}




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
		GetAnimator()->Play(L"GoldBig", fPoint(50, 50), StatuGet(GROUP_OBJECT_STATU::LOOK));
		break;
	}

	component_render();
}

void CCoin::DropUpdate()
{
}
