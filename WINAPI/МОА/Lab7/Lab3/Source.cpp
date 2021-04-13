// --- Обязательный включаемый файл
#include <windows.h>
#include <cmath>

#define WS_OVERLAPPEDWINDOW (WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_THICKFRAME|WS_MINIMIZEBOX|WS_MAXIMIZEBOX)
#define WS_POPUPWINDOW      (WS_POPUP|WS_BORDER|WS_SYSMENU)

// --- Описание функции главного окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// --- Глобальные переменные
HINSTANCE hInst; 		                 // Дескриптор экземпляра приложения
char ClassName[] = "WindowLab"; 		 // Название класса окна
char AppTitle[] = "Application Win32";   // Заголовок главного окна

struct UZOR
{
	unsigned C1, A3, A4, B3, B4; // коэффициенты 
	int x, y;                    // координаты лев. верх. угла изображения 
	unsigned w, h;               // ширина и высота рисунка (размер)
	COLORREF color;              // цвет линии (цвет изображения)
};

void uzor(HDC hDC, struct UZOR uzr) // функция вывода узора
{
	int dx = uzr.w / 2, dy = uzr.h / 2, ddx = dx / 4, ddy = dy / 4, x1, x2, y1, y2;
	double D, T = 5;
	COLORREF grey = RGB(127, 127, 127); // серый цвет чередуется с цветом изображения.
	int step = 1;

	// создание объектов GDI (функция CreatePen)
	HPEN uzrPen = CreatePen(PS_SOLID, 3, uzr.color); // создание сплошного пера цвета uzr.color толщиной 3 пикселя
	HPEN greyPen = CreatePen(PS_SOLID, 3, grey);     // создание сплошного пера цвета grey толщиной 3 пикселя
	HPEN prevPen;

	for (double t = 0; t < T; t += 0.01) // рисуем очередной фрагмент узора t ( 0<=T<5)
	{
		// установка атрибутов контекста отображения (функция SelectObject)
		if (step)
		{
			prevPen = (HPEN)SelectObject(hDC, uzrPen); // установка пера цвета изображения в контекст hDC
			// и сохранение "старого" пера
		}
		else
		{
			prevPen = (HPEN)SelectObject(hDC, greyPen); // установка пера серого цвета в контекст hDC
			// и сохранение "старого" пера
		}

		step = !step;

		// определение координат начала и конца очередной линии узора
		D = t + uzr.C1;
		x1 = (int)((2 * cos(uzr.A4 * t) + 2 * cos(uzr.A3 * 2 * t)) * ddx);
		y1 = (int)((2 * cos(uzr.B4 * t) + 2 * cos(uzr.B3 * 2 * t)) * ddy);
		x2 = (int)((2 * cos(uzr.A4 * D) + 2 * cos(uzr.A3 * 2 * D)) * ddx);
		y2 = (int)((2 * cos(uzr.B4 * D) + 2 * cos(uzr.B3 * 2 * D)) * ddy);
		x1 = uzr.x + (x1 + dx); y1 = uzr.y + (y1 + dy);
		x2 = uzr.x + (x2 + dx); y2 = uzr.y + (y2 + dy);

		// вывод очередной линии от (x1,y1) до (x2,y2)
		// (функции MoveToEx и LineTo)
		MoveToEx(hDC, x1, y1, NULL); // передвинуть текущую позицию пера в точку с координатами(x1, y1)
		LineTo(hDC, x2, y2);         // провести линию от текущей позиции пера до точки(x2, y2)

		// восстановление атрибутов контекста отображения
		SelectObject(hDC, prevPen); // установка "старого" пера в контекст hDC
	}

	// удаление созданных объектов GDI
	DeleteObject(uzrPen); DeleteObject(greyPen); // удаление двух созданных перьев
}

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static struct UZOR uzr;

	switch (msg)
	{
		// Необходимо обновить содержимое клиентской области окна.
	case WM_PAINT:
	{
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWnd, &ps);                       // Получение контекста отображения окна hWnd
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
