#pragma once
#include "CGameObject.h"


class CBackGround : public CGameObject
{


private:
	CD2DImage* m_pImg;
	float m_fAutoSpeed;			// �������̴� �ӵ�
	fPoint m_fDependOnSpeed;     // �÷��̾ ���� �����̴� ��� �ӵ�
	float m_fScale;				// ���������� ����									default = 4
	float m_fRepeatGap;			// ����� ���� �ݺ��ɶ� ���� ���� Gap				default = 0;
	float m_fAlpha;				// ����� ����										default = 1;
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


