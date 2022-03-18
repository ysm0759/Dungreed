#pragma once

//================================================
//## Logger	(visual studio 출력창에 정보 표시)	##
//================================================

#include <string>

class Logger
{

public:
	static void log(const wchar_t tag[], const wchar_t content[])
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		WCHAR str[30];
		swprintf_s(str, L"%d/%d/%d %02d:%02d:%02d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		OutputDebugStringW(str);
		OutputDebugStringW(L" ");
		OutputDebugStringW(tag);
		OutputDebugStringW(L" ");
		OutputDebugStringW(content);
		OutputDebugStringW(L"\n");
	}

	static void debug(const wchar_t content[])
	{
		log(L"[DEBUG]", content);
	}

	static void debug(wstring content)
	{
		log(L"[DEBUG]", content.c_str());
	}

	static void info(const wchar_t content[])
	{
		log(L"[ INFO]", content);
	}

	static void info(wstring content)
	{
		log(L"[ INFO]", content.c_str());
	}

	static void warning(const wchar_t content[])
	{
		log(L"[ WARN]", content);
	}

	static void warning(wstring content)
	{
		log(L"[ WARN]", content.c_str());
	}

	static void error(const wchar_t content[])
	{
		log(L"[ERROR]", content);
	}

	static void error(wstring content)
	{
		log(L"[ERROR]", content.c_str());
	}
};

//
//// Mouse 좌표 계산
//POINT ptPos = {};
//// GetCursorPos() 윈도우에서 모니터 좌상단 기준 마우스의 좌표를 반환
//GetCursorPos(&ptPos);
//// 모니터 좌상단 기준 마우스 좌표를 게임 윈도우 기준 마우스 위치로 계산
//ScreenToClient(hWnd, &ptPos);
//char charTmp[17];
//wchar_t tmp[17];
//wchar_t mouseInfo[255] = {};
//
//_gcvt_s(charTmp, sizeof(charTmp), ptPos.x, 8);
//mbstowcs_s(NULL, tmp, sizeof(tmp) / 2, charTmp, sizeof(charTmp));
//
//wcscat_s(mouseInfo, L"Mouse.X : ");
//wcscat_s(mouseInfo, tmp);
//wcscat_s(mouseInfo, L"\t");
//
//_gcvt_s(charTmp, sizeof(charTmp), ptPos.y, 8);
//mbstowcs_s(NULL, tmp, sizeof(tmp) / 2, charTmp, sizeof(charTmp));
//
//wcscat_s(mouseInfo, L"Mouse.Y : ");
//wcscat_s(mouseInfo, tmp);
//
//Logger::info(mouseInfo);


// 좌표 찾기용 
//char charTmp[17];
//wchar_t tmp[17];
//wchar_t objectInfo[255] = {};
//
//_gcvt_s(charTmp, sizeof(charTmp), m_fptCurLookAt.x, 8);
//mbstowcs_s(NULL, tmp, sizeof(tmp) / 2, charTmp, sizeof(charTmp));
//
//wcscat_s(objectInfo, L"Camera.X : ");
//wcscat_s(objectInfo, tmp);
//wcscat_s(objectInfo, L"\t");
//
//_gcvt_s(charTmp, sizeof(charTmp), m_fptCurLookAt.y, 8);
//mbstowcs_s(NULL, tmp, sizeof(tmp) / 2, charTmp, sizeof(charTmp));
//
//wcscat_s(objectInfo, L"Camera.Y : ");
//wcscat_s(objectInfo, tmp);
//
//Logger::info(objectInfo);