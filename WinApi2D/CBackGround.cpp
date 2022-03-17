#include "framework.h"
#include "CBackGround.h"

#include "CD2DImage.h"

CBackGround::CBackGround()
{
    m_pImg = nullptr;
    m_fSpeed = 1;
    m_isFix = true;
    m_isAuto = false;
    m_isDirLeft = true;
}

CBackGround::CBackGround(float fSpeed , bool isAuto , bool isDirLeft)
{
    m_pImg = nullptr;
    m_fSpeed = fSpeed;
    m_isFix = false;
    m_isAuto = isAuto;
    m_isDirLeft = isDirLeft;
}

CBackGround::~CBackGround()
{
   // delete m_pImg;
}

void CBackGround::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * 4.f, m_pImg->GetHeight() * 4.f));
}

CBackGround* CBackGround::Clone()
{
    return nullptr;
}

void CBackGround::update()
{

    if (true == m_isAuto)
    {
        fPoint pos = GetPos();
        pos.x += m_fSpeed * fDT;
        SetPos(pos);
    }
}

void CBackGround::render()
{
    if (nullptr == m_pImg)
    {
        return;
    }


    fPoint pos = GetPos();
    fPoint scale = GetScale();

    if (true == m_isFix) // 고정 배경
    {
        pos = CCameraManager::getInst()->GetRenderPos(pos);

        CRenderManager::getInst()->RenderImage(
            m_pImg,
            pos.x - scale.x / 2,
            pos.y - scale.y / 2,
            pos.x + scale.x / 2,
            pos.y + scale.y / 2
        );
    }
    else //캐릭터가 움직일때 따라 움직이는 배경
    {
        fPoint renderPos = CCameraManager::getInst()->GetRenderPos(pos);
        renderPos = pos + (renderPos - pos) / m_fSpeed;    // 배경은 살짝 느리게 이동

        CRenderManager::getInst()->RenderImage(
            m_pImg,
            renderPos.x,
            renderPos.y,
            renderPos.x + scale.x,
            renderPos.y + scale.y
        );
    }

}
