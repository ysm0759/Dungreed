#include "framework.h"
#include "CStatu.h"
#include "CGameObject.h"

// 중력
#define JUMPSPEED  1000		    // 점프 뛰어오르는 속도
#define GRAVITY_MAX 2000		// 맥스 중력값
#define GRAVITY_VALUE 2000		// 중력 가속도

CStatu::CStatu()
{
	m_pOwner = nullptr;
	m_iObjectStatu = 0;
	m_fGravity = 0;
	m_fDashDir = {};
}

CStatu::CStatu (const CStatu& other)
{
	m_pOwner = nullptr;
	m_iObjectStatu = other.m_iObjectStatu;
	m_fGravity = 0;
	m_fDashDir = other.m_fDashDir;
}

CStatu::~CStatu()
{

}

void CStatu::SetDashDir(fVec2 dashDir)
{
	this->m_fDashDir = dashDir;
}

void CStatu::SetForce(float Force)
{
	this->m_fForce = Force;
}

void CStatu::update()
{
	Jump();
	Gravity();
	Dash(); 
}

void CStatu::Jump()
{
	if (GetStatu((UINT)GROUP_OBJECT_STATU::JUMP))
	{
		fPoint objectPos = m_pOwner->GetPos();
		objectPos.y -= JUMPSPEED * fDT;
		m_pOwner->SetPos(objectPos);
	}
}

void CStatu::Gravity()
{
	if (GetStatu((UINT)GROUP_OBJECT_STATU::GROUND)) //	GROUND상태이면 중력을 받지 않음
	{
		m_fGravity = 0;
	}
	else // 그게 아니면 중력을 받게 됨
	{
		fPoint objectPos = m_pOwner->GetPos();
		objectPos.y += m_fGravity * fDT;
		m_pOwner->SetPos(objectPos);

		if (m_fGravity <= GRAVITY_MAX)
		{
			m_fGravity += GRAVITY_VALUE * fDT;
		}
	}
}

void CStatu::Dash()
{
	if (GetStatu((UINT)GROUP_OBJECT_STATU::FORCE))
	{
		 // 대쉬 상용할때 카메라 , realpos 주의
		fPoint objectRealPos = m_pOwner->GetPos();
		objectRealPos.x += m_fForce * m_fDashDir.normalize().x * fDT;
		objectRealPos.y += m_fForce * m_fDashDir.normalize().y * fDT;
		m_pOwner->SetPos(objectRealPos);
	}

}

void CStatu::SetStatu(UINT bit)	   //해당 비트를 1로 채움
{
	m_iObjectStatu |= (1 << bit);
}

bool CStatu::GetStatu(UINT bit)	   //해당 비트가 1이면 true 아니면 false
{
	return m_iObjectStatu & (1 << bit);
}

void CStatu::RemoveStatu(UINT bit) //해당 비트 제거
{
	m_iObjectStatu &= ~(1 << bit);
}

