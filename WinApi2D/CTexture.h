#pragma once
#include "CResource.h"
class CTexture : public CResource
{
private:
	HDC		m_hDC;
	HBITMAP m_hBMP;
	BITMAP	m_bmpInfo;

public:
	CTexture();
	virtual ~CTexture();

	HDC GetDC();
	HBITMAP GetBitmap();
	BITMAP GetBitInfo();

	int GetBmpWidth();
	int GetBmpHeight();

	void Load(const wstring& strFilePath);
	void Create(UINT width, UINT height);
};

