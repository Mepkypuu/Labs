#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
int RegClass(void);
HINSTANCE hInstance;
HWND hwnd_main;
static HDC hdc, hdc2, hdc3, hdc4, p;
static int xPos, yPos;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInstance = hInst;
    if (!RegClass()) return -1;

    hwnd_main = CreateWindow("MyWindowClass", "Светофор",
        WS_OVERLAPPEDWINDOW,
        0, 0, 250, 450, NULL, NULL, hInstance, 0);

    if (!hwnd_main) return 0;
    ShowWindow(hwnd_main, SW_SHOW);
    UpdateWindow(hwnd_main);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

int RegClass(void)
{
    WNDCLASS wc;
    memset(&wc, 0, sizeof(WNDCLASS));
    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "MyWindowClass";

    return RegisterClass(&wc);
}

void Create(HWND, LPARAM);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

    case WM_MOVE: {
        RECT r;
        r.bottom = 360;
        r.left = 60;
        r.right = 150;
        r.top = 60;
        HDC p = GetDC(hwnd_main);
        HBRUSH br = CreateSolidBrush(RGB(128, 128, 128));
        SelectObject(p, br);
        FrameRect(p, &r, br);
        DeleteObject(br);

        /////////////////////////////////////////////////
        HDC hdc = GetDC(hwnd_main);
        HBRUSH brush = (HBRUSH)GetStockObject(GRAY_BRUSH);
        SetROP2(hdc, R2_COPYPEN);
        HGDIOBJ obj = SelectObject(hdc, brush);
        SelectObject(hdc, obj);
        Ellipse(hdc, 70, 70, 140, 140);
        ReleaseDC(hwnd, hdc);
        ////////////////////////////////////////////////////
        HDC hdc2 = GetDC(hwnd_main);
        SetROP2(hdc2, R2_COPYPEN);
        HGDIOBJ obj2 = SelectObject(hdc2, brush);
        SelectObject(hdc2, obj2);
        Ellipse(hdc2, 70, 175, 140, 245);
        ReleaseDC(hwnd, hdc2);
        ///////////////////////////////////////////////////
        HDC hdc3 = GetDC(hwnd_main);
        SetROP2(hdc3, R2_COPYPEN);
        HGDIOBJ obj3 = SelectObject(hdc3, brush);
        SelectObject(hdc3, obj3);
        Ellipse(hdc3, 70, 280, 140, 350);
        DeleteObject(brush);
        ReleaseDC(hwnd, hdc2);
        break;
    }

    case WM_LBUTTONDOWN: {

        xPos = LOWORD(lParam);
        yPos = HIWORD(lParam);
        if (xPos > 70 && xPos < 140 && yPos>280 && yPos < 350) {
            HDC hdc4 = GetDC(hwnd_main);
            HBRUSH brush = CreateSolidBrush(RGB(100, 255, 0));
            SelectObject(hdc4, brush);
            Ellipse(hdc4, 70, 280, 140, 350);
            DeleteObject(brush);
            //-------------------------
            HDC hdc = GetDC(hwnd_main);
            HBRUSH brush2 = (HBRUSH)GetStockObject(GRAY_BRUSH);
            SetROP2(hdc, R2_COPYPEN);
            HGDIOBJ obj = SelectObject(hdc, brush2);
            SelectObject(hdc, obj);
            Ellipse(hdc, 70, 70, 140, 140);
            ReleaseDC(hwnd, hdc);
            //----------------------------
            HDC hdc2 = GetDC(hwnd_main);
            SetROP2(hdc2, R2_COPYPEN);
            HGDIOBJ obj2 = SelectObject(hdc2, brush2);
            SelectObject(hdc2, obj2);
            Ellipse(hdc2, 70, 175, 140, 245);
            DeleteObject(brush2);
            ReleaseDC(hwnd, hdc2);
        }
        if ((yPos > 70 && xPos < 140 && xPos>70 && yPos < 140)) {
            HDC hdc4 = GetDC(hwnd_main);
            HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
            SelectObject(hdc4, brush);
            Ellipse(hdc4, 70, 70, 140, 140);
            DeleteObject(brush);
            //---------------------------
            HDC hdc2 = GetDC(hwnd_main);
            HBRUSH brush3 = (HBRUSH)GetStockObject(GRAY_BRUSH);
            SetROP2(hdc2, R2_COPYPEN);
            HGDIOBJ obj2 = SelectObject(hdc2, brush3);
            SelectObject(hdc2, obj2);
            Ellipse(hdc2, 70, 175, 140, 245);
            //DeleteObject(brush3);
            ReleaseDC(hwnd, hdc2);
            //----------------------
            HDC hdc3 = GetDC(hwnd_main);
            SetROP2(hdc3, R2_COPYPEN);
            HGDIOBJ obj3 = SelectObject(hdc3, brush3);
            SelectObject(hdc3, obj3);
            Ellipse(hdc3, 70, 280, 140, 350);
            DeleteObject(brush3);
            ReleaseDC(hwnd, hdc2);
        }
        //-----------------------
        if ((xPos > 70 && xPos < 140) && (yPos > 175 && yPos < 245)) {
            HDC hdc4 = GetDC(hwnd_main);
            HBRUSH brush = CreateSolidBrush(RGB(255, 255, 190));
            SelectObject(hdc4, brush);
            Ellipse(hdc4, 70, 175, 140, 245);
            DeleteObject(brush);
            //--------------------------
            HDC hdc3 = GetDC(hwnd_main);
            HBRUSH brush3 = (HBRUSH)GetStockObject(GRAY_BRUSH);
            SetROP2(hdc3, R2_COPYPEN);
            HGDIOBJ obj3 = SelectObject(hdc3, brush3);
            SelectObject(hdc3, obj3);
            Ellipse(hdc3, 70, 280, 140, 350);
            DeleteObject(brush3);
            ReleaseDC(hwnd, hdc2);
            //-----------------------------
            HDC hdc = GetDC(hwnd_main);
            HBRUSH brush2 = (HBRUSH)GetStockObject(GRAY_BRUSH);
            SetROP2(hdc, R2_COPYPEN);
            HGDIOBJ obj = SelectObject(hdc, brush2);
            SelectObject(hdc, obj);
            Ellipse(hdc, 70, 70, 140, 140);
            ReleaseDC(hwnd, hdc);
        }
        break;
    }

    default: return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}