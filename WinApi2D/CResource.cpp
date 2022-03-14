#include "framework.h"
#include "CResource.h"

CResource::CResource()
{
}

CResource::~CResource()
{
}

void CResource::SetKey(const wstring& strKey)
{
	m_strKey = strKey;
}

void CResource::SetRelativePath(const wstring& strPath)
{
	m_strRelativePath = strPath;
}

const wstring& CResource::GetKey()
{
	return m_strKey;
}

const wstring& CResource::GetRelativePath()
{
	return m_strRelativePath;
}
