#include "framework.h"
#include "CRenderManager.h"
#include "CD2DImage.h"

CRenderManager::CRenderManager()
{
	m_pFactory = nullptr;
	m_pRenderTarget = nullptr;
	m_pWriteFactory = nullptr;
	m_pImageFactory = nullptr;
	m_pBitmap = nullptr;
	m_pTextFormat = nullptr;
}

CRenderManager::~CRenderManager()
{
	if (nullptr != m_pRenderTarget)
	{
		m_pRenderTarget->Release();
	}
}

void CRenderManager::init()
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	// D2D1Factory 생성
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pFactory);

	// 지정한 윈도우의 클라이언트 영역에 그림을 그리기 위한 Render Target을 생성
	m_pFactory->CreateHwndRenderTarget(RenderTargetProperties(),
		HwndRenderTargetProperties(hWnd, SizeU(rc.right, rc.bottom)),
		&m_pRenderTarget);

	// WICImagingFactory 생성
	if (S_OK == CoInitialize(nullptr))
	{

	}
	if (S_OK == CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pImageFactory)))
	{

	}
	if (S_OK == DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_pWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pWriteFactory)))
	{

	}
}

//void CRenderManager::RenderImage(CD2DImage* img, float dstX, float dstY, float dstW, float dstH)
//{
//	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
//	if (nullptr != img)
//	{
//		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
//	}
//}
//
//void CRenderManager::RenderFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH)
//{
//	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
//	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };
//
//	if (nullptr != img)
//	{
//		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
//	}
//}
//
//
//
//void CRenderManager::RenderRevFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH)
//{
//	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
//	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };
//
//	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(-1.f, 1.f,
//		D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f }));
//
//	if (nullptr != img)
//	{
//		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
//	}
//
//	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.f, 1.f,
//		D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f }));
//}

void CRenderManager::RenderText(wstring str, float dstX, float dstY, float dstW, float dstH, float fontSize, COLORREF color)
{
	m_pWriteFactory->CreateTextFormat(
		L"굴림",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"ko",
		&m_pTextFormat);

	m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;
	ID2D1SolidColorBrush* brush;

	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(red / 2.f, green / 255.0f, blue / 255.0f), &brush);
	m_pRenderTarget->DrawTextW(str.c_str(), (UINT)str.size(), m_pTextFormat,
		D2D1::RectF(dstX, dstY, dstW, dstH), brush);
}

void CRenderManager::RenderRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color)
{
	D2D1_RECT_F m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;
	ID2D1SolidColorBrush* brush;

	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(red / 2.f, green / 255.0f, blue / 255.0f), &brush);
	m_pRenderTarget->DrawRectangle(m_imgRect, brush);
}

void CRenderManager::RenderFillRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color)
{
	D2D1_RECT_F m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;
	ID2D1SolidColorBrush* brush;

	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(red / 2.f, green / 255.0f, blue / 255.0f), &brush);
	m_pRenderTarget->FillRectangle(m_imgRect, brush);
}

void CRenderManager::RenderEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color)
{
	D2D1_ELLIPSE m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;
	ID2D1SolidColorBrush* brush;

	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(red / 2.f, green / 255.0f, blue / 255.0f), &brush);
	m_pRenderTarget->DrawEllipse(m_imgRect, brush);
}

void CRenderManager::RenderFillEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color)
{
	D2D1_ELLIPSE m_imgRect = { dstX, dstY, dstW, dstH };

	int red = color & 0xFF;
	int green = (color >> 8) & 0xFF;
	int blue = (color >> 16) & 0xFF;
	ID2D1SolidColorBrush* brush;

	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(red / 2.f, green / 255.0f, blue / 255.0f), &brush);
	m_pRenderTarget->FillEllipse(m_imgRect, brush);
}

ID2D1Bitmap* CRenderManager::GetBitmap()
{
	return m_pBitmap;
}

ID2D1HwndRenderTarget* CRenderManager::GetRenderTarget()
{
	return m_pRenderTarget;
}

IWICImagingFactory* CRenderManager::GetImageFactory()
{
	return m_pImageFactory;
}

IDWriteFactory* CRenderManager::GetWriteFactory()
{
	return m_pWriteFactory;
}

void CRenderManager::RenderFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH, float angle, fPoint pos )
{
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };


	Matrix3x2F matlot = D2D1::Matrix3x2F::Scale(-1.f, 1.f, D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f });

	if (nullptr != img)
	{
		Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
		Matrix3x2F matlr = matlot * matlot;
		m_pRenderTarget->SetTransform(matlr);
		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
	}
}




void CRenderManager::RenderImage(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float angle , fPoint pos)
{
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };

	Matrix3x2F matlot = D2D1::Matrix3x2F::Scale(-1.f, 1.f, D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f });

	if (nullptr != img)
	{
		Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
		Matrix3x2F matlr = matlot * matlot;
		m_pRenderTarget->SetTransform(matlr);
		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
	}
}



void CRenderManager::RenderRevFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY, float srcW, float srcH, float angle, fPoint pos)
{
	D2D1_RECT_F imgRect = { dstX, dstY, dstW, dstH };
	D2D1_RECT_F srcRect = { srcX, srcY, srcW, srcH };

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(-1.f, 1.f,
		D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f }));
	Matrix3x2F matlot = D2D1::Matrix3x2F::Scale(-1.f, 1.f, D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f });

	if (nullptr != img)
	{
		Matrix3x2F matrot = D2D1::Matrix3x2F::Rotation(angle, D2D1::Point2F(pos.x, pos.y));
		Matrix3x2F matlr = matlot * matlot;
		m_pRenderTarget->SetTransform(matlr);
		m_pRenderTarget->DrawBitmap(img->GetImage(), imgRect, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, srcRect);
	}

	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Scale(1.f, 1.f,
		D2D1_POINT_2F{ (dstX + dstW) / 2.f, (dstY + dstH) / 2.f }));
}




