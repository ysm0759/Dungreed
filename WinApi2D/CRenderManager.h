#pragma once
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "Dwrite.lib")

using namespace D2D1;

class CD2DImage;

class CRenderManager
{
	SINGLETON(CRenderManager);

private:
	ID2D1Factory* m_pFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	IDWriteFactory* m_pWriteFactory;
	IWICImagingFactory* m_pImageFactory;
	ID2D1Bitmap* m_pBitmap;
	ID2D1SolidColorBrush* m_pBrush;
	
	IDWriteTextFormat* m_pTextFormat;
	
	/*
	void RenderImage(CD2DImage* img, float dstX, float dstY, float dstW, float dstH);
	void RenderFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY,
		float srcW, float srcH);

	void RenderRevFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH,
		float srcX, float srcY, float srcW, float srcH);*/
public:
	void init();


	void RenderImage(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float alpha = 1.f, float angle = 0.f, fPoint pos = { 0.f,0.f });
																							// 투명도				//회전				   // 상대좌표 
	void RenderFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH, float srcX, float srcY,
		float srcW, float srcH, float angle = 0.f, fPoint pos = { 0.f,0.f });

	void RenderRevFrame(CD2DImage* img, float dstX, float dstY, float dstW, float dstH,
		float srcX, float srcY, float srcW, float srcH, float angle = 0.f, fPoint pos = { 0.f,0.f });







	void RenderText(wstring str, float dstX, float dstY, float dstW, float dstH, float fontSize = 12.f, COLORREF color = RGB(0, 0, 0));
	void RenderRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0), float strokeWidth = 1.f);
	void RenderFillRectangle(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0), float alpha = 1.f);
	void RenderEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0), float strokeWidth = 1.f);
	void RenderFillEllipse(float dstX, float dstY, float dstW, float dstH, COLORREF color = RGB(0, 0, 0));


	ID2D1Bitmap* GetBitmap();
	ID2D1HwndRenderTarget* GetRenderTarget();
	IWICImagingFactory* GetImageFactory();
	IDWriteFactory* GetWriteFactory();
};

