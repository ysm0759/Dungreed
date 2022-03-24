#include "framework.h"
#include "CGameItem.h"
#include "CAnimator.h"
#include "CStatu.h"
#include "CCollider.h"


CGameItem* CGameItem::Clone()
{
	return new CGameItem(*this);
}

CGameItem::CGameItem(GROUP_GAMEITEM type)
{


	CreateCollider();
	CreateAnimator();
	this->m_eGameItem = type;
	switch (type)
	{
	case GROUP_GAMEITEM::GOLD_SMALL:
		this->m_sKey = L"GoldSmall";		     // �ִϸ��̼� ���� �̸�
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //�̹��� �ҷ�����
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7); //����
		SetScale(fPoint(30, 30));				 // �ִϸ��̼� ũ��
		GetCollider()->SetScale(fPoint(30, 30)); // �ִϸ��̼� �ݶ��̴� ũ��
		SetDrop();
		break;
	case GROUP_GAMEITEM::GOLD_BIG:
		this->m_sKey = L"GoldBig";				 // �ִϸ��̼� ���� �̸�
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //�̹��� �ҷ�����
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 7); //����
		SetScale(fPoint(30, 30));				 // �ִϸ��̼� ũ��
		GetCollider()->SetScale(fPoint(30, 30)); // �ִϸ��̼� �ݶ��̴� ũ��
		SetDrop();
		break;
	case GROUP_GAMEITEM::FAIRY_SMALL:
		this->m_sKey = L"FairyS";				 // �ִϸ��̼� ���� �̸�
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //�̹��� �ҷ�����
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 16); //����
		SetScale(fPoint(30, 30));				 // �ִϸ��̼� ũ��
		GetCollider()->SetScale(fPoint(30, 30)); // �ִϸ��̼� �ݶ��̴� ũ��
		SetStay();
		break;
	case GROUP_GAMEITEM::FAIRY_MIDDLE:
		this->m_sKey = L"FairyM";				 // �ִϸ��̼� ���� �̸�
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //�̹��� �ҷ�����
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 16); //����
		SetScale(fPoint(30, 30));				 // �ִϸ��̼� ũ��
		GetCollider()->SetScale(fPoint(30, 30)); // �ִϸ��̼� �ݶ��̴� ũ��
		SetStay();
		break;
	case GROUP_GAMEITEM::FAIRY_BIG:
		this->m_sKey = L"FairyL";				 // �ִϸ��̼� ���� �̸�
		m_pImg = CResourceManager::getInst()->LoadD2DImage(m_sKey, L"texture\\Item\\" + m_sKey + L".png");		    //�̹��� �ҷ�����
		GetAnimator()->CreateAnimation(m_sKey, m_pImg, fPoint(0, 0), fPoint(32.f, 32.f), fPoint(32.f, 0), 0.1f, 16); //����
		SetScale(fPoint(30, 30));				 // �ִϸ��̼� ũ��
		GetCollider()->SetScale(fPoint(30, 30)); // �ִϸ��̼� �ݶ��̴� ũ��
		SetStay();
		break;
	}

}	

CGameItem::~CGameItem()
{

}


void CGameItem::ItemAniRender()
{

};


