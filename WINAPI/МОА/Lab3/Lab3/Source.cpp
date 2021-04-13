// --- Обязательный включаемый файл
#include <windows.h>

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW (WS_POPUP|WS_BORDER|WS_SYSMENU)


// --- Описание функции главного окна
LRESULT CALLBACK main_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK popup_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK child_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst; 		                   // Дескриптор экземпляра приложения

// --- Глобальные переменные
char ClassNameMain[] = "MainWindows";      // Название класса окна
char ClassNameChild[] = "ChildWindows";
char ClassNamePopup[] = "PopupWindows";

char AppTitleMain[] = "OVERLAPPEDWINDOW";  // Заголовок главного окна
char AppTitlePopup[] = "POPUPWINDOW";
char AppTitleChild[] = "CHILDWINDOW";


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
	WNDCLASS wcMain; // Структура для информации о классе окна
	WNDCLASS wcPopup, wcChild;

	HWND hWndMain;   // Дескриптор главного окна приложения
	HWND hWndPopup, hWndPopup2, hWndChild;
	//HWND hWndChild2; //

	MSG msg; // Структура для хранения сообщения

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
	if ((hWndMain = FindWindow(ClassNameMain, NULL)) != NULL)
	{
		// Пользователь может не помнить, какие приложения уже
		// запущены, а какие нет. Когда он запускает приложение, 
		// то ожидает, что на экране появится его главное окно.
		// Поэтому, если приложение было запущено ранее,
		// целесообразно активизировать и выдвинуть на передний
		// план его главное окно. Это именно то, к чему приготовился
		// пользователь.
		if (IsIconic(hWndMain)) ShowWindow(hWndMain, SW_RESTORE);
		SetForegroundWindow(hWndMain);

		// Найдена работающая копия - работа новой копии
		// прекращается.
		return FALSE;
	}

	// --- Работающая копия не найдена - функция WinMain
	// приступает к инициализации. Заполнение структуры
	// WNDCLASS для регистрации класса окна.
	memset(&wcMain, 0, sizeof(wcMain));
	wcMain.lpszClassName = ClassNameMain;                     // Имя класса окон
	wcMain.lpfnWndProc = (WNDPROC)main_WndProc;               // Адрес оконной функции
	wcMain.style = CS_HREDRAW | CS_VREDRAW;                   // Стиль класса
	wcMain.hInstance = hInstance;                             // Экземпляр приложения
	wcMain.hIcon = LoadIcon(NULL, IDI_APPLICATION);           // Пиктограмма для окон
	wcMain.hCursor = LoadCursor(NULL, IDC_ARROW);             // Курсор мыши для окон
	//wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Кисть для окон
	wcMain.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));  // Кисть для окон
	wcMain.lpszMenuName = NULL;                               // Ресурс меню окон
	wcMain.cbClsExtra = 0;                                    // Дополнительная память
	wcMain.cbWndExtra = 0;                                    // Дополнительная память
	// Pегистрация класса окна.
	RegisterClass(&wcMain);

	memset(&wcPopup, 0, sizeof(wcPopup));
	wcPopup.lpszClassName = ClassNamePopup;                   // Имя класса окон
	wcPopup.lpfnWndProc = (WNDPROC)popup_WndProc;             // Адрес оконной функции
	wcPopup.style = CS_HREDRAW | CS_VREDRAW;                  // Стиль класса
	wcPopup.hInstance = hInstance;                            // Экземпляр приложения
	wcPopup.hIcon = LoadIcon(NULL, IDI_APPLICATION);          // Пиктограмма для окон
	wcPopup.hCursor = LoadCursor(NULL, IDC_ARROW);            // Курсор мыши для окон
	wcPopup.hbrBackground = CreateSolidBrush(RGB(0, 255, 255)); // Кисть для окон
	wcPopup.lpszMenuName = NULL;                              // Ресурс меню окон
	wcPopup.cbClsExtra = 0;                                   // Дополнительная память
	wcPopup.cbWndExtra = 0;                                   // Дополнительная память
	// Pегистрация класса окна.
	RegisterClass(&wcPopup);

	memset(&wcChild, 0, sizeof(wcChild));
	wcChild.lpszClassName = ClassNameChild;                   // Имя класса окон
	wcChild.lpfnWndProc = (WNDPROC)child_WndProc;             // Адрес оконной функции
	wcChild.style = CS_HREDRAW | CS_VREDRAW;                  // Стиль класса
	wcChild.hInstance = hInstance;                            // Экземпляр приложения
	wcChild.hIcon = LoadIcon(NULL, IDI_APPLICATION);          // Пиктограмма для окон
	wcChild.hCursor = LoadCursor(NULL, IDC_ARROW);            // Курсор мыши для окон
	wcChild.hbrBackground = CreateSolidBrush(RGB(0145, 123, 200)); // Кисть для окон
	wcChild.lpszMenuName = NULL;                              // Ресурс меню окон
	wcChild.cbClsExtra = 0;                                   // Дополнительная память
	wcChild.cbWndExtra = 0;                                   // Дополнительная память
	// Pегистрация класса окна.
	RegisterClass(&wcChild);
	//WS_OVERLAPPEDWINDOW^WS_MINIMIZEBOX^WS_MAXIMIZEBOX

	// Создание главного перекрывающегося окна
	hWndMain = CreateWindow(
		ClassNameMain,              // Имя класса окон
		AppTitleMain,               // Заголовок окна
		WS_OVERLAPPEDWINDOW,        // Стиль окна
		0,                          // X-координаты
		0,                          // Y-координаты
		1280,                       // Ширина окна
		600,                        // Высота окна
		NULL,                       // Дескриптор окна-родителя
		NULL,                       // Дескриптор меню окна
		hInstance,                  // Дескриптор экземпляра приложения
		NULL);                      // Дополнительная информация
	if (!hWndMain)
	{
		// Окно не создано, выдаем предупреждение.
		MessageBox(NULL, "Create: error", AppTitleMain, MB_OK | MB_ICONSTOP);
		return FALSE;
	}

	// Отображаем окно.
	ShowWindow(hWndMain, nCmdShow);

	// Обновляем содержимое клиентской области окна.
	UpdateWindow(hWndMain);

	// Создание временного окна
	hWndPopup = CreateWindow(
		ClassNamePopup,                                // Имя класса окон
		AppTitlePopup,                                 // Заголовок окна
		WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | WS_VISIBLE,                   // Стиль окна
		900,                                           // X-координаты
		40,                                            // Y-координаты
		350,                                           // Ширина окна
		220,                                           // Высота окна
		hWndMain,                                      // Дескриптор окна-родителя
		NULL,                                          // Дескриптор меню окна
		hInstance,                                     // Дескриптор экземпляра приложения
		NULL                                           // Дополнительная информация
	);
	if (!hWndPopup)
	{
		DestroyWindow(hWndMain);
		return FALSE;
	}

	// Отображаем окно.
	ShowWindow(hWndPopup, nCmdShow);

	// Обновляем содержимое клиентской области окна.
	UpdateWindow(hWndPopup);

	// Создание временного окна
	hWndPopup2 = CreateWindow(
		ClassNamePopup,                                // Имя класса окон
		AppTitlePopup,                                 // Заголовок окна
		WS_POPUPWINDOW | WS_CAPTION | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | WS_VISIBLE,                   // Стиль окна
		500,                                           // X-координаты
		40,                                            // Y-координаты
		350,                                           // Ширина окна
		220,                                           // Высота окна
		NULL,                                          // Дескриптор окна-родителя
		NULL,                                          // Дескриптор меню окна
		hInstance,                                     // Дескриптор экземпляра приложения
		NULL                                           // Дополнительная информация
	);
	if (!hWndPopup2)
	{
		DestroyWindow(hWndMain);
		return FALSE;
	}

	// Отображаем окно.
	ShowWindow(hWndPopup2, nCmdShow);

	// Обновляем содержимое клиентской области окна.
	UpdateWindow(hWndPopup2);

	// Создание дочернего окна
	hWndChild = CreateWindow(
		ClassNameChild,                                // Имя класса окон
		AppTitleChild,                                 // Заголовок окна 
		WS_CHILDWINDOW | WS_CAPTION | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | CS_HREDRAW | CS_VREDRAW,      // Стиль окна  
		50,                                            // X-координаты
		200,                                           // Y-координаты
		400,                                           // Ширина окна
		300,                                           // Высота окна
		hWndMain,                                      // Дескриптор окна-родителя
		NULL,                                          // Дескриптор меню окна
		hInstance,                                     // Дескриптор экземпляра приложения
		NULL);                                         // Дополнительная информация

	if (!hWndChild)
	{
		DestroyWindow(hWndMain);
		DestroyWindow(hWndPopup);
		return FALSE;
	}

	// Отображаем окно.
	ShowWindow(hWndChild, nCmdShow);

	// Обновляем содержимое клиентской области окна.
	UpdateWindow(hWndChild);

	// Запускаем цикл обработки очереди сообщений.
	// Функция GetMessage получает сообщение из очереди, 
	// выдает false при выборке из очереди сообщения WM_QUIT
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Преобразование некоторых сообщений, 
		// полученных с помощью клавиатуры
		TranslateMessage(&msg);
		// Отправляем сообщение оконной процедуре
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

