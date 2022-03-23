#include "framework.h"
#include "CEquipment.h"

CEquipment::CEquipment()
{
	this->m_eItemType = (ITEM_TYPE)0;
	this->m_sExplanation = L"ÇÑ´ë ÆÐ¸é ÇÇ 1¾ï´Ù´Â ½ë°Ë";
	this->m_sEffect = L"Å·¿ÕÂ¯È¿°ú";
	this->m_sName = L"½´ÆÛÅ·°«Á¦³×·²°Ë";
	this->m_sType = L"Á¶·ÎÀÇ »ïµµ·ù!!";
	m_cItemStat = Stat();
}

CEquipment::~CEquipment()
{

}

void CEquipment::SetEquipmentName(wstring name)
{
	m_sName = name;
}

void CEquipment::SetEquipmentItemType(ITEM_TYPE itemType)
{
	m_eItemType = itemType;
}

void CEquipment::SetEquipmentEffect(wstring name)
{

	this->m_sEffect = name;
}

void CEquipment::SetEquipmentExplanation(wstring name)
{
	this->m_sExplanation = name;
}

void CEquipment::SetEquipmentItemStat(STAT_INFO statInfo, int data)
{
	m_cItemStat.info[(UINT)statInfo] = data;

}