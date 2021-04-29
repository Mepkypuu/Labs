// --- ������������ ���������� ����
#include <windows.h>

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW (WS_POPUP|WS_BORDER|WS_SYSMENU)


// --- �������� ������� �������� ����
LRESULT CALLBACK main_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK popup_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK child_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst; 		                   // ���������� ���������� ����������

// --- ���������� ����������
char ClassNameMain[] = "MainWindows";      // �������� ������ ����
char ClassNameChild[] = "ChildWindows";
char ClassNamePopup[] = "PopupWindows";

char AppTitleMain[] = "OVERLAPPEDWINDOW";  // ��������� �������� ����
char AppTitlePopup[] = "POPUPWINDOW";
char AppTitleChild[] = "CHILDWINDOW";


// --- ������� WinMain
int WINAPI WinMain(
	HINSTANCE hInstance,     // ���������� ���������� ����������
	HINSTANCE hPrevInstance, // � Win32 ������ ����� NULL
	LPSTR lpCmdLine,
	// ��������� �� ��������� ������. ��
	// ���������
	// ���������� �������� ������ �� ��������� ������.
	int nCmdShow
	// ����������, ��� ���������� ������������� 
	// ������������ �� �������: ������������
	// (nCmdShow = SW_SHOWMINNOACTIVE) 
	// ��� � ���� ��������� ����
	// (nCmdShow = SW_SHOWNORMAL).
)
{
	WNDCLASS wcMain; // ��������� ��� ���������� � ������ ����
	WNDCLASS wcPopup, wcChild;

	HWND hWndMain;   // ���������� �������� ���� ����������
	HWND hWndPopup, hWndPopup2, hWndChild;
	//HWND hWndChild2; //

	MSG msg; // ��������� ��� �������� ���������

	// ��������� ���������� ���������� ���������� � ����������
	// ����������, ����� ��� ������������� ��������������� �� �
	// ������� ����.
	hInst = hInstance;

	// --- ���������, ���� �� ���������� �������� �����.
	// ������������� �������� FindWindow, ������� ���������
	// ����� ���� �������� 
	// ������ �� ����� ������ ��� �� ��������� ����:
	// HWND FindWindow(LPCTSTR lpClassName,
	// LPCTSTRlpWindowName);
	// ����� �������� lpClassName ���������� ��������� ��
	// ��������� ������, � ������� ���������� �������� ���
	// ������ �������� ����. �� ���� ������ � ���� �� ������ 
	// ����� ������� ��������� ����. ���� ���������� ����� 
	// ���� � �������� ����������, �� ��� ��������� �������
	// �������� ����� �������� lpWindowName. ���� �� �������� 
	// ����� ����, �� �������� lpWindowName ����� �����
	// �������� NULL.
	if ((hWndMain = FindWindow(ClassNameMain, NULL)) != NULL)
	{
		// ������������ ����� �� �������, ����� ���������� ���
		// ��������, � ����� ���. ����� �� ��������� ����������, 
		// �� �������, ��� �� ������ �������� ��� ������� ����.
		// �������, ���� ���������� ���� �������� �����,
		// ������������� �������������� � ��������� �� ��������
		// ���� ��� ������� ����. ��� ������ ��, � ���� ������������
		// ������������.
		if (IsIconic(hWndMain)) ShowWindow(hWndMain, SW_RESTORE);
		SetForegroundWindow(hWndMain);

		// ������� ���������� ����� - ������ ����� �����
		// ������������.
		return FALSE;
	}

	// --- ���������� ����� �� ������� - ������� WinMain
	// ���������� � �������������. ���������� ���������
	// WNDCLASS ��� ����������� ������ ����.
	memset(&wcMain, 0, sizeof(wcMain));
	wcMain.lpszClassName = ClassNameMain;                     // ��� ������ ����
	wcMain.lpfnWndProc = (WNDPROC)main_WndProc;               // ����� ������� �������
	wcMain.style = CS_HREDRAW | CS_VREDRAW;                   // ����� ������
	wcMain.hInstance = hInstance;                             // ��������� ����������
	wcMain.hIcon = LoadIcon(NULL, IDI_APPLICATION);           // ����������� ��� ����
	wcMain.hCursor = LoadCursor(NULL, IDC_ARROW);             // ������ ���� ��� ����
	//wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ����� ��� ����
	wcMain.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));  // ����� ��� ����
	wcMain.lpszMenuName = NULL;                               // ������ ���� ����
	wcMain.cbClsExtra = 0;                                    // �������������� ������
	wcMain.cbWndExtra = 0;                                    // �������������� ������
	// P���������� ������ ����.
	RegisterClass(&wcMain);

	memset(&wcPopup, 0, sizeof(wcPopup));
	wcPopup.lpszClassName = ClassNamePopup;                   // ��� ������ ����
	wcPopup.lpfnWndProc = (WNDPROC)popup_WndProc;             // ����� ������� �������
	wcPopup.style = CS_HREDRAW | CS_VREDRAW;                  // ����� ������
	wcPopup.hInstance = hInstance;                            // ��������� ����������
	wcPopup.hIcon = LoadIcon(NULL, IDI_APPLICATION);          // ����������� ��� ����
	wcPopup.hCursor = LoadCursor(NULL, IDC_ARROW);            // ������ ���� ��� ����
	wcPopup.hbrBackground = CreateSolidBrush(RGB(0, 255, 255)); // ����� ��� ����
	wcPopup.lpszMenuName = NULL;                              // ������ ���� ����
	wcPopup.cbClsExtra = 0;                                   // �������������� ������
	wcPopup.cbWndExtra = 0;                                   // �������������� ������
	// P���������� ������ ����.
	RegisterClass(&wcPopup);

	memset(&wcChild, 0, sizeof(wcChild));
	wcChild.lpszClassName = ClassNameChild;                   // ��� ������ ����
	wcChild.lpfnWndProc = (WNDPROC)child_WndProc;             // ����� ������� �������
	wcChild.style = CS_HREDRAW | CS_VREDRAW;                  // ����� ������
	wcChild.hInstance = hInstance;                            // ��������� ����������
	wcChild.hIcon = LoadIcon(NULL, IDI_APPLICATION);          // ����������� ��� ����
	wcChild.hCursor = LoadCursor(NULL, IDC_ARROW);            // ������ ���� ��� ����
	wcChild.hbrBackground = CreateSolidBrush(RGB(0145, 123, 200)); // ����� ��� ����
	wcChild.lpszMenuName = NULL;                              // ������ ���� ����
	wcChild.cbClsExtra = 0;                                   // �������������� ������
	wcChild.cbWndExtra = 0;                                   // �������������� ������
	// P���������� ������ ����.
	RegisterClass(&wcChild);
	//WS_OVERLAPPEDWINDOW^WS_MINIMIZEBOX^WS_MAXIMIZEBOX

	// �������� �������� ���������������� ����
	hWndMain = CreateWindow(
		ClassNameMain,              // ��� ������ ����
		AppTitleMain,               // ��������� ����
		WS_OVERLAPPEDWINDOW,        // ����� ����
		0,                          // X-����������
		0,                          // Y-����������
		1280,                       // ������ ����
		600,                        // ������ ����
		NULL,                       // ���������� ����-��������
		NULL,                       // ���������� ���� ����
		hInstance,                  // ���������� ���������� ����������
		NULL);                      // �������������� ����������
	if (!hWndMain)
	{
		// ���� �� �������, ������ ��������������.
		MessageBox(NULL, "Create: error", AppTitleMain, MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	// ���������� ����.
	ShowWindow(hWndMain, nCmdShow);

	// ��������� ���������� ���������� ������� ����.
	UpdateWindow(hWndMain);

	// �������� ���������� ����
	hWndPopup = CreateWindow(
		ClassNamePopup,                                // ��� ������ ����
		AppTitlePopup,                                 // ��������� ����
		WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | WS_VISIBLE,                   // ����� ����
		900,                                           // X-����������
		40,                                            // Y-����������
		350,                                           // ������ ����
		220,                                           // ������ ����
		hWndMain,                                      // ���������� ����-��������
		NULL,                                          // ���������� ���� ����
		hInstance,                                     // ���������� ���������� ����������
		NULL                                           // �������������� ����������
	);
	if (!hWndPopup)
	{
		DestroyWindow(hWndMain);
		return FALSE;
	}

	// ���������� ����.
	ShowWindow(hWndPopup, nCmdShow);

	// ��������� ���������� ���������� ������� ����.
	UpdateWindow(hWndPopup);

	// �������� ���������� ����
	hWndPopup2 = CreateWindow(
		ClassNamePopup,                                // ��� ������ ����
		AppTitlePopup,                                 // ��������� ����
		WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | WS_VISIBLE,                   // ����� ����
		500,                                           // X-����������
		40,                                            // Y-����������
		350,                                           // ������ ����
		220,                                           // ������ ����
		NULL,                                          // ���������� ����-��������
		NULL,                                          // ���������� ���� ����
		hInstance,                                     // ���������� ���������� ����������
		NULL                                           // �������������� ����������
	);
	if (!hWndPopup2)
	{
		DestroyWindow(hWndMain);
		return FALSE;
	}

	// ���������� ����.
	ShowWindow(hWndPopup2, nCmdShow);

	// ��������� ���������� ���������� ������� ����.
	UpdateWindow(hWndPopup2);

	// �������� ��������� ����
	hWndChild = CreateWindow(
		ClassNameChild,                                // ��� ������ ����
		AppTitleChild,                                 // ��������� ���� 
		WS_CHILDWINDOW | WS_CAPTION | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | CS_HREDRAW | CS_VREDRAW,      // ����� ����  
		50,                                            // X-����������
		200,                                           // Y-����������
		400,                                           // ������ ����
		300,                                           // ������ ����
		hWndMain,                                      // ���������� ����-��������
		NULL,                                          // ���������� ���� ����
		hInstance,                                     // ���������� ���������� ����������
		NULL);                                         // �������������� ����������

	if (!hWndChild)
	{
		DestroyWindow(hWndMain);
		DestroyWindow(hWndPopup);
		return FALSE;
	}

	// ���������� ����.
	ShowWindow(hWndChild, nCmdShow);

	// ��������� ���������� ���������� ������� ����.
	UpdateWindow(hWndChild);

	// ��������� ���� ��������� ������� ���������.
	// ������� GetMessage �������� ��������� �� �������, 
	// ������ false ��� ������� �� ������� ��������� WM_QUIT
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// �������������� ��������� ���������, 
		// ���������� � ������� ����������
		TranslateMessage(&msg);
		// ���������� ��������� ������� ���������
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// --- ������� ����
LRESULT CALLBACK main_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char x[10] = "", y[10] = "";

	switch (msg)
	{
		// ���������� �������� ���������� ���������� ������� ����.
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // ��������� ��������� ����������� ���� hWnd
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		_itoa_s(screenWidth, x, sizeof(x));
		_itoa_s(screenHeight, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 20, "������ ������", 14);
		TextOut(hDC, 20, 40, "������ ������", 14);
		TextOut(hDC, 140, 20, x, strlen(x));
		TextOut(hDC, 140, 40, y, strlen(y));

		RECT r;                  // ������� ������� ����
		GetClientRect(hWnd, &r);
		GetWindowRect(hWnd, &r); // �������� ������� ����

		int xLeft = r.left;
		int yLeft = r.top;

		_itoa_s(xLeft, x, sizeof(x));
		_itoa_s(yLeft, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 60, "���������� X �������� ������ ����", 34);
		TextOut(hDC, 20, 80, "���������� Y �������� ������ ����", 34);
		TextOut(hDC, 300, 60, x, strlen(x));
		TextOut(hDC, 300, 80, y, strlen(y));

		int xRight = r.right;
		int yRight = r.bottom;

		_itoa_s(xRight, x, 10);
		_itoa_s(yRight, y, 10);

		// ���������� �����
		TextOut(hDC, 20, 100, "���������� X ������� ������� ����", 34);
		TextOut(hDC, 20, 120, "���������� Y ������� ������� ����", 34);
		TextOut(hDC, 300, 100, x, strlen(x));
		TextOut(hDC, 300, 120, y, strlen(y));

		int xWin = r.right - r.left;
		int yWin = r.bottom - r.top;

		_itoa_s(xWin, x, 10);
		_itoa_s(yWin, y, 10);

		// ���������� �����
		TextOut(hDC, 20, 140, "������ ����", 12);
		TextOut(hDC, 20, 160, "������ ����", 12);
		TextOut(hDC, 300, 140, x, strlen(x));
		TextOut(hDC, 300, 160, y, strlen(y));

		EndPaint(hWnd, &ps); // ���������� �������� ����
	}; break;

	// ������������ ������ ����.
	case WM_DESTROY:
	{
		// ���� ������ ������� �������� ������� ��������
		// �������� ����, �� ������� � ������� ���������
		// ���������� ������� ��������� WM_QUIT
		PostQuitMessage(0);
	}; break;

	case WM_SIZE:
	{
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}; break;

	case WM_MOVE:
	{
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}; break;

	// �������������� ��������� �������� � �����������
	// ������� ��������� ��������� �� ���������.
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0l;
}

// --- ������� ����
LRESULT CALLBACK child_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char x[10] = "", y[10] = "";

	switch (msg)
	{
		// ���������� �������� ���������� ���������� ������� ����.
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // ��������� ��������� ����������� ���� hWnd
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		_itoa_s(screenWidth, x, sizeof(x));
		_itoa_s(screenHeight, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 20, "������ ������", 14);
		TextOut(hDC, 20, 40, "������ ������", 14);
		TextOut(hDC, 140, 20, x, strlen(x));
		TextOut(hDC, 140, 40, y, strlen(y));

		RECT r;                  // ������� ������� ����
		GetClientRect(hWnd, &r);
		GetWindowRect(hWnd, &r); // ���������� ������� ����

		int xLeft = r.left;
		int yLeft = r.top;

		_itoa_s(xLeft, x, sizeof(x));
		_itoa_s(yLeft, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 60, "���������� X �������� ������ ����", 34);
		TextOut(hDC, 20, 80, "���������� Y �������� ������ ����", 34);
		TextOut(hDC, 300, 60, x, strlen(x));
		TextOut(hDC, 300, 80, y, strlen(y));

		int xRight = r.right;
		int yRight = r.bottom;

		_itoa_s(xRight, x, sizeof(x));
		_itoa_s(yRight, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 100, "���������� X ������� ������� ����", 34);
		TextOut(hDC, 20, 120, "���������� Y ������� ������� ����", 34);
		TextOut(hDC, 300, 100, x, strlen(x));
		TextOut(hDC, 300, 120, y, strlen(y));

		int xWin = r.right - r.left;
		int yWin = r.bottom - r.top;

		_itoa_s(xWin, x, sizeof(x));
		_itoa_s(yWin, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 140, "������ ����", 12);
		TextOut(hDC, 20, 160, "������ ����", 12);
		TextOut(hDC, 300, 140, x, strlen(x));
		TextOut(hDC, 300, 160, y, strlen(y));

		EndPaint(hWnd, &ps); // ���������� �������� ����
	}; break;

	// ������������ ������ ����.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}; break;

	case WM_MOVE:
	{
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}; break;

	// �������������� ��������� �������� � �����������
	// ������� ��������� ��������� �� ���������.
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0l;
}

