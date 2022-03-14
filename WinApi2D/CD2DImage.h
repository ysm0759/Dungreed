#pragma once
#include "CResource.h"
#include <d2d1.h>
#pragma comment(lib, "D2D1.lib")

class CD2DImage : public CResource
{
	ID2D1Bitmap* m_pBitmap;

public:
	CD2DImage();
	~CD2DImage();

	ID2D1Bitmap* GetImage();
	void SetImage(ID2D1Bitmap* bitmap);

	int GetWidth();
	int GetHeight();
};

