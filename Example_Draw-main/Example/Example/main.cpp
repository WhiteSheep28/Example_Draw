#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void DrawFigure(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    wchar_t szAppName[] = L"¿¬½À¿ë";
	HWND hWnd;
	MSG msg;
	WNDCLASS wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(DC_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

	RegisterClass(&wndclass);

    hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, 1000, 1000, 1000, 1000, NULL, NULL, hInstance, NULL);

    if (!hWnd) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (TRUE)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;
            DispatchMessage(&msg);
        }
        else
        { 
            DrawFigure(hWnd);
            Sleep(100);
        }
    }
    return (int)msg.wParam;
}

int g_nWidth, g_nHeight;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HBRUSH newBrush, oldBrush;
    HPEN newPen, oldPen;

    switch (message)
    {
	case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        for (int nXCount = 0; nXCount < 501; nXCount++)
        {
            for (int nYCount = 0; nYCount < 501; nYCount++)
            {
                SetPixel(hdc, nXCount + 500, nYCount + 500, GetPixel(hdc, nXCount, nYCount));
            }
        }

		EndPaint(hWnd, &ps);


    case WM_SIZE:
		g_nWidth = LOWORD(lParam);
		g_nHeight = HIWORD(lParam);
		break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void DrawFigure(HWND hWnd)
{
    HDC hdc;
    RECT rc = { 0, 0, 1000, 1000 };
    RECT r;
    HBRUSH newBrush, oldBrush;
    HPEN newPen, oldPen;
   
    if (g_nWidth && g_nHeight)
    {
        r.left = rand() % 500;
        r.top = rand() % 500;
        r.right = rand() % 500;
        r.bottom = rand() % 500;

        hdc = GetDC(hWnd);
		//newBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
		newBrush = CreateHatchBrush(rand() % 6, RGB(rand() % 256, rand() % 256, rand() % 256));
        oldBrush = (HBRUSH)SelectObject(hdc, newBrush);
		newPen = CreatePen(PS_SOLID, rand() % 50, RGB(rand() % 256, rand() % 256, rand() % 256));
        oldPen = (HPEN)SelectObject(hdc, newPen);
        Ellipse(hdc, r.left, r.top, r.right, r.bottom);

        r.left = rand() % 500;
        r.top = rand() % 500;
        r.right = rand() % 500;
        r.bottom = rand() % 500;

        Rectangle(hdc, r.left, r.top, r.right, r.bottom);


        SelectObject(hdc, oldBrush);
        DeleteObject(newBrush);
        ReleaseDC(hWnd, hdc);
        InvalidateRect(hWnd, &rc, FALSE);
    }
}