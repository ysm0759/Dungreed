#include "framework.h"
#include "CAnimation.h"
#include "CAnimator.h"
#include "CGameObject.h"
#include "CTexture.h"

CAnimation::CAnimation()
{
    m_strName = L"";
    m_pAnimator = nullptr;
    m_pImg = nullptr;
    m_iCurFrm = 0;
    m_fAccTime = 0;
}

CAnimation::~CAnimation()
{
}


CAnimation::CAnimation(const CAnimation& pOther)
{
    m_strName = pOther.m_strName;
    for (int i = 0; i < pOther.m_vecFrm.size(); i++)
    {
        m_vecFrm.push_back(pOther.m_vecFrm[i]);
    }
    m_iCurFrm = pOther.m_iCurFrm;
    m_fAccTime = pOther.m_fAccTime;
    m_bReverse = pOther.m_bReverse;

    m_pAnimator = nullptr;
    m_pImg = pOther.m_pImg;
}


void CAnimation::SetName(const wstring& strName)
{
    m_strName = strName;
}

const wstring& CAnimation::GetName()
{
    return m_strName;
}

void CAnimation::SetFrame(int frmIndex)
{
    m_iCurFrm = frmIndex;
}

tAniFrm& CAnimation::GetFrame(int frmIndex)
{
    return m_vecFrm[frmIndex];
}

void CAnimation::SetSize(fPoint size)
{
    m_fSize = size;
}

void CAnimation::SetReverse(bool reverse)
{
    m_bReverse = reverse;
}

void CAnimation::update()
{
    m_fAccTime += fDT;

    if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
    {
        m_iCurFrm++;
        m_iCurFrm %= m_vecFrm.size();
        m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;
    }
}

void CAnimation::render()
{
    CGameObject* pObj = m_pAnimator->GetObj();
    fPoint fptPos = pObj->GetPos();
    tAniFrm frm = m_vecFrm[m_iCurFrm];

    fptPos = fptPos + frm.fptOffset;
    fptPos = CCameraManager::getInst()->GetRenderPos(fptPos);


    if (m_bReverse)
    {
        CRenderManager::getInst()->RenderRevFrame(
            m_pImg,
            fptPos.x - frm.fptSlice.x / 2.f - m_fSize.x,
            fptPos.y - frm.fptSlice.y / 2.f - m_fSize.y,
            fptPos.x + frm.fptSlice.x / 2.f + m_fSize.x,
            fptPos.y + frm.fptSlice.y / 2.f + m_fSize.y,
            frm.fptLT.x,
            frm.fptLT.y,
            frm.fptLT.x + frm.fptSlice.x,
            frm.fptLT.y + frm.fptSlice.y
            //ㅁㄴㅇㄹ
        );
    }
    else
    {
            CRenderManager::getInst()->RenderFrame(
            m_pImg,
            fptPos.x - frm.fptSlice.x / 2.f - m_fSize.x,
            fptPos.y - frm.fptSlice.y / 2.f - m_fSize.y,
            fptPos.x + frm.fptSlice.x / 2.f + m_fSize.x,
            fptPos.y + frm.fptSlice.y / 2.f + m_fSize.y,
            frm.fptLT.x,
            frm.fptLT.y,
            frm.fptLT.x + frm.fptSlice.x,
            frm.fptLT.y + frm.fptSlice.y
            //ㅁㄴㅇㄹ
        );
    }

}

void CAnimation::Create(CD2DImage* img,     // 애니메이션의 이미지
                        fPoint lt,          // 애니메이션 시작 프레임의 좌상단 좌표
                        fPoint slice,       // 애니메이션 프레임의 크기
                        fPoint step,        // 애니메이션 프레임의 반복 위치
                        float duration,     // 애니메이션 프레임 지속시간
                        UINT frmCount)      // 애니메이션 프레임 갯수
{
    m_pImg = img;

    tAniFrm frm = {};
    for (UINT i = 0; i < frmCount; i++)
    {
        frm.fDuration = duration;
        frm.fptSlice = slice;
        frm.fptLT = lt + step * i;

        m_vecFrm.push_back(frm);
    }
}
