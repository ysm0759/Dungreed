#pragma once
#include "CGameObject.h"
class CUI : public CGameObject
{
	friend class CUIManager;

private:
	vector<CUI*> m_vecChildUI;	// �ڽ� UI�� ������ ������ ����
	CUI* m_pParentUI;

	fPoint m_fptFinalPos;

	bool m_bCameraAffected;
	bool m_bMouseOn;
	bool m_bLbtnDown;			// UI���� ������ ���ȴ�.

public:
	CUI(bool bCameraAffected);	// ī�޶��� ���⿩�θ� �ݵ�� �ޱ� ���� �⺻������ ��� ������ ������ ���
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

