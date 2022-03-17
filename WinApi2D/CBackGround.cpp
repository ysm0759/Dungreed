#include "framework.h"
#include "CBackGround.h"

#include "CD2DImage.h"

CBackGround::CBackGround()
{
   m_pImg               = nullptr;
   m_fAutoSpeed         = 0;	    
   m_fDependOnSpeed     = 0;        
   m_isFix              = true;		
   m_isDirLeft          = true;		
   m_isDependOnPlayer   = false;  
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

    if (false == m_isFix)
    {

        fPoint pos = GetPos();
        if (true == m_isDirLeft)
            pos.x -= m_fAutoSpeed * fDT;
        else
            pos.x += m_fAutoSpeed * fDT;

        SetPos(pos);
    }
}

void CBackGround::render()
{
    if (nullptr == m_pImg)
    {
        Logger::info(L"BackGound 이미지 없음 !!!!!!!!!!!");
        return;
    }


    fPoint pos = GetPos();
    fPoint scale = GetScale();


    if (true == m_isDependOnPlayer) //플레이어 의존 
    {
        fPoint renderPos = CCameraManager::getInst()->GetRenderPos(pos);
        renderPos = pos + (renderPos - pos) / m_fDependOnSpeed;    // 배경은 살짝 느리게 이동

        CRenderManager::getInst()->RenderImage(
            m_pImg,
            renderPos.x,
            renderPos.y,
            renderPos.x + scale.x,
            renderPos.y + scale.y
        );
    }
    else // 배경이 움직이면서 플레이어가 움직일때 가속도를 붙게 하고 싶으면 SetAuto() SetDependOnPlayer()
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


}



void CBackGround::SetFix()
{
    m_isFix = true;
    m_isDependOnPlayer = false;
}

void CBackGround::SetAuto(float autoSpeed)
{
    m_isFix = false;
    m_fAutoSpeed = autoSpeed;
}

void CBackGround::SetDependOnPlayer(float dependOnSpeed)
{
    m_isDependOnPlayer = true;
    m_fDependOnSpeed = dependOnSpeed;
}

void CBackGround::SetIndependentOnPlayer()
{
    m_isDependOnPlayer = false;
    m_fDependOnSpeed = 0;
}

void CBackGround::SetLeft()
{
    m_isDirLeft = true;
}

void CBackGround::SetRight()
{
    m_isDirLeft = false;
}