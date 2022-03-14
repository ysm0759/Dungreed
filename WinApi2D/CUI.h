#pragma once
#include "CGameObject.h"
class CUI : public CGameObject
{
	friend class CUIManager;

private:
	vector<CUI*> m_vecChildUI;	// 자식 UI를 계층적 구조로 구현
	CUI* m_pParentUI;

	fPoint m_fptFinalPos;

	bool m_bCameraAffected;
	bool m_bMouseOn;
	bool m_bLbtnDown;			// UI에서 이전에 눌렸다.

public:
	CUI(bool bCameraAffected);	// 카메라의 영향여부를 반드시 받기 위해 기본생성자 대신 구현한 생성자 사용
	CUI(const CUI& other);
	virtual ~CUI();

	virtual CUI* Clone() = 0;

	virtual void update();
	virtual void finalupdate();
	virtual void render();

	void update_child();
	void finalupdate_child();
	void render_child();

	virtual void MouseOn();
	virtual void MouseLbtnDown();
	virtual void MouseLbtnUp();
	virtual void MouseLbtnClicked();

	fPoint GetFinalPos();
	bool GetCameraAffected();
	bool IsMouseOn();
	bool IsLbtnDown();

	CUI* GetParent();
	void AddChild(CUI* pUI);
	const vector<CUI*>& GetChildUI();

private:
	void MouseOnCheck();
};

