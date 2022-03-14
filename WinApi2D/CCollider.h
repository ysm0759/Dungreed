#pragma once

class CGameObject;

class CCollider
{
	friend class CGameObject;

private:
	static UINT s_iID;

	CGameObject* m_pOwner;		// �浹ü�� ������ ���ӿ�����Ʈ�� �ּ�
	fPoint m_fptOffsetPos;		// �浹ü�� ������(������)
	fPoint m_fptFinalPos;		// �浹ü�� ���� ��ġ
	fPoint m_fptScale;			// �浹ü�� ũ��
	int m_iColCount;		// �浹��

	UINT m_iID;					// �浹ü ������ ID ��

public:
	CCollider();
	CCollider(const CCollider& other);
	~CCollider();

	CGameObject* GetObj();
	fPoint GetOffsetPos();
	fPoint GetFinalPos();
	fPoint GetScale();

	void SetOffsetPos(fPoint offsetPos);
	void SetFinalPos(fPoint finalPos);
	void SetScale(fPoint scale);
	UINT GetID();

	CCollider& operator=(CCollider& other) = delete;	// �Լ��� ����� �� ���� ����.

	void finalupdate();
	void render();

	// �浹 ���� �Լ�
	void OnCollision(CCollider* pOther);
	void OnCollisionEnter(CCollider* pOther);
	void OnCollisionExit(CCollider* pOther);
};

