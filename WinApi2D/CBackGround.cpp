#include "framework.h"
#include "CBackGround.h"

#include "CD2DImage.h"

CBackGround::CBackGround()
{
   m_pImg               = nullptr;
   m_fAutoSpeed         = 0;	    
   m_fDependOnSpeed     = 0;        
   m_fScale             = 4.f;
   m_fRepeatGap         = 0.f;
   m_fAlpha             = 1.f;
   m_iOption            = 1;		 //고정상태

}


CBackGround::~CBackGround()
{
   // delete m_pImg;
}




void CBackGround::Load(wstring strKey, wstring strPath)
{
    m_pImg = CResourceManager::getInst()->LoadD2DImage(strKey, strPath);
    SetScale(fPoint(m_pImg->GetWidth() * m_fScale, m_pImg->GetHeight() * m_fScale));
}

CBackGround* CBackGround::Clone()
{
    return new CBackGround(*this);
}

void CBackGround::update()
{
    fPoint pos = GetPos();
    if (GetOption((UINT)BACK_OPTION::AUTO))
    {

        if (GetOption((UINT)BACK_OPTION::LEFT))
            pos.x -= m_fAutoSpeed * fDT;
        if (GetOption((UINT)BACK_OPTION::RIGHT))
            pos.x += m_fAutoSpeed * fDT;
        if (GetOption((UINT)BACK_OPTION::UP))
            pos.y -= m_fAutoSpeed * fDT;
        if (GetOption((UINT)BACK_OPTION::DOWN))
            pos.y -= m_fAutoSpeed * fDT;
    }
    if (GetOption((UINT)BACK_OPTION::REPEAT))
    {
        fPoint pos = CCameraManager::getInst()->GetLookAt();
        if (GetPos().x + GetScale().x / 2 + m_fRepeatGap / 2 <= 0)
        {
            pos.x = GetScale().x + GetScale().x / 2.f + m_fRepeatGap / 2;

        }
    }
    SetPos(pos);
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


    if (GetOption((UINT)BACK_OPTION::FIX))
    {
        fPoint renderPos = CCameraManager::getInst()->GetRenderPos(pos);

        CRenderManager::getInst()->RenderImage(
            m_pImg,
            pos.x - scale.x / 2,
            pos.y - scale.y / 2,
            pos.x + scale.x / 2,
            pos.y + scale.y / 2,
            m_fAlpha
        );
    }
    else
    {
        if (GetOption((UINT)BACK_OPTION::AUTO))
        {
            pos = CCameraManager::getInst()->GetRenderPos(pos);

            CRenderManager::getInst()->RenderImage(
                m_pImg,
                pos.x - scale.x / 2,
                pos.y - scale.y / 2,
                pos.x + scale.x / 2,
                pos.y + scale.y / 2,
                m_fAlpha
            );
        }
        if (GetOption((UINT)BACK_OPTION::DEPEND_ON))
        {
            fPoint renderPos = CCameraManager::getInst()->GetRenderPos(pos);
            
            renderPos.y = pos.y + (renderPos.y - pos.y) / m_fDependOnSpeed;    // 배경은 살짝 느리게 이동

            CRenderManager::getInst()->RenderImage(
                m_pImg,
                renderPos.x,
                renderPos.y,
                renderPos.x + scale.x,
                renderPos.y + scale.y,
                m_fAlpha
            );
        }
        
    }

}



void CBackGround::OnFix()
{
    m_iOption = 0;
    SetOption((UINT)BACK_OPTION::FIX);
}

void CBackGround::OnAuto(float autoSpeed, bool m_fRepeat)
{
   
    RemoveOption((UINT)BACK_OPTION::FIX);
    SetOption((UINT)BACK_OPTION::AUTO);
    m_fAutoSpeed = autoSpeed;
    SetLeft();
}

void CBackGround::OnDependOnObject(float dependOnSpeed)
{
    RemoveOption((UINT)BACK_OPTION::FIX);
    SetOption((UINT)BACK_OPTION::DEPEND_ON);
    m_fDependOnSpeed = dependOnSpeed;
}

void CBackGround::OnRepeat(float repeatGap)
{
    RemoveOption((UINT)BACK_OPTION::FIX);
    SetOption((UINT)BACK_OPTION::REPEAT);
    this->m_fRepeatGap = repeatGap;
}


void CBackGround::SetLeft()
{
    if (false == GetOption((UINT)BACK_OPTION::AUTO))
        assert(nullptr);
    SetOption((UINT)BACK_OPTION::LEFT);
    RemoveOption((UINT)BACK_OPTION::RIGHT);

}


void CBackGround::SetRight()
{
    if (false == GetOption((UINT)BACK_OPTION::AUTO))
        assert(nullptr);
    SetOption((UINT)BACK_OPTION::RIGHT);

    RemoveOption((UINT)BACK_OPTION::LEFT);
}


void CBackGround::SetUp()
{
    if (false == GetOption((UINT)BACK_OPTION::AUTO))
        assert(nullptr);
    SetOption((UINT)BACK_OPTION::UP);

    RemoveOption((UINT)BACK_OPTION::DOWN);
}

void CBackGround::SetDown()
{
    if (false == GetOption((UINT)BACK_OPTION::AUTO))
        assert(nullptr);
    SetOption((UINT)BACK_OPTION::DOWN);

    RemoveOption((UINT)BACK_OPTION::UP);
}



void CBackGround::SetAlpha(float alpha)
{
    m_fAlpha = alpha;
}
void CBackGround::SetBackScale(float scale)
{
    m_fScale = scale;
}




void CBackGround::SetOption(UINT bit)	   //해당 비트를 1로 채움
{
    m_iOption |= (1 << bit);
}

bool CBackGround::GetOption(UINT bit)	   //해당 비트가 1이면 true 아니면 false
{
    return m_iOption & (1 << bit);
}

void CBackGround::RemoveOption(UINT bit) //해당 비트 제거
{
    m_iOption &= ~(1 << bit);
}


