#pragma once

class CCollider;
class CAnimator;

class CGameObject
{
	friend class CEventManager;

private:
	wstring m_strName;
	fPoint m_fptPos;
	fPoint m_fptScale;

	// Component
	CCollider* m_pCollider;
	CAnimator* m_pAnimator;

	bool m_bAlive;
	void SetDead();

public:
	CGameObject();
	CGameObject(const CGameObject& other);
	virtual ~CGameObject();
	virtual CGameObject* Clone() = 0;

	void SetPos(fPoint pos);
	void SetScale(fPoint scale);
	void SetName(wstring name);

	fPoint GetPos();
	fPoint GetScale();
	wstring GetName();

	bool isDead();

	virtual void update() = 0;			// �ݵ�� ��ӹ��� ��ü�� update�� �����ϵ��� ���������Լ��� ����
	virtual void finalupdate();			// ��ӹ޴� Ŭ������ �������̵� �� �� ���� ���� final Ű����
	virtual void render();
	virtual void component_render();	// ������Ʈ���� ������ ǥ���ϱ� ����

	CCollider* GetCollider();				// �浹ü ��ȯ
	void CreateCollider();					// �浹ü ����

	virtual void OnCollision(CCollider* _pOther) {}			// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// �����ǿ� �浹�� �����Լ�
	virtual void OnCollisionExit(CCollider* _pOther) {}		// �����ǿ� Ż�浹 �����Լ�

	CAnimator* GetAnimator();				// �ִϸ����� ��ȯ
	void CreateAnimator();					// �ִϸ����� ����
};

