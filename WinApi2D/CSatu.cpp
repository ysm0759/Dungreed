#include "framework.h"
#include "CStatu.h"
#include "CGameObject.h"

// �߷�
#define JUMPSPEED  1000		    // ���� �پ������ �ӵ�
#define GRAVITY_MAX 2000		// �ƽ� �߷°�
#define GRAVITY_VALUE 2000		// �߷� ���ӵ�

CStatu::CStatu()
{
	m_pOwner = nullptr;
	m_iObjectStatu = 0;
	m_fGravity = 0;
	m_fLook = {};
}

CStatu::CStatu (const CStatu& other)
{
	m_pOwner = nullptr;
	m_iObjectStatu = other.m_iObjectStatu;
	m_fGravity = 0;
	m_fLook = other.m_fLook;
}

CStatu::~CStatu()
{

}

void CStatu::SetForceDir(fVec2 forceDir)
{
	this->m_fDashDir = forceDir;
}

void CStatu::SetForce(float Force)
{
	this->m_fForce = Force;
}

void CStatu::SetLook(fVec2 look)
{
	this->m_fLook = look;
}

void CStatu::update()
{
	Look();
	Jump();
	Gravity();
	Fouce(); 
}

void CStatu::Jump()
{
	if (IsStatu((UINT)GROUP_OBJECT_STATU::JUMP))
	{
		fPoint objectPos = m_pOwner->GetPos();
		objectPos.y -= JUMPSPEED * fDT;
		m_pOwner->SetPos(objectPos);
	}
}

void CStatu::Gravity()
{
	if (IsStatu((UINT)GROUP_OBJECT_STATU::GROUND)) //	GROUND�����̸� �߷��� ���� ����
	{
		m_fGravity = 0;
	}
	else // �װ� �ƴϸ� �߷��� �ް� ��
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

void CStatu::Fouce()
{
	if (IsStatu((UINT)GROUP_OBJECT_STATU::FORCE))
	{
		 // �뽬 ����Ҷ� ī�޶� , realpos ����
		fPoint objectRealPos = m_pOwner->GetPos();
		objectRealPos.x += m_fForce * m_fDashDir.normalize().x * fDT;
		objectRealPos.y += m_fForce * m_fDashDir.normalize().y * fDT;
		m_pOwner->SetPos(objectRealPos);
	}

}

void CStatu::Look()
{
	if (m_fLook.x < 0)
		SetStatu((UINT)GROUP_OBJECT_STATU::LOOK);
	else
		RemoveStatu((UINT)GROUP_OBJECT_STATU::LOOK);
}


CStatu* CStatu::GetStatu()
{
	return this;
}

void CStatu::SetStatu(UINT bit)	   //�ش� ��Ʈ�� 1�� ä��
{
	m_iObjectStatu |= (1 << bit);
}

bool CStatu::IsStatu(UINT bit)	   //�ش� ��Ʈ�� 1�̸� true �ƴϸ� false
{
	return m_iObjectStatu & (1 << bit);
}

void CStatu::RemoveStatu(UINT bit) //�ش� ��Ʈ ����
{
	m_iObjectStatu &= ~(1 << bit);
}

