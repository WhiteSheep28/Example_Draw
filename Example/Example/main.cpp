#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

	RegisterClass(&wndclass);

    hWnd = CreateWindow(szAppName, szAppName, WS_OVERLAPPEDWINDOW, 100, 100, 250, 200, NULL, NULL, hInstance, NULL);

    if (!hWnd) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    HBRUSH newBrush, oldBrush;

    switch (message)
    {
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        HPEN NewPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        HPEN OldPen = (HPEN)SelectObject(hdc, NewPen);

        MoveToEx(hdc, 10, 10, NULL);
        LineTo(hdc, 100, 10);

        Rectangle(hdc, 110, 10, 210, 100);
        
        newBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
		oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

        RoundRect(hdc, 220, 10, 320, 100, 30, 30);

        Ellipse(hdc, 330, 10, 430, 100);

        SelectObject(hdc, oldBrush);

        SelectObject(hdc, OldPen);
        DeleteObject(NewPen);

        EndPaint(hWnd, &ps);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}