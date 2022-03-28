#pragma once
#include "CGameObject.h"


class CBackGround : public CGameObject
{


private:
	CD2DImage* m_pImg;
	float m_fAutoSpeed;			// 배경움직이는 속도
	fPoint m_fDependOnSpeed;     // 플레이어에 따라 움직이는 배경 속도
	float m_fScale;				// 원본사진의 배율									default = 4
	float m_fRepeatGap;			// 배경이 무한 반복될때 다음 장면과 Gap				default = 0;
	float m_fAlpha;				// 배경의 투명도										default = 1;
	int m_iOption;



	void SetOption(UINT bit);
	bool GetOption(UINT bit);
	void RemoveOption(UINT bit);


public:
	CBackGround();
	~CBackGround();

	void SetBackScale(float scale);

	void OnFix();
	void OnAuto(float autoSpeed ,bool m_fRepeat = true);
	void OnDependOnObject(fPoint dependOnSpeed);
	void OnRepeat(float repeatGap = 0);
	

	void SetLeft();
	void SetRight();
	void SetUp();
	void SetDown();
	void SetAlpha(float Alpha = 1.f);

	virtual CBackGround* Clone();
	virtual void update();
	virtual void render();



	void Load(wstring strKey, wstring strPath);



};


