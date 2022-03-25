#include "framework.h"
#include "CCore.h"
#include "CGameObject.h"
#include "CTexture.h"
#include <time.h>

CCore::CCore()
{
	// ���� ȭ���� �׸��� ���� DC �ڵ鰪 �ʱ�ȭ
	m_hDC = 0;
}

CCore::~CCore()
{

}

void CCore::update()
{
	// ���� update���� �߰��� �̺�Ʈ�� ������ �ʱ⿡ �Ѳ����� ó��
	CEventManager::getInst()->update();

	CTimeManager::getInst()->update();
	CKeyManager::getInst()->update();
	CSoundManager::getInst()->update();
	CSceneManager::getInst()->update();
	CCollisionManager::getInst()->update();
	CCameraManager::getInst()->update();
	CUIManager::getInst()->update();
}

void CCore::render()
{
	CRenderManager::getInst()->GetRenderTarget()->BeginDraw();

	CRenderManager::getInst()->RenderFillRectangle(-1, -1, WINSIZEX + 1, WINSIZEY + 1, RGB(255, 255, 255));

	CSceneManager::getInst()->render();
	CCameraManager::getInst()->render();

	// ������ ��ܿ� FPS ǥ��
	WCHAR strFPS[6];
	swprintf_s(strFPS, L"%5d", CTimeManager::getInst()->GetFPS());
	CRenderManager::getInst()->RenderText(strFPS, WINSIZEX - 50, 10, WINSIZEX, 50, 12, RGB(0, 0, 0));

	CRenderManager::getInst()->GetRenderTarget()->EndDraw();
}

void CCore::init()
{
	CreateBrushPenFont();
	m_hDC = GetDC(hWnd);

	CPathManager::getInst()->init();
	CTimeManager::getInst()->init();
	CKeyManager::getInst()->init();
	CSoundManager::getInst()->init();
	CRenderManager::getInst()->init();
	CCameraManager::getInst()->init();
	CSceneManager::getInst()->init();
	CCollisionManager::getInst()->init();


	srand((unsigned int)time(NULL));
}


void CCore::CreateBrushPenFont()
{
	// brush
	m_arrBrush[(UINT)TYPE_BRUSH::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);	// ���� ���� �� ��Ƴ��� stock�� ����
	// font
	m_arrFont[(UINT)TYPE_FONT::COMIC24] = CreateFont(24, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	m_arrFont[(UINT)TYPE_FONT::COMIC28] = CreateFont(28, 10, 0, 0, 1000, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	m_arrFont[(UINT)TYPE_FONT::COMIC18] = CreateFont(18, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Comic Sans MS"));
	// pen
	m_arrPen[(UINT)TYPE_PEN::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)TYPE_PEN::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)TYPE_PEN::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)TYPE_PEN::WHITE] = (HPEN)GetStockObject(WHITE_PEN);
}

HBRUSH CCore::getBrush(eBRUSH type)
{
	return m_arrBrush[(UINT)type];
}

HPEN CCore::getPen(ePEN type)
{
	return m_arrPen[(UINT)type];
}

HFONT CCore::getFont(eFONT type)
{
	return m_arrFont[(UINT)type];
}