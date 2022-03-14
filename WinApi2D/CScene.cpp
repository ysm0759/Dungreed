#include "framework.h"
#include "CScene.h"
#include "CGameObject.h"
#include "CTile.h"

CScene::CScene()
{
    m_strName = L"";
    m_iTileX = 0;
    m_iTileY = 0;
}

CScene::~CScene()
{
    // 씬이 가진 모든 게임오브젝트 삭제
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        for (int j = 0; j < m_arrObj[i].size(); j++)
        {
            delete m_arrObj[i][j];
        }
    }
}

void CScene::update()
{
    // 씬이 가진 모든 오브젝트 업데이트
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        for (int j = 0; j < m_arrObj[i].size(); j++)
        {
            if (!m_arrObj[i][j]->isDead())
                m_arrObj[i][j]->update();
        }
    }
}

void CScene::finalupdate()
{
    // 씬이 가진 모든 오브젝트 finalupdate
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        for (int j = 0; j < m_arrObj[i].size(); j++)
        {
            m_arrObj[i][j]->finalupdate();
        }
    }
}

void CScene::render()
{
    // 씬이 가진 모든 오브젝트 render
    for (int i = 0; i < (int)GROUP_GAMEOBJ::SIZE; i++)
    {
        if ((UINT)GROUP_GAMEOBJ::TILE == i)
        {
            render_tile();
            continue;
        }
        for (vector<CGameObject*>::iterator iter = m_arrObj[i].begin();
            iter != m_arrObj[i].end(); )
        {
            if (!(*iter)->isDead())
            {
                (*iter)->render();
                iter++;
            }
            else
            {
                iter = m_arrObj[i].erase(iter);
            }
        }
    }
}

void CScene::render_tile()
{
    const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);

    fPoint fptCamLook = CCameraManager::getInst()->GetLookAt();
    fPoint fptLeftTop = fptCamLook - fPoint(WINSIZEX, WINSIZEY) / 2.f;

    int iLTCol = (int)fptLeftTop.x / CTile::SIZE_TILE;
    int iLTRow = (int)fptLeftTop.y / CTile::SIZE_TILE;
    int iLTIdx = m_iTileX * iLTRow + iLTCol;

    int iClientWidth = (int)WINSIZEX / CTile::SIZE_TILE;
    int iClientHeight = (int)WINSIZEY / CTile::SIZE_TILE;
    for (int iCurRow = iLTRow; iCurRow <= (iLTRow + iClientHeight); ++iCurRow)
    {
        for (int iCurCol = iLTCol; iCurCol <= (iLTCol + iClientWidth); ++iCurCol)
        {
            if (iCurCol < 0 || m_iTileX <= (UINT)iCurCol || iCurRow < 0 || m_iTileY <= (UINT)iCurRow)
            {
                continue;
            }
            int iIdx = (m_iTileX * iCurRow) + iCurCol;

            vecTile[iIdx]->render();
        }
    }
}

const vector<CGameObject*>& CScene::GetGroupObject(GROUP_GAMEOBJ group)
{
    return m_arrObj[(UINT)group];
}

vector<CGameObject*>& CScene::GetUIGroup()
{
    return m_arrObj[(UINT)GROUP_GAMEOBJ::UI];
}

void CScene::SetName(const wstring& strName)
{
    m_strName = strName;
}

wstring CScene::GetName()
{
    return m_strName;
}

UINT CScene::GetTileX()
{
    return m_iTileX;
}

UINT CScene::GetTileY()
{
    return m_iTileY;
}

void CScene::AddObject(CGameObject* pObj, GROUP_GAMEOBJ type)
{
    m_arrObj[(int)type].push_back(pObj);
}

void CScene::DeleteGroup(GROUP_GAMEOBJ group)
{
    for (int i = 0; i < m_arrObj[(UINT)group].size(); i++)
    {
        delete m_arrObj[(UINT)group][i];
    }
    m_arrObj[(UINT)group].clear();
}

void CScene::DeleteAll()
{
    for (int i = 0; i < (UINT)GROUP_GAMEOBJ::SIZE; i++)
    {
        DeleteGroup((GROUP_GAMEOBJ)i);
    }
}

void CScene::CreateTile(UINT xSize, UINT ySize)
{
    DeleteGroup(GROUP_GAMEOBJ::TILE);

    m_iTileX = xSize;
    m_iTileY = ySize;

    CD2DImage* pImg = CResourceManager::getInst()->LoadD2DImage(L"Tile", L"texture\\tile\\tilemap.bmp");

    for (UINT i = 0; i < ySize; i++)
    {
        for (UINT j = 0; j < xSize; j++)
        {
            CTile* pTile = new CTile();
            pTile->SetPos(fPoint((float)(j * CTile::SIZE_TILE), (float)(i * CTile::SIZE_TILE)));
            pTile->SetTexture(pImg);
            AddObject(pTile, GROUP_GAMEOBJ::TILE);
        }
    }
}

void CScene::LoadTile(const wstring& strPath)
{
    FILE* pFile = nullptr;

    _wfopen_s(&pFile, strPath.c_str(), L"rb");      // w : write, b : binary
    assert(pFile);

    UINT xCount = 0;
    UINT yCount = 0;

    fread(&xCount, sizeof(UINT), 1, pFile);
    fread(&yCount, sizeof(UINT), 1, pFile);

    CreateTile(xCount, yCount);

    const vector<CGameObject*>& vecTile = GetGroupObject(GROUP_GAMEOBJ::TILE);

    for (UINT i = 0; i < vecTile.size(); i++)
    {
        ((CTile*)vecTile[i])->Load(pFile);
    }

    fclose(pFile);
}
