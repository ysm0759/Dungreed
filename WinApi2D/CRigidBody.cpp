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
	m_fDashDir = {};
}

CRigidBody::CRigidBody(const CRigidBody& other)
{
	m_pOwner = nullptr;
	m_iObjectStatu = other.m_iObjectStatu;
	m_fGravity = 0;
	m_fDashDir = other.m_fDashDir;
}

CRigidBody::~CRigidBody()
{

}

void CRigidBody::SetDashDir(fVec2 dashDir)
{
	this->m_fDashDir = dashDir;
}

void CRigidBody::SetVelocity(float velocity)
{
	this->m_fVelocity = velocity;
}

void CRigidBody::update()
{
	Jump();
	Gravity();
	Dash(); 
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
	if (GetStatu((UINT)GROUP_OBJECT_STATU::GROUND)) //	GROUND�����̸� �߷��� ���� ����
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

void CRigidBody::Dash()
{
	if (GetStatu((UINT)GROUP_OBJECT_STATU::DASH))
	{
		//fPoint mouseRenderPos = MousePos();// CCameraManager::getInst()->GetRenderPos(MousePos());

		//fPoint objectRenderPos = CCameraManager::getInst()->GetRenderPos(m_pOwner->GetPos());
		fPoint objectRealPos = m_pOwner->GetPos();
		objectRealPos.x += m_fVelocity * m_fDashDir.normalize().x * fDT;
		objectRealPos.y += m_fVelocity * m_fDashDir.normalize().y * fDT;
		m_pOwner->SetPos(objectRealPos);
	}

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

