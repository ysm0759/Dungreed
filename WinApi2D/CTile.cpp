#include "framework.h"
#include "CTile.h"
#include "CD2DImage.h"

CTile::CTile()
{
	m_pImg = nullptr;
	m_iIdx = 0;
	SetScale(fPoint(SIZE_TILE, SIZE_TILE));
}

CTile::~CTile()
{
}

CTile* CTile::Clone()
{
	return new CTile(*this);
}

void CTile::update()
{
}

void CTile::render()
{
	if (nullptr == m_pImg)
	{
		return;
	}

	UINT iWidth = m_pImg->GetWidth();
	UINT iHeight = m_pImg->GetHeight();

	UINT iMaxRow = iHeight / SIZE_TILE;
	UINT iMaxCol = iWidth / SIZE_TILE;

	UINT iCurRow = (m_iIdx / iMaxCol) % iMaxRow;
	UINT iCurCol = (m_iIdx % iMaxCol);

	fPoint fptRenderPos = CCameraManager::getInst()->GetRenderPos(GetPos());
	fPoint fptScale = GetScale();

	CRenderManager::getInst()->RenderFrame(
		m_pImg,
		fptRenderPos.x,
		fptRenderPos.y,
		fptScale.x,
		fptScale.y,
		iCurCol * fptScale.x,
		iCurRow * fptScale.y,
		fptScale.x,
		fptScale.y
	);
}

void CTile::SetTexture(CD2DImage* pImg)
{
	m_pImg = pImg;
}

void CTile::SetImgIdx(UINT idx)
{
	m_iIdx = idx;
}

void CTile::Save(FILE* pFile)
{
	fwrite(&m_iIdx, sizeof(int), 1, pFile);
}

void CTile::Load(FILE* pFile)
{
	fread(&m_iIdx, sizeof(int), 1, pFile);
}
