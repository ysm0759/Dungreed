#include "framework.h"
#include "CEquipment.h"

CEquipment::CEquipment()
{
	this->m_eItemType = (ITEM_TYPE)0;
	this->m_sExplanation = L"�Ѵ� �и� �� 1��ٴ� ���";
	this->m_sEffect = L"ŷ��¯ȿ��";
	this->m_sName = L"����ŷ�����׷���";
	this->m_sType = L"������ �ﵵ��!!";
	m_cItemStat = Stat();
}

CEquipment::~CEquipment()
{

}

void CEquipment::SetName(string name)
{
}

void CEquipment::SetItemType(ITEM_TYPE itemType)
{

}
