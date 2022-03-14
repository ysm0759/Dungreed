#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

private:
	WCHAR m_strContentPath[255];		// 윈도우 최대 경로 255

public:
	void init();

	const wchar_t* GetContentPath();	// 리소스 저장 폴더의 경로 반환
	const wchar_t* GetRelativeContentPath();	// 리소스 저장 폴더의 상대 경로 반환
};

