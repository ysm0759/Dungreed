#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CCollider.h"

CCollisionManager::CCollisionManager()
{
	m_arrCheck[0] = 0;
}

CCollisionManager::~CCollisionManager()
{

}

void CCollisionManager::CollisionGroupUpdate(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight)
{
	CScene* pCurScene = CSceneManager::getInst()->GetCurScene();

	const vector<CGameObject*>& vecLeft = pCurScene->GetGroupObject(objLeft);
	const vector<CGameObject*>& vecRight = pCurScene->GetGroupObject(objRight);

	for (int i = 0; i < vecLeft.size(); i++)
	{
		// �浹ü ������Ʈ�� ���� ��� ����
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (int j = 0; j < vecRight.size(); j++)
		{
			// �浹ü ������Ʈ�� ���� ��� ����
			if (nullptr == vecRight[j]->GetCollider())
				continue;

			// �ڱ� �ڽŰ��� �浹�� ����
			if (vecLeft[i] == vecRight[j])
				continue;

			// �� �浹ü�� ID�� �̿��ؼ�, ������ Ű ����
			COLLIDER_ID id;
			id.left_id = vecLeft[i]->GetCollider()->GetID();
			id.Right_id = vecRight[j]->GetCollider()->GetID();

			map<ULONGLONG, bool>::iterator iter = m_mapCollInfo.find(id.ID);

			// �浹 ������ ���� ���, �浹���� ���� ���¸� �־���
			if (m_mapCollInfo.end() == iter)
			{
				m_mapCollInfo.insert(make_pair(id.ID, false));
				iter = m_mapCollInfo.find(id.ID);
			}

			// �浹 ó��
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{
				// Prev O, Cur O
				if (iter->second)
				{
					// �浹ü �� �ϳ��� Dead ���¶�� �浹 ����
					if (vecLeft[i]->isDead() || vecRight[j]->isDead())
					{
						vecLeft[i]->GetCollider()->OnCollisionExit(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnCollisionExit(vecLeft[i]->GetCollider());
						iter->second = false;
					}
					else
					{
						vecLeft[i]->GetCollider()->OnCollision(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnCollision(vecLeft[i]->GetCollider());
					}
				}
				// Prev X, Cur O
				else
				{
					// �浹ü �� �ϳ��� Dead ���¶�� �浹 ��Ű�� ����
					if (vecLeft[i]->isDead() || vecRight[j]->isDead())
					{
						// �ƹ��͵� ���� ����
					}
					else
					{
						vecLeft[i]->GetCollider()->OnCollisionEnter(vecRight[j]->GetCollider());
						vecRight[j]->GetCollider()->OnCollisionEnter(vecLeft[i]->GetCollider());
						iter->second = true;
					}
				}
			}
			else
			{
				// Prev O, Cur X
				if (iter->second)
				{
					vecLeft[i]->GetCollider()->OnCollisionExit(vecRight[j]->GetCollider());
					vecRight[j]->GetCollider()->OnCollisionExit(vecLeft[i]->GetCollider());
					iter->second = false;
				}
				else
				{
					// �ƹ��͵� ���� ����
				}
			}
		}
	}
}

bool CCollisionManager::IsCollision(CCollider* pLeftCollider, CCollider* pRightCollider)
{
	// �簢 �浹
	fPoint fptLeftPos = pLeftCollider->GetFinalPos();
	fPoint fptLeftScale = pLeftCollider->GetScale();

	fPoint fptRightPos = pRightCollider->GetFinalPos();
	fPoint fptRightScale = pRightCollider->GetScale();

	if (abs(fptLeftPos.x - fptRightPos.x) < (fptLeftScale.x + fptRightScale.x) / 2.f
		&& abs(fptLeftPos.y - fptRightPos.y) < (fptLeftScale.y + fptRightScale.y) / 2.f)
	{
		return true;
	}

	return false;
}

void CCollisionManager::init()
{
}

void CCollisionManager::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_GAMEOBJ::SIZE; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_GAMEOBJ::SIZE; iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				// �浹�� �˻��ؾ��ϴ� �� �׷�
				CollisionGroupUpdate((GROUP_GAMEOBJ)iRow, (GROUP_GAMEOBJ)iCol);
			}
		}
	}
}

void CCollisionManager::CheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight)
{
	// [��][��]
	UINT iRow;	// ��
	UINT iCol;	// ��

	// �� ���� ���� ������ ��
	if ((UINT)objLeft < (UINT)objRight)
	{
		iRow = (UINT)objLeft;
		iCol = (UINT)objRight;
	}
	else
	{
		iRow = (UINT)objRight;
		iCol = (UINT)objLeft;
	}

	m_arrCheck[iRow] |= (1 << iCol);
}

void CCollisionManager::UnCheckGroup(GROUP_GAMEOBJ objLeft, GROUP_GAMEOBJ objRight)
{
	// [��][��]
	UINT iRow;	// ��
	UINT iCol;	// ��

	// �� ���� ���� ������ ��
	if ((UINT)objLeft > (UINT)objRight)
	{
		iRow = (UINT)objLeft;
		iCol = (UINT)objRight;
	}
	else
	{
		iRow = (UINT)objRight;
		iCol = (UINT)objLeft;
	}

	m_arrCheck[iRow] &= ~(1 << iCol);
}

void CCollisionManager::Reset()
{
	// memset(���� �ּ�, ������ ������, ������ ũ��);
	memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_GAMEOBJ::SIZE);
	/*for (int i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; i++)
	{
		m_arrCheck[i] = 0;
	}*/
}