// --- Функция окна
LRESULT CALLBACK main_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char x[10] = "", y[10] = "";

	switch (msg)
	{
		// Необходимо обновить содержимое клиентской области окна.
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // Получение контекста отображения окна hWnd
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		_itoa_s(screenWidth, x, sizeof(x));
		_itoa_s(screenHeight, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 20, "Ширина экрана", 14);
		TextOut(hDC, 20, 40, "Высота экрана", 14);
		TextOut(hDC, 140, 20, x, strlen(x));
		TextOut(hDC, 140, 40, y, strlen(y));

		RECT r;                  // Рабочая область окна
		GetClientRect(hWnd, &r);
		GetWindowRect(hWnd, &r); // Получить область окна

		int xLeft = r.left;
		int yLeft = r.top;

		_itoa_s(xLeft, x, sizeof(x));
		_itoa_s(yLeft, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 60, "Координата X верхнего левого угла", 34);
		TextOut(hDC, 20, 80, "Координата Y верхнего левого угла", 34);
		TextOut(hDC, 300, 60, x, strlen(x));
		TextOut(hDC, 300, 80, y, strlen(y));

		int xRight = r.right;
		int yRight = r.bottom;

		_itoa_s(xRight, x, 10);
		_itoa_s(yRight, y, 10);

		// Нарисовать текст
		TextOut(hDC, 20, 100, "Координата X нижнего правого угла", 34);
		TextOut(hDC, 20, 120, "Координата Y нижнего правого угла", 34);
		TextOut(hDC, 300, 100, x, strlen(x));
		TextOut(hDC, 300, 120, y, strlen(y));

		int xWin = r.right - r.left;
		int yWin = r.bottom - r.top;

		_itoa_s(xWin, x, 10);
		_itoa_s(yWin, y, 10);

		// Нарисовать текст
		TextOut(hDC, 20, 140, "Ширина окна", 12);
		TextOut(hDC, 20, 160, "Высота окна", 12);
		TextOut(hDC, 300, 140, x, strlen(x));
		TextOut(hDC, 300, 160, y, strlen(y));

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

// --- Функция окна
LRESULT CALLBACK child_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char x[10] = "", y[10] = "";

	switch (msg)
	{
		// Необходимо обновить содержимое клиентской области окна.
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // Получение контекста отображения окна hWnd
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		_itoa_s(screenWidth, x, sizeof(x));
		_itoa_s(screenHeight, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 20, "Ширина экрана", 14);
		TextOut(hDC, 20, 40, "Высота экрана", 14);
		TextOut(hDC, 140, 20, x, strlen(x));
		TextOut(hDC, 140, 40, y, strlen(y));

		RECT r;                  // Рабочая область окна
		GetClientRect(hWnd, &r);
		GetWindowRect(hWnd, &r); // Полученить область окна

		int xLeft = r.left;
		int yLeft = r.top;

		_itoa_s(xLeft, x, sizeof(x));
		_itoa_s(yLeft, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 60, "Координата X верхнего левого угла", 34);
		TextOut(hDC, 20, 80, "Координата Y верхнего левого угла", 34);
		TextOut(hDC, 300, 60, x, strlen(x));
		TextOut(hDC, 300, 80, y, strlen(y));

		int xRight = r.right;
		int yRight = r.bottom;

		_itoa_s(xRight, x, sizeof(x));
		_itoa_s(yRight, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 100, "Координата X нижнего правого угла", 34);
		TextOut(hDC, 20, 120, "Координата Y нижнего правого угла", 34);
		TextOut(hDC, 300, 100, x, strlen(x));
		TextOut(hDC, 300, 120, y, strlen(y));

		int xWin = r.right - r.left;
		int yWin = r.bottom - r.top;

		_itoa_s(xWin, x, sizeof(x));
		_itoa_s(yWin, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 140, "Ширина окна", 12);
		TextOut(hDC, 20, 160, "Высота окна", 12);
		TextOut(hDC, 300, 140, x, strlen(x));
		TextOut(hDC, 300, 160, y, strlen(y));

		EndPaint(hWnd, &ps); // Освободить контекст окна
	}; break;

	// Пользователь удалил окно.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
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

// --- Функция окна
LRESULT CALLBACK popup_WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	char x[10] = "", y[10] = "";

	switch (msg)
	{
		// Необходимо обновить содержимое клиентской области окна.
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // Получение контекста отображения окна hWnd
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);

		_itoa_s(screenWidth, x, sizeof(x));
		_itoa_s(screenHeight, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 20, "Ширина экрана", 14);
		TextOut(hDC, 20, 40, "Высота экрана", 14);
		TextOut(hDC, 140, 20, x, strlen(x));
		TextOut(hDC, 140, 40, y, strlen(y));

		RECT r;                  // Рабочая область окна
		GetClientRect(hWnd, &r);
		GetWindowRect(hWnd, &r); // Получить область окна

		int xLeft = r.left;
		int yLeft = r.top;

		_itoa_s(xLeft, x, sizeof(x));
		_itoa_s(yLeft, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 60, "Координата X верхнего левого угла", 34);
		TextOut(hDC, 20, 80, "Координата Y верхнего левого угла", 34);
		TextOut(hDC, 300, 60, x, strlen(x));
		TextOut(hDC, 300, 80, y, strlen(y));

		int xRight = r.right;
		int yRight = r.bottom;

		_itoa_s(xRight, x, sizeof(x));
		_itoa_s(yRight, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 100, "Координата X нижнего правого угла", 34);
		TextOut(hDC, 20, 120, "Координата Y нижнего правого угла", 34);
		TextOut(hDC, 300, 100, x, strlen(x));
		TextOut(hDC, 300, 120, y, strlen(y));

		int xWin = r.right - r.left;
		int yWin = r.bottom - r.top;

		_itoa_s(xWin, x, sizeof(x));
		_itoa_s(yWin, y, sizeof(y));

		// Нарисовать текст
		TextOut(hDC, 20, 140, "Ширина окна", 12);
		TextOut(hDC, 20, 160, "Высота окна", 12);
		TextOut(hDC, 300, 140, x, strlen(x));
		TextOut(hDC, 300, 160, y, strlen(y));

		EndPaint(hWnd, &ps); // Освободить контекст окна
	}; break;

	// Пользователь удалил окно.
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

	// Необработанные сообщения передаем в стандартную
	// функцию обработки сообщений по умолчанию.
	default: return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0l;
}
