#include "framework.h"
#include "CWeapon.h"

CWeapon::CWeapon()
{
	m_fDelay = 0.f;
	m_fRange = 0.f;
	m_fColScale = fPoint();
	m_eKind = ITEM_KIND::DEFAULT
}

CWeapon::~CWeapon()
{

}

void CWeapon::Attack()
{

}
