#pragma once
#include "CScene.h"

class CD2DImage;
class CButtonUI;
class CTileButton;

class CScene_Tool : public CScene
{
private:
	CD2DImage* m_pMap;

	HWND m_hWnd;
	UINT m_iIdx;
	GROUP_TILE m_gTile;
	float m_velocity;

	UINT m_iTileX;
	UINT m_iTileY;

public:
	CScene_Tool();
	~CScene_Tool();

	virtual void update();
	virtual void render();

	virtual void Enter();
	virtual void Exit();

	void SetIdx(UINT idx);
	void SetTileIdx();		// 마우스와 상호작용해서 타일을 바꿈.
	void SetGroup(GROUP_TILE group);
	void SetTileGroup();

	void CreateTile(UINT xSize, UINT ySize);
	void SaveTile(const wstring& strPath);
	void LoadTile(const wstring& strPath);
	void SaveTileData();
	void LoadTileData();
	void LoadMap();

	void ClickTileGroup(CButtonUI* button);
	void ClickTile(CTileButton* button);

private:
	void CreateTilePanel();

	void PrintMap();
	void PrintTileLine();
	void PrintTileGroup();


};

