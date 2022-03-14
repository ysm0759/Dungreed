#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
	m_strContentPath[0] = {};
}

CPathManager::~CPathManager()
{

}

void CPathManager::init()
{
	GetCurrentDirectory(255, m_strContentPath);

	// 상위 폴더로
	// + bin\\content\\

	int iLen = (int)wcslen(m_strContentPath);		// wchar_t 문자열의 길이 확인

	for (int i = iLen - 1; i >= 0; i--)
	{
		if ('\\' == m_strContentPath[i])
		{
			m_strContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_strContentPath, 255, L"\\Release\\content\\");	// wchar_t 문자열 뒤에 문자열 붙이기

	Logger::info(m_strContentPath);
}

const wchar_t* CPathManager::GetContentPath()
{
	return m_strContentPath;
}

const wchar_t* CPathManager::GetRelativeContentPath()
{
#ifdef _DEBUG
	return L"..\\Release\\content\\";
#else
	return L"content\\";
#endif
	
}
