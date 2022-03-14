#pragma once

class CGameObject;

class CCollider
{
	friend class CGameObject;

private:
	static UINT s_iID;

	CGameObject* m_pOwner;		// 충돌체를 가지는 게임오브젝트의 주소
	fPoint m_fptOffsetPos;		// 충돌체의 변위차(수정값)
	fPoint m_fptFinalPos;		// 충돌체의 최종 위치
	fPoint m_fptScale;			// 충돌체의 크기
	int m_iColCount;		// 충돌중

	UINT m_iID;					// 충돌체 고유한 ID 값

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

	CCollider& operator=(CCollider& other) = delete;	// 함수를 사용할 수 없게 막음.

	void finalupdate();
	void render();

	// 충돌 시점 함수
	void OnCollision(CCollider* pOther);
	void OnCollisionEnter(CCollider* pOther);
	void OnCollisionExit(CCollider* pOther);
};

