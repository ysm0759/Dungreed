#pragma once
class CTexture;
class CSound;
class CD2DImage;

class CResourceManager
{
	SINGLETON(CResourceManager);

private:
	map<wstring, CTexture*> m_mapTex;		// Texture ���ҽ��� ���� �ڷᱸ��
	map<wstring, CSound*> m_mapSound;		// Sound ���ҽ��� ���� �ڷᱸ��
	CSound* m_pBGM;							// BGM ���ҽ��� ���� ����

	map<wstring, CD2DImage*> m_mapD2DImg;	// D2D Image ���ҽ��� ���� �ڷᱸ��

public:
	CTexture* FindTexture(const wstring& strKey);	// ����� Texture Ž��
	CTexture* LoadTextrue(const wstring& strKey, const wstring& strRelativePath);	// Texture �ҷ����� �̹� �ִ� ��� �ִ� Texture ��ȯ
	CTexture* CreateTexture(const wstring& strKey, UINT width, UINT height);

	CSound* FindSound(const wstring& strKey);		// ����� Sound Ž��
	CSound* LoadSound(const wstring& strKey, const wstring& strRelativePath);	// Sound �ҷ����� �̹� �ִ� ��� �ִ� Sound ��ȯ

	CSound* LoadBGM(const wstring& strKey, const wstring& strRelativePath);		// BGM �ҷ����� �̹� �ִ� ��� �ִ� BGM ��ȯ

	CD2DImage* FindD2DImage(const wstring& strKey);
	CD2DImage* LoadD2DImage(const wstring& strKey, const wstring& strRelativePath);	// D2DImage �ҷ����� �̹� �ִ� ��� �ִ� D2DImage ��ȯ
};

