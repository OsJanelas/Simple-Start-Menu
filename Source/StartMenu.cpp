#include <windows.h>
#include "framework.h"

#include "StartMenu.h"

#define ID_BOTAO_SAIR 101

LRESULT CALLBACK MenuProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_CREATE:
        // BUTTON
        CreateWindowW(L"BUTTON", L"Close start",
            WS_VISIBLE | WS_CHILD | BS_FLAT,
            25, 330, 200, 40,
            hWnd, (HMENU)ID_BOTAO_SAIR, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wp) == ID_BOTAO_SAIR) {
            PostQuitMessage(0);
        }
        break;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TITLE
        SetTextColor(hdc, RGB(255, 255, 255));
        SetBkMode(hdc, TRANSPARENT);
        TextOutW(hdc, 25, 20, L"Hello User", 15);
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProcW(hWnd, msg, wp, lp);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int nShow) {
    WNDCLASSW wc = { 0 };
    wc.hbrBackground = CreateSolidBrush(RGB(15, 15, 25));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"Start";
    wc.lpfnWndProc = MenuProcedure;

    if (!RegisterClassW(&wc)) return -1;

    // POSITION
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    CreateWindowW(L"Start", L"Start menu",
        WS_POPUP | WS_VISIBLE,
        10, screenHeight - 450, 250, 400,
        NULL, NULL, hInst, NULL);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;

}
