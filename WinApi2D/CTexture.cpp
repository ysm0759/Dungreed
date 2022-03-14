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
		nullptr,								// hInstance. nullptr로 해도 됨.
		strFilePath.c_str(),					// 파일 경로를 C style 문자열로 변환
		IMAGE_BITMAP,							// 이미지 타입, 비트맵 이미지로 지정
		0, 0,									// 이미지의 X, Y 크기, 0을 주면 이미지 크기로 설정
		LR_CREATEDIBSECTION | LR_LOADFROMFILE	// 이미지 로딩 타입.
	);

	assert(m_hBMP);		// 이미지가 없다면 assert

	// 비트맵과 연결할 DC
	m_hDC = CreateCompatibleDC(CCore::getInst()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBMP);

	// 비트맵 정보
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
