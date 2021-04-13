// --- ������������ ���������� ����
#include <windows.h>
#include <cmath>

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW      (WS_POPUP|WS_BORDER|WS_SYSMENU)

// --- �������� ������� �������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// --- ���������� ����������
HINSTANCE hInst; 		                 // ���������� ���������� ����������
char ClassName[] = "WindowLab"; 		 // �������� ������ ����
char AppTitle[] = "Application Win32";   // ��������� �������� ����

struct UZOR
{
	unsigned C1, A3, A4, B3, B4; // ������������ 
	int x, y;                    // ���������� ���. ����. ���� ����������� 
	unsigned w, h;               // ������ � ������ ������� (������)
	COLORREF color;              // ���� ����� (���� �����������)
};

void uzor(HDC hDC, struct UZOR uzr) // ������� ������ �����
{
	int dx = uzr.w / 2, dy = uzr.h / 2, ddx = dx / 4, ddy = dy / 4, x1, x2, y1, y2;
	double D, T = 5;
	COLORREF grey = RGB(127, 127, 127); // ����� ���� ���������� � ������ �����������.
	int step = 1;

	// �������� �������� GDI (������� CreatePen)
	HPEN uzrPen = CreatePen(PS_SOLID, 3, uzr.color); // �������� ��������� ���� ����� uzr.color �������� 3 �������
	HPEN greyPen = CreatePen(PS_SOLID, 3, grey);     // �������� ��������� ���� ����� grey �������� 3 �������
	HPEN prevPen;

	for (double t = 0; t < T; t += 0.01) // ������ ��������� �������� ����� t ( 0<=T<5)
	{
		// ��������� ��������� ��������� ����������� (������� SelectObject)
		if (step)
		{
			prevPen = (HPEN)SelectObject(hDC, uzrPen); // ��������� ���� ����� ����������� � �������� hDC
			// � ���������� "�������" ����
		}
		else
		{
			prevPen = (HPEN)SelectObject(hDC, greyPen); // ��������� ���� ������ ����� � �������� hDC
			// � ���������� "�������" ����
		}

		step = !step;

		// ����������� ��������� ������ � ����� ��������� ����� �����
		D = t + uzr.C1;
		x1 = (int)((2 * cos(uzr.A4 * t) + 2 * cos(uzr.A3 * 2 * t)) * ddx);
		y1 = (int)((2 * cos(uzr.B4 * t) + 2 * cos(uzr.B3 * 2 * t)) * ddy);
		x2 = (int)((2 * cos(uzr.A4 * D) + 2 * cos(uzr.A3 * 2 * D)) * ddx);
		y2 = (int)((2 * cos(uzr.B4 * D) + 2 * cos(uzr.B3 * 2 * D)) * ddy);
		x1 = uzr.x + (x1 + dx); y1 = uzr.y + (y1 + dy);
		x2 = uzr.x + (x2 + dx); y2 = uzr.y + (y2 + dy);

		// ����� ��������� ����� �� (x1,y1) �� (x2,y2)
		// (������� MoveToEx � LineTo)
		MoveToEx(hDC, x1, y1, NULL); // ����������� ������� ������� ���� � ����� � ������������(x1, y1)
		LineTo(hDC, x2, y2);         // �������� ����� �� ������� ������� ���� �� �����(x2, y2)

		// �������������� ��������� ��������� �����������
		SelectObject(hDC, prevPen); // ��������� "�������" ���� � �������� hDC
	}

	// �������� ��������� �������� GDI
	DeleteObject(uzrPen); DeleteObject(greyPen); // �������� ���� ��������� ������
}

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
	WNDCLASS wc; // ��������� ��� ���������� � ������ ����
	HWND hWnd;   // ���������� �������� ���� ����������
	MSG msg;     // ��������� ��� �������� ���������

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
	if ((hWnd = FindWindow(ClassName, NULL)) != NULL)
	{
		// ������������ ����� �� �������, ����� ���������� ���
		// ��������, � ����� ���. ����� �� ��������� ����������, 
		// �� �������, ��� �� ������ �������� ��� ������� ����.
		// �������, ���� ���������� ���� �������� �����,
		// ������������� �������������� � ��������� �� ��������
		// ���� ��� ������� ����. ��� ������ ��, � ���� ������������
		// ������������.
		if (IsIconic(hWnd)) ShowWindow(hWnd, SW_RESTORE);
		SetForegroundWindow(hWnd);

		// ������� ���������� ����� - ������ ����� �����
		// ������������.
		return FALSE;
	}

	// --- ���������� ����� �� ������� - ������� WinMain
	// ���������� � �������������. ���������� ���������
	// WNDCLASS ��� ����������� ������ ����.
	memset(&wc, 0, sizeof(wc));
	wc.lpszClassName = ClassName;                                 // ��� ������ ����
	wc.lpfnWndProc = (WNDPROC)WndProc;                            // ����� ������� �������
	wc.style = CS_HREDRAW | CS_VREDRAW;                           // ����� ������
	wc.hInstance = hInstance;                                     // ��������� ����������
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);                   // ����������� ��� ����
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);                     // ������ ���� ��� ����
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);       // ����� ��� ����
	wc.lpszMenuName = NULL;                                       // ������ ���� ����
	wc.cbClsExtra = 0;                                            // �������������� ������
	wc.cbWndExtra = 0;                                            // �������������� ������
	// P���������� ������ ����.
	RegisterClass(&wc);

	// �������� �������� ���������������� ����
	hWnd = CreateWindow(
		ClassName,                  // ��� ������ ����
		AppTitle,                   // ��������� ����
		WS_OVERLAPPEDWINDOW,        // ����� ����
		0,                          // X-����������
		0,                          // Y-����������
		1280,                       // ������ ����
		600,                        // ������ ����
		NULL,                       // ���������� ����-��������
		NULL,                       // ���������� ���� ����
		hInstance,                  // ���������� ���������� ����������
		NULL);                      // �������������� ����������
	if (!hWnd)
	{
		// ���� �� �������, ������ ��������������.
		MessageBox(NULL, "Create: error", AppTitle, MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	// ���������� ����.
	ShowWindow(hWnd, nCmdShow);

	// ��������� ���������� ���������� ������� ����.
	UpdateWindow(hWnd);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static struct UZOR uzr;

	switch (msg)
	{
		// ���������� �������� ���������� ���������� ������� ����.
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // ��������� ��������� ����������� ���� hWnd
		RECT r;
		GetClientRect(hWnd, &r);
		int width = r.right - r.left;
		int height = r.bottom - r.top;
		uzr.A4 = rand() % (5 + 1);
		uzr.A3 = rand() % (5 + 1);
		uzr.B4 = rand() % (5 + 1);
		uzr.B3 = rand() % (5 + 1);
		uzr.C1 = rand() % (5 + 1);
		uzr.w = 20 + rand() % ((width - 20 + 1) - 20);
		uzr.h = 20 + rand() % ((height - r.top - 20 + 1) - 20);
		uzr.x = rand() % (width - uzr.w + 1);
		uzr.y = rand() % (height - uzr.h + 1);
		uzr.color = RGB(rand() % 255, rand() % 255, rand() % 255);
		uzor(hDC, uzr);
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
