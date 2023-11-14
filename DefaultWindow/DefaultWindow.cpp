// DefaultWindow.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "DefaultWindow.h"
#include "MainGame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND	g_hWnd;

// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);	// 창 스타일을 지정하는 함수
BOOL                InitInstance(HINSTANCE, int);			// 창을 생성하는 명령어를 호출하는 함수
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);	// 윈도우에서 발생한 메세지를 처리하는 함수
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);		// 창의 정보를 띄워주는 메세지 박스 함수

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,				// 메모리에 할당되는 실체, 현재 프로그램의 고유 식별 번호를 저장
                     _In_opt_ HINSTANCE hPrevInstance,		// 전에 실행되었던 인스턴스의 핸들이 넘어옴, 없을 경우 기본값 null로 채워짐(호환성을 위해 존재)
                     _In_ LPWSTR    lpCmdLine,				// 지원되는 문자 체계(L"")
                     _In_ int       nCmdShow)				// 실행한 창의 스타일(모양/ 최소화, 최대화 모양 변경 등)의 옵션 값이 전달됨
{
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);





	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);		
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULTWINDOW, szWindowClass, MAX_LOADSTRING);
   
	MyRegisterClass(hInstance);

    // 응용 프로그램 초기화를 수행합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEFAULTWINDOW));
	
    MSG msg;
	msg.message = WM_NULL;

	CMainGame		MainGame;

	MainGame.Initialize();

	DWORD	dwTime = GetTickCount();			// 990

	while (true)
	{
		// PM_REMOVE	: 메시지를 읽어옴과 동시에 메시지 큐에서 제거
		// PM_NOREMOVE : 메시지 큐에 메시지가 있는지 여부만 파악, 메시지를 얻어오려면 GetMessage를 다시 호출해야 한다.

		// PeekMessage는 윈도우 메세지가 큐에 없을 경우 자동 0을 리턴한다.
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;

			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}

		else
		{	//	1000			1001
			if (dwTime + 10 < GetTickCount())
			{
				MainGame.Update();
				MainGame.Late_Update();
				MainGame.Render();

				//1003
				dwTime = GetTickCount();
			}			

			/*MainGame.Update();
			MainGame.Late_Update();
			MainGame.Render();*/
		}		
	}
	
    // 기본 메시지 루프입니다.
   /* while (GetMessage(&msg, nullptr, 0, 0))
    {
		// TranslateAccelerator : 메뉴 기능의 단축키가 제대로 작동하도록 검사하는 함수
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
			// TranslateMessage : 키보드 메세지를 가공하여 프로그램에서 쉽게 사용할 수 있도록 해주는 함수, 
			// GetMessage 함수가 읽어온 키보드 메세지를 가공하는 역할

            TranslateMessage(&msg);

			// 시스템 메세지 큐에서 꺼낸 메세지를 WndProc함수에게 전달
            DispatchMessage(&msg);
        }
    }*/


	GdiplusShutdown(gdiplusToken);

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;			// 윈도우 창을 만들 때 사용되는 구조체

    wcex.cbSize = sizeof(WNDCLASSEX);		 // 자기 자신의 사이즈를 저장해 놓음

    wcex.style          = CS_HREDRAW | CS_VREDRAW;	// 윈도우 스타일을 정의, 창 초기화 값을 의미, 윈도우의 수직 또는 수평의 크기가 변할 경우 다시 그린다는 의미 

	//CS_HREDRAW : 가로를 다시 그린다.
	//CS_VREDRAW : 세로를 다시 그린다.

    wcex.lpfnWndProc    = WndProc;	// 메세지를 처리할 함수의 이름
    wcex.cbClsExtra     = 0;		// 윈도우가 특수한 목적으로 사용하는 여분의 공간
    wcex.cbWndExtra     = 0;		// 일종의 예약 영역이며 사용하지 않은 경우 0

    wcex.hInstance      = hInstance;	// 윈도우 클래스를 사용하는 프로그램의 번호 설정
	
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULTWINDOW));
	// 윈도우가 사용할 아이콘 지정(시작 표시줄)

    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	// 윈도우에서 사용할 마우스 커서를 지정

    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	// 윈도우 작업 영역의 배경 색을 설정
	
	wcex.lpszMenuName = NULL;
	// 윈도우 상단에 있는 메뉴 설정

    wcex.lpszClassName  = szWindowClass;
	// 실행 파일의 이름을 저장 (가급적이면 프로젝트 이름과 일치시킴)

    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	// 윈도우 창 상단에 있는 작은 아이콘 모양을 지정

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   RECT	rcWindow{ 0, 0, WINCX, WINCY };

   // CreateWindowW : 등록해 놓은 정보들을 토대로 윈도우를 만드는 작업을 실행

   // rcWindow = rcWindow + 기본 창 스타일 + 메뉴 바의 크기 고려 여부

   AdjustWindowRect(&rcWindow, WS_OVERLAPPEDWINDOW, FALSE);

   HWND hWnd = CreateWindowW(szWindowClass,  // 앞서 정의한 윈도우 클래스에 전달한 클래스 이름을 그대로 넣어줌
						   szTitle,			// 윈도우 상단에 나타낼 문자열
						   WS_OVERLAPPEDWINDOW,	// 만들고자 하는 윈도우 스타일 지정(WS_OVERLAPPEDWINDOW : 우리가 흔히 보는 창 스타일)
						   CW_USEDEFAULT, 0,  // 출력할 창의 left, top 좌표
						   rcWindow.right - rcWindow.left,
						   rcWindow.bottom - rcWindow.top,  // 출력할 창의 가로, 세로 길이
						   nullptr,		// 부모 윈도우가 있다면 부모 윈도우 핸들을 지정	
						   nullptr,	 // 윈도우에서 사용할 메뉴의 핸들 지정	
						   hInstance,// 윈도우를 만드는 주체, 프로그램 핸들 지정 
						   nullptr); // 운영체제가 특수한 목적으로 사용함	

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// 윈도우 구성 라이브러리

