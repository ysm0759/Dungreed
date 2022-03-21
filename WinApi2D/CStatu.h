#pragma once



class CStatu
{
	friend class CGameObject;

	int m_iObjectStatu;
	float m_fGravity;
	float m_fForce;
	fVec2 m_fLook;
	fVec2 m_fDashDir;
	CGameObject* m_pOwner;		// 충돌체를 가지는 게임오브젝트의 주소

	void Jump();
	void Gravity();
	void Fouce();
	void Look();
public:
	CStatu();
	CStatu(const CStatu& other);
	~CStatu();

	void SetForceDir(fVec2 dashDir);
	void SetForce(float force);
	void SetLook(fVec2 look);
	void update();


	CStatu* GetStatu();

	void SetStatu(UINT bit);
	bool IsStatu(UINT bit);
	void RemoveStatu(UINT bit);
};

