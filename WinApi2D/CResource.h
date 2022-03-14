#pragma once
class CResource
{
private:
	wstring m_strKey;
	wstring m_strRelativePath;

public:
	CResource();
	virtual ~CResource();

	void SetKey(const wstring& strKey);
	void SetRelativePath(const wstring& strPath);

	const wstring& GetKey();
	const wstring& GetRelativePath();
};