// 1. KERNEL : 메모리를 관리하고 프로그램을 실행
// 2. USER : 유저 인터페이스와 윈도우를 관리
// 3. GDI : 화면 처리와 그래픽 담당

// 라이브러리 : 바이너리로 번역(컴파일)된 함수들을 모아놓은 파일

// 코드 재사용을 위한 초창기 방법 중 하나이며, 다른 프로그램에서 사용할 수 있도록 운영체제나 소프트웨어 개발자레 의해 제공
// 라이브러리의 대다수 함수들은 함수의 정의 및 선언들을 필요로 하기 때문에 링크되기 전 전처리기에 의해 해당 헤더 파일을 프로그램의 반드시 포함시켜야 함
// 라이브러리들은 사용자의 프로그램과 링크되어 실행이 가능한 완전한 프로그램을 이루게 됨.

//RECT	rc{ 100, 100, 200, 200 };
//list<RECT>	BulletList;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
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

	// DC : 출력에 관한 정보를 갖고 있는 데이터 구조체
	// GDI가 어떤 포인트(점)인지 선의 색상, 굵기, 면의 무늬 등등을 관리한다.

	case WM_PAINT:		// 그리기 메세지 처리 구문
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);

		/*Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);	

		for (auto& iter : BulletList)
		{
			Ellipse(hdc, iter.left, iter.top, iter.right, iter.bottom);

			iter.top	-= 10;
			iter.bottom -= 10;

		}*/

		EndPaint(hWnd, &ps);
	}
	break;

	//case WM_CREATE:

	//	SetTimer(hWnd, 0, 0, 0);
	//	// 1인자 : 윈도우 핸들
	//	// 2인자 : 타이머의 id값, 생성한 타이머의 고유 정수 값
	//	// 3인자 : 타이머 주기(0일 경우 1000당 1초)
	//	// 4인자 : NULL(0)인 경우 주기대로 WM_TIMER 메세지를 발생시킴
	//	break;

	//case WM_TIMER:

	//	InvalidateRect(hWnd, 0, TRUE);	// 윈도우 그리기 갱신(WM_PAINT 메세지가 발생)
	//	// 1인자 : 윈도우 핸들
	//	// 2인자 : 윈도우 갱신 범위(0 또는 null인경우 윈도우 전체 영역을 의미)
	//	// 3인자 : true인 경우 그려져 있는 않는 부분도 갱신, false인 경우 새로 그리는 부분만 갱신
	//	
	//	break;


	case WM_KEYDOWN:

		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;

		/*case VK_RIGHT:
			rc.left		+= 10;
			rc.right	+= 10;
			break;

		case VK_LEFT:
			rc.left		-= 10;
			rc.right	-= 10;
			break;

		case VK_UP:
			rc.top		-= 10;
			rc.bottom   -= 10;
			break;

		case VK_DOWN:
			rc.top		+= 10;
			rc.bottom	+= 10;
			break;

		case VK_SPACE:

			BulletList.push_back(rc);

			break;*/
		}

		break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

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


// 함수 호출 규약 : 함수의 실행이 종료되면 할당 되었던 스택 메모리를 해제해야 하는데 함수를 호출한 호출원(caller)에서 정리할 것인지, 호출 받은 피호출자(callee)에서 할지에 대한 약속, 또는 규약

// __cdecl : c / c++언어의 기본 호출 규약, 호출원이 스택 메모리를 정리, 정작 자기 자신의 매개 변수가 어떤 값이 얼마나 들어올지 모른다(가변 인자 함수), 함수 본인 스스로 스택 메모리 정리를 못함

// __stdcall : WIN32 api 기본 호출 규약, 피 호출자가 스택 메모리를 정리, api에서 제공하는 대부분의 함수들은 '고정 인자 함수'이다. 매개 변수가 어떤 것이 들어올 지 이미 고정되어 있기 때문에 피호출자가 메모리의 크기를 계산 할 수 있어 스스로 스택 메모리를 정리 할 수 있다.

// __fastcall : 함수 호출을 빠르게 처리하기 위한 호출 규약, ecx와 edx라는 레지스터를 통해 저장되어 함수 호출이 빨라지는 근거가 된다. 피 호출자가 스택 메모리를 정리

// __thiscall : 함수 매개 변수로 this포인터를 넘겨 받을 때 사용하는 호출 규약, 피 호출자가 스택 메모리를 정리