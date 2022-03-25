#pragma once

class CTexture;

class CCore
{
	SINGLETON(CCore);

private:
	HDC m_hDC;
	CTexture* m_pMemTex;

	CTexture* m_pMagentaTex;

	// GDI
	HBRUSH	m_arrBrush[(UINT)TYPE_BRUSH::SIZE];
	HPEN	m_arrPen[(UINT)TYPE_PEN::SIZE];
	HFONT	m_arrFont[(UINT)TYPE_FONT::SIZE];

public:
	void update();
	void render();
	void init();

	void	CreateBrushPenFont();
	HBRUSH	getBrush(eBRUSH type);
	HPEN	getPen(ePEN type);
	HFONT	getFont(eFONT type);
	HDC GetMainDC();

};

