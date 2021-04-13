// --- ������������ ���������� ����
#include <windows.h>
#include <cmath>
#include <string>

#include "resource.h"

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW      (WS_POPUP|WS_BORDER|WS_SYSMENU)

struct UZOR
{
	unsigned C1, A3, A4, B3, B4; // ������������ 
	int x, y;                    // ���������� ���. ����. ���� ����������� 
	unsigned w, h;               // ������ � ������ ������� (������)
	COLORREF color;              // ���� ����� (���� �����������)
};

// --- �������� ������� �������� ����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
UINT APIENTRY CCHookProc
(
	HWND hdlg,     // ���������� ���� ����� �������
	UINT uiMsg,    // ��� ���������
	WPARAM wParam, // �������� ���������
	LPARAM lParam  // �������� ���������
);

void uzor(HDC hDC, struct UZOR uzr); // ������� ������ �����

// --- ���������� ����������
HINSTANCE hInst;                       // ���������� ���������� ����������
char ClassName[] = "WindowLab";        // �������� ������ ����
char AppTitle[] = "Application Win32"; // ��������� �������� ����
HWND hWnd;                             // ���������� �������� ���� ����������

bool isInited = false;
struct UZOR uzr;
int dTimer = 10000;
int nTimer = 0;

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
	wc.lpszClassName = ClassName;                             // ��� ������ ����
	wc.lpfnWndProc = (WNDPROC)WndProc;                        // ����� ������� �������
	wc.style = CS_HREDRAW | CS_VREDRAW;                       // ����� ������
	wc.hInstance = hInstance;                                 // ��������� ����������
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);      // ����������� ��� ����
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);        // ������ ���� ��� ����
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // ����� ��� ����
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);             // ������ ���� ����
	wc.cbClsExtra = 0;                                        // �������������� ������
	wc.cbWndExtra = 0;                                        // �������������� ������
	// P���������� ������ ����.
	RegisterClass(&wc);

	// �������� �������� ���������������� ����
	hWnd = CreateWindow(
		ClassName,           // ��� ������ ����
		AppTitle,            // ��������� ����
		WS_OVERLAPPEDWINDOW, // ����� ����
		0,                   // X-����������
		0,                   // Y-����������
		1280,                // ������ ����
		600,                 // ������ ����
		NULL,                // ���������� ����-��������
		NULL,                // ���������� ���� ����
		hInstance,           // ���������� ���������� ����������
		NULL);               // �������������� ����������
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

	SetTimer(hWnd, nTimer, dTimer, NULL);

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
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_SETVALUE:
			switch(DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_CHARACTERISTIC), hWnd, DlgProc))
			{
			case IDOK:
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				KillTimer(hWnd, nTimer);
				SetTimer(hWnd, nTimer, dTimer, NULL);
				break;
			}
			break;
		}
		break;

	// ���������� �������� ���������� ���������� ������� ����.
	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps); // ��������� ��������� ����������� ���� hWnd

		if (!isInited)
		{
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
			isInited = true;
		}

		uzor(hDC, uzr);
		EndPaint(hWnd, &ps); // ���������� �������� ����
		break;

	// ������������ ������ ����.
	case WM_DESTROY:
		// ���� ������ ������� �������� ������� ��������
		// �������� ����, �� ������� � ������� ���������
		// ���������� ������� ��������� WM_QUIT
		PostQuitMessage(0);
		break;

	// �������������� ��������� �������� � �����������
	// ������� ��������� ��������� �� ���������.
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0l;
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDlg, IDC_EDIT_X_LABEL, "���������� X: ");
		SetDlgItemText(hDlg, IDC_EDIT_Y_LABEL, "���������� Y: ");
		SetDlgItemText(hDlg, IDC_EDIT_W_LABEL, "������: ");
		SetDlgItemText(hDlg, IDC_EDIT_H_LABEL, "������: ");
		SetDlgItemText(hDlg, IDC_EDIT_TIMER_LABEL, "�������� �������: ");
		SetDlgItemText(hDlg, IDC_EDIT_COLOR_LABEL, "RGB ����: ");

		SetDlgItemText(hDlg, IDC_EDIT_X, std::to_string(uzr.x).c_str());
		SetDlgItemText(hDlg, IDC_EDIT_Y, std::to_string(uzr.y).c_str());
		SetDlgItemText(hDlg, IDC_EDIT_W, std::to_string(uzr.w).c_str());
		SetDlgItemText(hDlg, IDC_EDIT_H, std::to_string(uzr.h).c_str());
		SetDlgItemText(hDlg, IDC_EDIT_TIMER, std::to_string(dTimer).c_str());
		SetDlgItemText(hDlg, IDC_EDIT_R, std::to_string(GetRValue(uzr.color)).c_str());
		SetDlgItemText(hDlg, IDC_EDIT_G, std::to_string(GetGValue(uzr.color)).c_str());
		SetDlgItemText(hDlg, IDC_EDIT_B, std::to_string(GetBValue(uzr.color)).c_str());
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON_CHOSE:
			CHOOSECOLOR cc;                 // ���������
			static COLORREF acrCustClr[16]; // ������ ������

			for (int i = 0; i < 16; i++)
			{
				acrCustClr[i] = RGB(rand() % 255, rand() % 255, rand() % 255);
			}

			// ��������� CHOOSECOLOR
			ZeroMemory(&cc, sizeof(cc));
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = hDlg; // ���� - ��������
			cc.lpCustColors = (LPDWORD)acrCustClr;
			cc.rgbResult = uzr.color;
			cc.Flags = CC_PREVENTFULLOPEN | CC_RGBINIT | CC_ENABLEHOOK;
			cc.lpfnHook = CCHookProc;

			if (ChooseColor(&cc) == TRUE)
			{
				SetDlgItemText(hDlg, IDC_EDIT_R, LPCSTR(std::to_string(GetRValue(cc.rgbResult)).c_str()));
				SetDlgItemText(hDlg, IDC_EDIT_G, LPCSTR(std::to_string(GetGValue(cc.rgbResult)).c_str()));
				SetDlgItemText(hDlg, IDC_EDIT_B, LPCSTR(std::to_string(GetBValue(cc.rgbResult)).c_str()));
			}
			
			break;
		case IDOK:
			uzr.x = GetDlgItemInt(hDlg, IDC_EDIT_X, (BOOL*)0, false);
			uzr.y = GetDlgItemInt(hDlg, IDC_EDIT_Y, (BOOL*)0, false);
			uzr.w = GetDlgItemInt(hDlg, IDC_EDIT_W, (BOOL*)0, false);
			uzr.h = GetDlgItemInt(hDlg, IDC_EDIT_H, (BOOL*)0, false);
			uzr.color = RGB(GetDlgItemInt(hDlg, IDC_EDIT_R, (BOOL*)0, false),
				GetDlgItemInt(hDlg, IDC_EDIT_G, (BOOL*)0, false),
				GetDlgItemInt(hDlg, IDC_EDIT_B, (BOOL*)0, false));
			dTimer = GetDlgItemInt(hDlg, IDC_EDIT_TIMER, (BOOL*)0, false);
			
			EndDialog(hDlg, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			break;
		}
		break;
	default: return FALSE;
	}

	return TRUE;
}

UINT APIENTRY CCHookProc(HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uiMsg)
	{
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
		return (UINT)CreateSolidBrush(RGB(255, 255, 255));
	case WM_DESTROY:
		PostMessage(hdlg, WM_COMMAND, IDABORT, lParam);
		break;
	}

	return 0u;
}

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
		x1 = uzr.x + (x1 + dx);
		y1 = uzr.y + (y1 + dy);
		x2 = uzr.x + (x2 + dx);
		y2 = uzr.y + (y2 + dy);

		// ����� ��������� ����� �� (x1,y1) �� (x2,y2)
		// (������� MoveToEx � LineTo)
		MoveToEx(hDC, x1, y1, NULL); // ����������� ������� ������� ���� � ����� � ������������(x1, y1)
		LineTo(hDC, x2, y2);              // �������� ����� �� ������� ������� ���� �� �����(x2, y2)

		// �������������� ��������� ��������� �����������
		SelectObject(hDC, prevPen); // ��������� "�������" ���� � �������� hDC
	}

	// �������� ��������� �������� GDI
	DeleteObject(uzrPen);
	DeleteObject(greyPen); // �������� ���� ��������� ������
}
