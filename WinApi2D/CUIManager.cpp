#include "framework.h"
#include "CUIManager.h"
#include "CScene.h"
#include "CUI.h"

CUIManager::CUIManager()
{
	m_pFocusedUI = nullptr;
}

CUIManager::~CUIManager()
{

}

void CUIManager::update()
{
	m_pFocusedUI = GetFocusedUI();
	CUI* pUI = GetTargetUI(m_pFocusedUI);

	if (nullptr != pUI)
	{
		pUI->MouseOn();

		if (KeyDown(VK_LBUTTON))
		{
			pUI->MouseLbtnDown();
			pUI->m_bLbtnDown = true;
		}
		else if (KeyUp(VK_LBUTTON))
		{
			pUI->MouseLbtnUp();

			if (pUI->m_bLbtnDown)
			{
				pUI->MouseLbtnClicked();
			}
			pUI->m_bLbtnDown = false;
		}
	}
}

void CUIManager::SetFocusedUI(CUI* pUI)
{
	// 이미 포커싱된 UI 이거나 이전에 포커싱된 UI가 없었을 경우
	if (m_pFocusedUI == pUI || nullptr == m_pFocusedUI)
	{
		m_pFocusedUI = pUI;
		return;
	}

	m_pFocusedUI = pUI;

	if (nullptr == m_pFocusedUI)
		return;

	CScene* pCurScene = CSceneManager::getInst()->GetCurScene();
	vector<CGameObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CGameObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); iter++)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}


CUI* CUIManager::GetTargetUI(CUI* pParentUI)
{
	list<CUI*> queue;
	vector<CUI*> vecNoneTarget;
	CUI* pTargetUI = nullptr;

	if (nullptr == pParentUI)
		return nullptr;

	queue.push_back(pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}

	}

	if (KeyUp(VK_LBUTTON))
	{
		for (size_t i = 0; i < vecNoneTarget.size(); i++)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}

CUI* CUIManager::GetFocusedUI()
{
	CScene* pCurScene = CSceneManager::getInst()->GetCurScene();
	vector<CGameObject*>& vecUI = pCurScene->GetUIGroup();
	CUI* pFocusedUI = m_pFocusedUI;

	if (!KeyDown(VK_LBUTTON))
	{
		return pFocusedUI;
	}

	vector<CGameObject*>::iterator targetiter = vecUI.end();
	vector<CGameObject*>::iterator iter = vecUI.begin();
	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	if (vecUI.end() == targetiter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targetiter;

	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}
