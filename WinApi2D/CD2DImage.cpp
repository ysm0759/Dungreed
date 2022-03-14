#include "framework.h"
#include "CD2DImage.h"

CD2DImage::CD2DImage()
{
	m_pBitmap = nullptr;
}

CD2DImage::~CD2DImage()
{
}

ID2D1Bitmap* CD2DImage::GetImage()
{
	return m_pBitmap;
}

void CD2DImage::SetImage(ID2D1Bitmap* bitmap)
{
	m_pBitmap = bitmap;
}

int CD2DImage::GetWidth()
{
	return (int)m_pBitmap->GetSize().width;
}

int CD2DImage::GetHeight()
{
	return (int)m_pBitmap->GetSize().height;
}
