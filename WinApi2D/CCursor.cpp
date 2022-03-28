#include "framework.h"
#include "CCursor.h"
#include "CAnimator.h"

CCursor::CCursor()
{
	m_eType = GROUP_CURSOR::DEFAULT;



	CreateAnimator();
	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"DEFAULT_CURSOR", L"texture\\UI\\DEFAULT_CURSOR.png");
	GetAnimator()->CreateAnimation(L"DEFAULT_CURSOR", m_pImg, fPoint(0, 0), fPoint(19.f, 19.f), fPoint(19.f, 0), 0.1f, 1);


	m_pImg = CResourceManager::getInst()->LoadD2DImage(L"AIM_CURSOR", L"texture\\UI\\DEFAULT_CURSOR.png");
	GetAnimator()->CreateAnimation(L"PlayerRun", m_pImg, fPoint(0, 0), fPoint(21.f, 21.f), fPoint(21.f, 0), 0.1f, 1);

}
CCursor::~CCursor()
{

}

CCursor* CCursor::Clone()
{
	assert(nullptr);

	return nullptr;
}


void CCursor::update()
{
	
	SetPos(MousePos());

	GetAnimator()->update();
}


void CCursor::render()
{
	fPoint pos = GetPos();
	fPoint scale = GetScale();
	pos = CCameraManager::getInst()->GetRenderPos(pos);

	if (GROUP_CURSOR::AIM == m_eType)
	{
		GetAnimator()->Play(L"AIM_CURSOR");
	}
	else
	{
		GetAnimator()->Play(L"DEFAULT_CURSOR");
	}

	component_render();

}

void CCursor::SetCursor(GROUP_CURSOR type)
{
	this->m_eType = type;
}