// --- ������� ����
LRESULT CALLBACK popup_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char x[10] = "", y[10] = "";

	switch (msg)
	{
		// ���������� �������� ���������� ���������� ������� ����.
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // ��������� ��������� ����������� ���� hWnd
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		_itoa_s(screenWidth, x, sizeof(x));
		_itoa_s(screenHeight, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 20, "������ ������", 14);
		TextOut(hDC, 20, 40, "������ ������", 14);
		TextOut(hDC, 140, 20, x, strlen(x));
		TextOut(hDC, 140, 40, y, strlen(y));

		RECT r;                  // ������� ������� ����
		GetClientRect(hWnd, &r);
		GetWindowRect(hWnd, &r); // �������� ������� ����

		int xLeft = r.left;
		int yLeft = r.top;

		_itoa_s(xLeft, x, sizeof(x));
		_itoa_s(yLeft, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 60, "���������� X �������� ������ ����", 34);
		TextOut(hDC, 20, 80, "���������� Y �������� ������ ����", 34);
		TextOut(hDC, 300, 60, x, strlen(x));
		TextOut(hDC, 300, 80, y, strlen(y));

		int xRight = r.right;
		int yRight = r.bottom;

		_itoa_s(xRight, x, sizeof(x));
		_itoa_s(yRight, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 100, "���������� X ������� ������� ����", 34);
		TextOut(hDC, 20, 120, "���������� Y ������� ������� ����", 34);
		TextOut(hDC, 300, 100, x, strlen(x));
		TextOut(hDC, 300, 120, y, strlen(y));

		int xWin = r.right - r.left;
		int yWin = r.bottom - r.top;

		_itoa_s(xWin, x, sizeof(x));
		_itoa_s(yWin, y, sizeof(y));

		// ���������� �����
		TextOut(hDC, 20, 140, "������ ����", 12);
		TextOut(hDC, 20, 160, "������ ����", 12);
		TextOut(hDC, 300, 140, x, strlen(x));
		TextOut(hDC, 300, 160, y, strlen(y));

		EndPaint(hWnd, &ps); // ���������� �������� ����
	}; break;

	// ������������ ������ ����.
	case WM_DESTROY:
	{
		DestroyWindow(hWnd);
		//PostQuitMessage(0);
	}; break;

	case WM_MOVE:
	{
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}; break;

	// �������������� ��������� �������� � �����������
	// ������� ��������� ��������� �� ���������.
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0l;
}
