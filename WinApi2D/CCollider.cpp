#include "framework.h"
#include "CCollider.h"
#include "CGameObject.h"

UINT CCollider::s_iID = 0;

CCollider::CCollider()
{
	m_pOwner = nullptr;
	m_fptOffsetPos = {};
	m_fptFinalPos = {};
	m_fptScale = {};
	m_iColCount = 0;
	m_iID = s_iID++;
}

CCollider::CCollider(const CCollider& other)
{
	m_pOwner = nullptr;
	m_fptOffsetPos = other.m_fptOffsetPos;
	m_fptFinalPos = other.m_fptFinalPos;
	m_fptScale = other.m_fptScale;
	m_iColCount = other.m_iColCount;
	m_iID = s_iID++;
}

CCollider::~CCollider()
{
}

CGameObject* CCollider::GetObj()
{
	return m_pOwner;
}

fPoint CCollider::GetOffsetPos()
{
	return m_fptOffsetPos;
}

fPoint CCollider::GetFinalPos()
{
	return m_fptFinalPos;
}

fPoint CCollider::GetScale()
{
	return m_fptScale;
}

void CCollider::SetOffsetPos(fPoint offsetPos)
{
	m_fptOffsetPos = offsetPos;
}

void CCollider::SetFinalPos(fPoint finalPos)
{
	m_fptFinalPos = finalPos;
}

void CCollider::SetScale(fPoint scale)
{
	m_fptScale = scale;
}

UINT CCollider::GetID()
{
	return m_iID;
}

void CCollider::finalupdate()
{
	fPoint fptObjectPos = m_pOwner->GetPos();
	m_fptFinalPos = fptObjectPos + m_fptOffsetPos;
}

void CCollider::render()
{
	COLORREF rgb = RGB(0, 0, 0);
	if (m_iColCount)
		rgb = RGB(255, 0, 0);
	else
		rgb = RGB(0, 255, 0);

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(m_fptFinalPos);

	CRenderManager::getInst()->RenderRectangle(
		fptRenderPos.x - m_fptScale.x / 2.f,
		fptRenderPos.y - m_fptScale.y / 2.f,
		fptRenderPos.x + m_fptScale.x / 2.f,
		fptRenderPos.y + m_fptScale.y / 2.f,
		rgb);
}

void CCollider::OnCollision(CCollider* pOther)
{
	m_pOwner->OnCollision(pOther);
}

void CCollider::OnCollisionEnter(CCollider* pOther)
{
	m_pOwner->OnCollisionEnter(pOther);
	m_iColCount++;
}

void CCollider::OnCollisionExit(CCollider* pOther)
{
	m_pOwner->OnCollisionExit(pOther);
	m_iColCount--;
}
