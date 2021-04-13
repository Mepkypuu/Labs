#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

HWND Edit;
static HWND button_1;
static HWND button_2;
static HWND button_3;
static HWND button_4;
static HWND button_5;
static HWND button_6;
static HWND button_7;
static HWND button_8;
static HWND button_9;
static HWND button_Zero;
static HWND button_Point;
static HWND button_Plus;
static HWND button_Minus;
static HWND button_Multiply;
static HWND button_Divided;
static HWND button_Equally;
static HWND button_C;
static HWND button_NEG;
static HWND button_CE;
char* FirstOperand = new char[32];
char* SecondOperand = new char[32];
int Sign;

#define Zero 0
#define Plus 11
#define Minus 12
#define Multiply 13
#define Divided 14
#define Equally 100
#define Point 101
#define ClearAll 102
#define Negative 103
#define ClearLast 104





LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {

    case(WM_CREATE): {
        FirstOperand[0] = 0;
        SecondOperand[0] = 0;
    }
                   break;

    case WM_COMMAND: {

        switch (LOWORD(wParam)) {
        case 1: {
            strcat(FirstOperand, "1");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case 2: {
            strcat(FirstOperand, "2");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case 3: {
            strcat(FirstOperand, "3");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case 4: {
            strcat(FirstOperand, "4");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case 5: {
            strcat(FirstOperand, "5");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case 6: {
            strcat(FirstOperand, "6");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case 7: {
            strcat(FirstOperand, "7");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case 8: {
            strcat(FirstOperand, "8");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case 9: {
            strcat(FirstOperand, "9");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case Zero: {
            strcat(FirstOperand, "0");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case Point: {
            if (strstr(FirstOperand, ".") == 0)
                strcat(FirstOperand, ".");
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case ClearAll: {
            FirstOperand[0] = 0;
            SecondOperand[0] = 0;
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case ClearLast: {
            FirstOperand[0] = 0;
            SetWindowText(Edit, FirstOperand);
            break;
        }

        case Plus: {
            Sign = Plus;
            for (int i = 0; i <= strlen(FirstOperand); i++)
                SecondOperand[i] = FirstOperand[i];
            FirstOperand[0] = 0;
            SetWindowText(Edit, "");
            break;
        }

        case Minus: {
            Sign = Minus;
            for (int i = 0; i <= strlen(FirstOperand); i++)
                SecondOperand[i] = FirstOperand[i];
            FirstOperand[0] = 0;
            SetWindowText(Edit, "");
            break;
        }

        case Multiply: {
            Sign = Multiply;
            for (int i = 0; i <= strlen(FirstOperand); i++)
                SecondOperand[i] = FirstOperand[i];
            FirstOperand[0] = 0;
            SetWindowText(Edit, "");
            break;
        }

        case Divided: {
            Sign = Divided;
            for (int i = 0; i <= strlen(FirstOperand); i++)
                SecondOperand[i] = FirstOperand[i];
            FirstOperand[0] = 0;
            SetWindowText(Edit, "");
            break;
        }

        case Equally: {
            double _FirstOperand = atof(FirstOperand);
            double _SecondOperand = atof(SecondOperand);
            if (_FirstOperand == 0 && Sign == Divided) {
                MessageBox(NULL, "Деление на ноль", "ERROR", MB_ICONERROR);
                FirstOperand[0] = 0;
                SecondOperand[0] = 0;
                break;
            }
            FirstOperand[0] = 0;
            SecondOperand[0] = 0;

            if (Sign == Plus) {
                double FirstOperandDouble = _SecondOperand + _FirstOperand;
                sprintf(FirstOperand, "%lf", FirstOperandDouble);
            }

            if (Sign == Minus) {
                double FirstOperandDouble = _SecondOperand - _FirstOperand;
                sprintf(FirstOperand, "%lf", FirstOperandDouble);

            }

            if (Sign == Multiply) {
                double FirstOperandDouble = _SecondOperand * _FirstOperand;
                sprintf(FirstOperand, "%lf", FirstOperandDouble);
            }

            if (Sign == Divided) {
                double FirstOperandDouble = _SecondOperand / _FirstOperand;
                sprintf(FirstOperand, "%lf", FirstOperandDouble);
            }

            SetWindowText(Edit, FirstOperand);
            break;
        }


        case Negative: {
            double _FirstOperand = atof(FirstOperand);
            double _SecondOperand = 0;
            double FirstOperandDouble = _SecondOperand - _FirstOperand;
            sprintf(FirstOperand, "%lf", FirstOperandDouble);
            SetWindowText(Edit, FirstOperand);
            break;
        }

        }

        break;
    }


    case WM_DESTROY: {
        delete[] FirstOperand;
        delete[] SecondOperand;
        PostQuitMessage(0);
        break;
    }


    default:
        return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;


    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);


    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Калькулятор", WS_VISIBLE | WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_THICKFRAME),
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        170, 
        260, 
        NULL, NULL, hInstance, NULL);

    Edit = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", "", WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_NUMBER,
        10, 
        10, 
        139, 
        30, 
        hwnd,
        NULL,
        hInstance,
        NULL);

    button_1 = CreateWindow("button", "1", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 149, 30, 30, hwnd, HMENU(1), hInstance, NULL);
    button_2 = CreateWindow("button", "2", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 43, 149, 30, 30, hwnd, HMENU(2), hInstance, NULL);
    button_3 = CreateWindow("button", "3", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 76, 149, 30, 30, hwnd, HMENU(3), hInstance, NULL);
    button_4 = CreateWindow("button", "4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 116, 30, 30, hwnd, HMENU(4), hInstance, NULL);
    button_5 = CreateWindow("button", "5", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 43, 116, 30, 30, hwnd, HMENU(5), hInstance, NULL);
    button_6 = CreateWindow("button", "6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 76, 116, 30, 30, hwnd, HMENU(6), hInstance, NULL);
    button_7 = CreateWindow("button", "7", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 83, 30, 30, hwnd, HMENU(7), hInstance, NULL);
    button_8 = CreateWindow("button", "8", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 43, 83, 30, 30, hwnd, HMENU(8), hInstance, NULL);
    button_9 = CreateWindow("button", "9", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 76, 83, 30, 30, hwnd, HMENU(9), hInstance, NULL);
    button_Zero = CreateWindow("button", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 43, 182, 30, 30, hwnd, HMENU(Zero), hInstance, NULL);
    button_Plus = CreateWindow("button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 119, 149, 30, 30, hwnd, HMENU(Plus), hInstance, NULL);
    button_Minus = CreateWindow("button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 119, 116, 30, 30, hwnd, HMENU(Minus), hInstance, NULL);
    button_Multiply = CreateWindow("button", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 119, 83, 30, 30, hwnd, HMENU(Multiply), hInstance, NULL);
    button_Divided = CreateWindow("button", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 119, 50, 30, 30, hwnd, HMENU(Divided), hInstance, NULL);
    button_Equally = CreateWindow("button", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 119, 182, 30, 30, hwnd, HMENU(Equally), hInstance, NULL);
    button_Point = CreateWindow("button", ".", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 76, 182, 30, 30, hwnd, HMENU(Point), hInstance, NULL);
    button_C = CreateWindow("button", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 43, 50, 30, 30, hwnd, HMENU(ClearAll), hInstance, NULL);
    button_NEG = CreateWindow("button", "-/+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 182, 30, 30, hwnd, HMENU(Negative), hInstance, NULL);
    button_CE = CreateWindow("button", "CE", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 10, 50, 30, 30, hwnd, HMENU(ClearLast), hInstance, NULL);


    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }


    while (GetMessage(&Msg, NULL, 0, 0) > 0) { 
        TranslateMessage(&Msg); 
        DispatchMessage(&Msg); 
    }
    return Msg.wParam;
}