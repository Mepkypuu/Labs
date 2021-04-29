// --- ������������ ���������� ����
#include <windows.h>
#include "resource.h"

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW      (WS_POPUP|WS_BORDER|WS_SYSMENU)

// --- �������� ������� �������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// --- ���������� ����������
HINSTANCE hInst; 		                 // ���������� ���������� ����������
char ClassName[] = "WindowLab"; 		 // �������� ������ ����
char AppTitle[] = "Application Win32";   // ��������� �������� ����

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

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// ��������� ���� ��������� ������� ���������.
	// ������� GetMessage �������� ��������� �� �������, 
	// ������ false ��� ������� �� ������� ��������� WM_QUIT
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccel, &msg))
		{
			// �������������� ��������� ���������, 
			// ���������� � ������� ����������
			TranslateMessage(&msg);
			// ���������� ��������� ������� ���������
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

// --- ������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int counter = 0, interval = 1000;
	static char char_buffer[2] = "";
	static bool lbuttondown_flag = false, rbuttondown_flag = false;
	char counter_buffer[10] = "";

	switch (msg)
	{
	case WM_CREATE:
	{
		SetTimer(hWnd,             // ���������� ����
			1,                     // ������������� �������
			interval,              // ��������
			NULL);      // ������� ��������� ������
	}; break;

	case WM_TIMER:
	{
		counter++;
		lbuttondown_flag = rbuttondown_flag = false;
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}; break;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_UP:
		{
			interval *= 2;
			SetTimer(hWnd,             // ���������� ����
				1,                     // ������������� �������
				interval,              // ��������
				NULL);                 // ������� ��������� ������
		}; break;

		case VK_DOWN:
		{
			interval /= 2;
			SetTimer(hWnd,             // ���������� ����
				1,                     // ������������� �������
				interval,              // ��������
				NULL);                 // ������� ��������� ������
		};  break;

		default:
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		};  break;
		}
	}; break;

	case WM_CHAR:
	{
		char_buffer[0] = wParam;
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}; break;

	case WM_LBUTTONDOWN:
	{
		lbuttondown_flag = true;
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}; break;

	case WM_RBUTTONDOWN:
	{
		rbuttondown_flag = true;
		InvalidateRect(hWnd, NULL, TRUE);
		UpdateWindow(hWnd);
	}; break;

	case WM_MOUSEMOVE:
	{
		// ��������� ������ ����
		UINT fwKeys = wParam;
		// �������������� ������� �������
		int xPos = LOWORD(lParam);
		// ������������ ������� �������
		int yPos = HIWORD(lParam);

		if (fwKeys & MK_LBUTTON)
		{
			HDC hDC = GetDC(hWnd);
			SetPixel(hDC, xPos, yPos, 0l);
			ReleaseDC(hWnd, hDC);
		}
	}; break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_ACCELERATOR40001:
		{
			DestroyWindow(hWnd);
		}; break;

		default:
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}; break;
		}
	}; break;

	// ���������� �������� ���������� ���������� ������� ����.
	case WM_PAINT:
	{
		char temp_buffer[128] = "������� �������: ";

		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // ��������� ��������� ����������� ���� hWnd

		_itoa_s(counter, counter_buffer, sizeof(counter_buffer));
		strcat_s(temp_buffer, sizeof(temp_buffer), counter_buffer);

		// ���������� �����
		TextOut(hDC, 20, 20, temp_buffer, strlen(temp_buffer));

		strcpy_s(temp_buffer, sizeof(temp_buffer), "��������� ������� ������: ");
		strcat_s(temp_buffer, sizeof(temp_buffer), char_buffer);

		// ���������� �����
		TextOut(hDC, 20, 40, temp_buffer, strlen(temp_buffer));

		if (lbuttondown_flag)
		{
			// ���������� �����
			TextOut(hDC, 20, 60, "���� ������ ����� ������ ����", 30);
		}
		else if (rbuttondown_flag)
		{
			// ���������� �����
			TextOut(hDC, 20, 60, "���� ������ ������ ������ ����", 31);
		}

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
