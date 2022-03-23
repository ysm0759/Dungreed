#include "framework.h"
#include "CFairy.h"
#include "CAnimator.h"
#include "CStatu.h"
#include "CCollider.h"

CFairy::CFairy(GROUP_FAIRY type)
{
	this->m_eFairyType = type;

	StatuSet(GROUP_OBJECT_STATU::GROUND);
	switch (m_eFairyType)
	{
	case GROUP_FAIRY::FAIRY_SMALL:
		GetCollider()->SetScale(fPoint(10, 10));
		GetCollider()->SetOffsetPos(fPoint(0, 3));
		break;

	case GROUP_FAIRY::FAIRY_MIDDLE:
		GetCollider()->SetScale(fPoint(20, 20));
		GetCollider()->SetOffsetPos(fPoint(0, 3));
		break;

	case GROUP_FAIRY::FAIRY_BIG:
		GetCollider()->SetScale(fPoint(30, 30));
		GetCollider()->SetOffsetPos(fPoint(0, 3));
		break;
	}

}

CFairy::~CFairy()
{

};

//
//void CFairy::DropRender()
//{
//	switch (m_eFairyType)
//	{
//	case GROUP_FAIRY::FAIRY_SMALL:
//		GetAnimator()->Play(L"FairyS", fPoint(20, 20), StatuGet(GROUP_OBJECT_STATU::LOOK));
//		break;
//	case GROUP_FAIRY::FAIRY_MIDDLE:
//		GetAnimator()->Play(L"FairyM", fPoint(5, 5), StatuGet(GROUP_OBJECT_STATU::LOOK));
//		break;
//	case GROUP_FAIRY::FAIRY_BIG:
//		GetAnimator()->Play(L"FairyL", fPoint(20, 20), StatuGet(GROUP_OBJECT_STATU::LOOK));
//		break;
//	}
//	component_render();
//}
//
//void CFairy::DropUpdate()
//{
//
//	GetAnimator()->update();
//}
