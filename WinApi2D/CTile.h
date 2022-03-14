#pragma once
#include "CGameObject.h"

class CD2DImage;

class CTile : public CGameObject
{

private:
	CD2DImage* m_pImg;
	int m_iIdx;			// 텍스쳐 인덱스

public:
	const static int SIZE_TILE = 32;

	CTile();
	virtual ~CTile();

	virtual CTile* Clone();

	virtual void update();
	virtual void render();

	void SetTexture(CD2DImage* pTex);
	void SetImgIdx(UINT idx);

	virtual void Save(FILE* pFile);
	virtual void Load(FILE* pFile);
};

