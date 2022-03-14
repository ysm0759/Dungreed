#pragma once

class CTexture;

class CCore
{
	SINGLETON(CCore);

private:
	HDC m_hDC;

public:
	void update();
	void render();
	void init();

	HDC GetMainDC();
};

