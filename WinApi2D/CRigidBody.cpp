#include "framework.h"
#include "CRigidBody.h"
#include "CGameObject.h"

// �߷�
#define JUMPSPEED  1000		    // ���� �پ������ �ӵ�
#define GRAVITY_MAX 2000		// �ƽ� �߷°�
#define GRAVITY_VALUE 2000		// �߷� ���ӵ�

CRigidBody::CRigidBody()
{
	m_pOwner = nullptr;
	m_iObjectStatu = 0;
	m_fGravity = 0;

}

CRigidBody::CRigidBody(const CRigidBody& other)
{
	m_pOwner = nullptr;
	m_iObjectStatu = other.m_iObjectStatu;
	m_fGravity = 0;
}

CRigidBody::~CRigidBody()
{

}

void CRigidBody::update()
{
	Jump();
	Gravity();
}

void CRigidBody::Jump()
{

	if (GetStatu((UINT)GROUP_OBJECT_STATU::JUMP))
	{
		fPoint objectPos = m_pOwner->GetPos();
		objectPos.y -= JUMPSPEED * fDT;
		m_pOwner->SetPos(objectPos);
	}
}

void CRigidBody::Gravity()
{
	if (GetStatu((UINT)GROUP_OBJECT_STATU::GROUND)) //�ٴ��� ���� �پ� ������ 
	{
		m_fGravity = 0;
	}
	else // �װ� �ƴϸ�
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

void CRigidBody::Dash()
{
	
	
}

void CRigidBody::SetStatu(UINT bit)	   //�ش� ��Ʈ�� 1�� ä��
{
	m_iObjectStatu |= (1 << bit);
}

bool CRigidBody::GetStatu(UINT bit)	   //�ش� ��Ʈ�� 1�̸� true �ƴϸ� false
{
	return m_iObjectStatu & (1 << bit);
}

void CRigidBody::RemoveStatu(UINT bit) //�ش� ��Ʈ ����
{
	m_iObjectStatu &= ~(1 << bit);
}

