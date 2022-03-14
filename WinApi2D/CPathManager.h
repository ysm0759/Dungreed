#pragma once
class CPathManager
{
	SINGLETON(CPathManager);

private:
	WCHAR m_strContentPath[255];		// ������ �ִ� ��� 255

public:
	void init();

	const wchar_t* GetContentPath();	// ���ҽ� ���� ������ ��� ��ȯ
	const wchar_t* GetRelativeContentPath();	// ���ҽ� ���� ������ ��� ��� ��ȯ
};

