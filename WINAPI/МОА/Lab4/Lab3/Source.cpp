// --- Обязательный включаемый файл
#include <windows.h>
#include "resource.h"

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW      (WS_POPUP|WS_BORDER|WS_SYSMENU)

// --- Описание функции главного окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// --- Глобальные переменные
HINSTANCE hInst; 		                 // Дескриптор экземпляра приложения
char ClassName[] = "WindowLab"; 		 // Название класса окна
char AppTitle[] = "Application Win32";   // Заголовок главного окна

// --- Функция WinMain
int WINAPI WinMain(
	HINSTANCE hInstance,     // Дескриптор экземпляра приложения
	HINSTANCE hPrevInstance, // В Win32 всегда равен NULL
	LPSTR lpCmdLine,
	// Указатель на командную строку. Он
	// позволяет
	// приложению получать данные из командной строки.
	int nCmdShow
	// Определяет, как приложение первоначально 
	// отображается на дисплее: пиктограммой
	// (nCmdShow = SW_SHOWMINNOACTIVE) 
	// или в виде открытого окна
	// (nCmdShow = SW_SHOWNORMAL).
)
{
	WNDCLASS wc; // Структура для информации о классе окна
	HWND hWnd;   // Дескриптор главного окна приложения
	MSG msg;     // Структура для хранения сообщения

	// Сохраняем дескриптор экземпляра приложения в глобальной
	// переменной, чтобы при необходимости воспользоваться им в
	// функции окна.
	hInst = hInstance;

	// --- Проверяем, было ли приложение запущено ранее.
	// Воспользуемся функцией FindWindow, которая позволяет
	// найти окно верхнего 
	// уровня по имени класса или по заголовку окна:
	// HWND FindWindow(LPCTSTR lpClassName,
	// LPCTSTRlpWindowName);
	// Через параметр lpClassName передается указатель на
	// текстовую строку, в которую необходимо записать имя
	// класса искомого окна. На базе одного и того же класса 
	// можно создать несколько окон. Если необходимо найти 
	// окно с заданным заголовком, то имя заголовка следует
	// передать через параметр lpWindowName. Если же подойдет 
	// любое окно, то параметр lpWindowName может иметь
	// значение NULL.
	if ((hWnd = FindWindow(ClassName, NULL)) != NULL)
	{
		// Пользователь может не помнить, какие приложения уже
		// запущены, а какие нет. Когда он запускает приложение, 
		// то ожидает, что на экране появится его главное окно.
		// Поэтому, если приложение было запущено ранее,
		// целесообразно активизировать и выдвинуть на передний
		// план его главное окно. Это именно то, к чему приготовился
		// пользователь.
		if (IsIconic(hWnd)) ShowWindow(hWnd, SW_RESTORE);
		SetForegroundWindow(hWnd);

		// Найдена работающая копия - работа новой копии
		// прекращается.
		return FALSE;
	}

	// --- Работающая копия не найдена - функция WinMain
	// приступает к инициализации. Заполнение структуры
	// WNDCLASS для регистрации класса окна.
	memset(&wc, 0, sizeof(wc));
	wc.lpszClassName = ClassName;                                 // Имя класса окон
	wc.lpfnWndProc = (WNDPROC)WndProc;                            // Адрес оконной функции
	wc.style = CS_HREDRAW | CS_VREDRAW;                           // Стиль класса
	wc.hInstance = hInstance;                                     // Экземпляр приложения
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);                   // Пиктограмма для окон
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);                     // Курсор мыши для окон
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);       // Кисть для окон
	wc.lpszMenuName = NULL;                                       // Ресурс меню окон
	wc.cbClsExtra = 0;                                            // Дополнительная память
	wc.cbWndExtra = 0;                                            // Дополнительная память
	// Pегистрация класса окна.
	RegisterClass(&wc);

	// Создание главного перекрывающегося окна
	hWnd = CreateWindow(
		ClassName,                  // Имя класса окон
		AppTitle,                   // Заголовок окна
		WS_OVERLAPPEDWINDOW,        // Стиль окна
		0,                          // X-координаты
		0,                          // Y-координаты
		1280,                       // Ширина окна
		600,                        // Высота окна
		NULL,                       // Дескриптор окна-родителя
		NULL,                       // Дескриптор меню окна
		hInstance,                  // Дескриптор экземпляра приложения
		NULL);                      // Дополнительная информация
	if (!hWnd)
	{
		// Окно не создано, выдаем предупреждение.
		MessageBox(NULL, "Create: error", AppTitle, MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	// Отображаем окно.
	ShowWindow(hWnd, nCmdShow);

	// Обновляем содержимое клиентской области окна.
	UpdateWindow(hWnd);

	HACCEL hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

	// Запускаем цикл обработки очереди сообщений.
	// Функция GetMessage получает сообщение из очереди, 
	// выдает false при выборке из очереди сообщения WM_QUIT
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccel, &msg))
		{
			// Преобразование некоторых сообщений, 
			// полученных с помощью клавиатуры
			TranslateMessage(&msg);
			// Отправляем сообщение оконной процедуре
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

// --- Функция окна
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
		SetTimer(hWnd,             // Дескриптор окна
			1,                     // Идентификатор таймера
			interval,              // Интервал
			NULL);      // Функция обратного вызова
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
			SetTimer(hWnd,             // Дескриптор окна
				1,                     // Идентификатор таймера
				interval,              // Интервал
				NULL);                 // Функция обратного вызова
		}; break;

		case VK_DOWN:
		{
			interval /= 2;
			SetTimer(hWnd,             // Дескриптор окна
				1,                     // Идентификатор таймера
				interval,              // Интервал
				NULL);                 // Функция обратного вызова
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
		// состояние кнопок мыши
		UINT fwKeys = wParam;
		// горизонтальная позиция курсора
		int xPos = LOWORD(lParam);
		// вертикальная позиция курсора
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

	// Необходимо обновить содержимое клиентской области окна.
	case WM_PAINT:
	{
		char temp_buffer[128] = "Счётчик таймера: ";

		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // Получение контекста отображения окна hWnd

		_itoa_s(counter, counter_buffer, sizeof(counter_buffer));
		strcat_s(temp_buffer, sizeof(temp_buffer), counter_buffer);

		// Нарисовать текст
		TextOut(hDC, 20, 20, temp_buffer, strlen(temp_buffer));

		strcpy_s(temp_buffer, sizeof(temp_buffer), "Последний нажатый символ: ");
		strcat_s(temp_buffer, sizeof(temp_buffer), char_buffer);

		// Нарисовать текст
		TextOut(hDC, 20, 40, temp_buffer, strlen(temp_buffer));

		if (lbuttondown_flag)
		{
			// Нарисовать текст
			TextOut(hDC, 20, 60, "Была нажата левая кнопка мыши", 30);
		}
		else if (rbuttondown_flag)
		{
			// Нарисовать текст
			TextOut(hDC, 20, 60, "Была нажата правая кнопка мыши", 31);
		}

		EndPaint(hWnd, &ps); // Освободить контекст окна
	}; break;

	// Пользователь удалил окно.
	case WM_DESTROY:
	{
		// Если данная функция является оконной функцией
		// главного окна, то следует в очередь сообщений
		// приложения послать сообщение WM_QUIT
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

	// Необработанные сообщения передаем в стандартную
	// функцию обработки сообщений по умолчанию.
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0l;
}
