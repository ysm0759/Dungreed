#include "framework.h"
#include "CTexture.h"

CTexture::CTexture()
{
	m_hDC = 0;
	m_hBMP = 0;
	m_bmpInfo = {};
}

CTexture::~CTexture()
{
	DeleteDC(m_hDC);
	DeleteObject(m_hBMP);
}

HDC CTexture::GetDC()
{
	return m_hDC;
}

HBITMAP CTexture::GetBitmap()
{
	return m_hBMP;
}

BITMAP CTexture::GetBitInfo()
{
	return m_bmpInfo;
}

int CTexture::GetBmpWidth()
{
	return (int)(m_bmpInfo.bmWidth);
}

int CTexture::GetBmpHeight()
{
	return (int)(m_bmpInfo.bmHeight);
}

void CTexture::Load(const wstring& strFilePath)
{
	m_hBMP = (HBITMAP)LoadImage(
		nullptr,								// hInstance. nullptr�� �ص� ��.
		strFilePath.c_str(),					// ���� ��θ� C style ���ڿ��� ��ȯ
		IMAGE_BITMAP,							// �̹��� Ÿ��, ��Ʈ�� �̹����� ����
		0, 0,									// �̹����� X, Y ũ��, 0�� �ָ� �̹��� ũ��� ����
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// �̹��� �ε� Ÿ��.
	);

	assert(m_hBMP);		// �̹����� ���ٸ� assert

	// ��Ʈ�ʰ� ������ DC
	m_hDC = CreateCompatibleDC(CCore::getInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBMP);

	// ��Ʈ�� ����
	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);
}

void CTexture::Create(UINT width, UINT height)
{
	HDC mainDC = CCore::getInst()->GetMainDC();
	m_hBMP = CreateCompatibleBitmap(mainDC, width, height);
	m_hDC = CreateCompatibleDC(mainDC);

	HBITMAP hOldBmp = (HBITMAP)SelectObject(m_hDC, m_hBMP);
	DeleteObject(hOldBmp);

	GetObject(m_hBMP, sizeof(BITMAP), &m_bmpInfo);
}
