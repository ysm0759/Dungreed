// WinApi2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinApi2D.h"
#include "locale.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND hWnd;                                      // 윈도우의 핸들
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// _In_ : SAL 주석 - 자주 사용되는 주석을 매번 적기보다 키워드로 작성함.
// hInstance : 실행된 프로세스의 시작 주소. 인스턴스 핸들
// hPrevIsntance : 이전에 실행된 인스턴스 핸들
// lpCmdLine : 명령으로 입렵된 프로그램의 인수
// nCmdShow : 프로그램이 시작될 형태

// 윈도우 메인의 역할
// 1. 윈도우창 세팅 후 화면에 띄우고
// 2. 메세지 루프
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    setlocale(LC_ALL, "Korean");
    // 메모리 누수 체크
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(219);

    // 사용되지 않은 매개변수 정의
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 리소스 뷰의 String table 용도
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 단축키 정보
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2D));

    // 기본 메시지 루프입니다:
    // 메세지 큐에서 메세지가 확인될 때까지 대기
    // 메세지 큐에 msg.message == WM_QUIT 인 경우 false를 반환

    // GetMessage : 메시지 큐에 메시지가 없으면 대기, 메시지가 들어왔다면 true 반환, WM_QUIT 메시지가 있으면 false 반환
    // PeekMessage : 메시지 큐에 메시지가 없다면 false 반환, 메시지가 있다면 true 반환

    // 게임 루프
    // 이전 GetMessage의 대기 상태 유지에서
    // 현재 PeekMessage의 메시지가 없는 99.99% 상황에서 게임 상황을 처리

    // Core 초기화
    CCore::getInst()->init();

    MSG msg;
    while (TRUE)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))    // 메시지 없으면 게임처리, 메시지 있으면 메시지처리
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키에 대한 처리
            {
                TranslateMessage(&msg);     // 키보드 입력메세지 처리를 담당
                DispatchMessage(&msg);      // WndProc에서 전달된 메세지를 실제 윈도우에 전달
            }
        }
        else
        {
            // 게임 처리
            CCore::getInst()->update();
            CCore::getInst()->render();
        }
        
    }

    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 윈도우 창의 정보를 저장하기 위한 구조체
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);   // 구조체의 크기 설정

    wcex.style          = CS_HREDRAW | CS_VREDRAW;  // 윈도우 클래스의 스타일 지정
    wcex.lpfnWndProc    = WndProc;                  // 메세지를 처리하는 함수를 지정(윈도우 프로시져)
    wcex.cbClsExtra     = 0;                        // 윈도우 클래스에서 사용하고자 하는 여분의 메모리양을 바이트 단위로 지정
    wcex.cbWndExtra     = 0;                        // cbClsExtra와 유사하나 개별 윈도우에서 사용하고자 하는 여분의 메모리양을 지정
    wcex.hInstance      = hInstance;                // 윈도우 클래스를 등록한 인스턴스의 핸들
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI2D));   // 프로그램 아이콘
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // 타이틀바 좌상단과 윈도우가 최소화 되었을 때 보여주는 아이콘을 지정
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);   // 커서 지정
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);         // 윈도우 작업영역에 칠한 배경 브러시
    wcex.lpszMenuName   = nullptr;                          // 윈도우에서 사용할 메뉴 지정, nullptr로 없앰
    wcex.lpszClassName  = szWindowClass;                    // 윈도우 클래스의 이름

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass,         // 클래스 이름
                            szTitle,                // 윈도우 타이틀 이름
                            WINSTYLE,               // 윈도우 스타일, 내부 뜯어서 보여주기
                            WINSTARTX,              // 윈도우 화면 X
                            WINSTARTY,              // 윈도우 화면 Y
                            WINSIZEX,               // 가로 크기
                            WINSIZEY,               // 세로 크기
                            nullptr,                // 부모 윈도우
                            nullptr,                // 메뉴 핸들
                            hInstance,              // 인스턴스 지정
                            nullptr);               // 추가 매개변수

    if (!hWnd)
    {
        return FALSE;
    }

   // 실제 윈도우 크기를 구하기 위해 AdjustWindowRect 사용
   RECT rc;
   rc.left = 0;
   rc.top = 0;
   rc.right = WINSIZEX;
   rc.bottom = WINSIZEY;

   // 실제 창이 크기에 맞게 나온다.
   AdjustWindowRect(&rc, WINSTYLE, false);
   //위 RECT정보로 윈도우 사이즈를 셋팅하자.
   SetWindowPos(hWnd, NULL, WINSTARTX, WINSTARTY, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

    return TRUE;
}

// WndProc : 메세지를 운영체제에 전달한다. 강제로 운영체제가 호출함.
// hWnd : 메세지가 어느 윈도우를 대상으로 전달되었는지 구분
// message : 메세지 구분 번호
// wParam : unsigned int 메세지의 매개변수 1
// lParam : unsigned long 메세지의 매개변수 2

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:      // 윈도우의 작업영역이 다시 그려져야 할 때 실행됨. (무효화 영역이 발생 했을 떄)
        {
            PAINTSTRUCT ps;
            // Device Context 만들어서 ID 를 반환
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:    // 윈도우가 종료될 떄 실행됨.
        PostQuitMessage(0);     // 메세지 큐에 WM_QUIT 입력
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}