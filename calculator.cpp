#include <windows.h>
#include <iostream>
#include <cstdlib>

#define ID_INPUT1 101
#define ID_INPUT2 102
#define ID_MULTIPLY 1
#define ID_DIVIDE 2
#define ID_ADD 3
#define ID_SUBTRACT 4
HWND input1, input2,multi_button,divide_button,plus_button,minus_button;
/* Callback function for handling window messages */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    static HWND textfield;

    switch (Message) {
        case WM_CREATE:
            textfield = CreateWindow("STATIC", "Please input two numbers",
                                     WS_VISIBLE | WS_CHILD | SS_CENTER, 
                                     10, 10, 180, 20, hwnd, NULL, NULL, NULL);
                input1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                        10, 40, 100, 25, hwnd, (HMENU)ID_INPUT1, NULL, NULL);
                input2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                        10, 80, 100, 25, hwnd, (HMENU)ID_INPUT2, NULL, NULL);
                multi_button = CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                            90, 120, 30, 30, hwnd, (HMENU)ID_MULTIPLY, NULL, NULL);
                divide_button = CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                             130, 120, 30, 30, hwnd, (HMENU)ID_DIVIDE, NULL, NULL);
                plus_button = CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                           10, 120, 30, 30, hwnd, (HMENU)ID_ADD, NULL, NULL);
                minus_button = CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                            50, 120, 30, 30, hwnd, (HMENU)ID_SUBTRACT, NULL, NULL);
        
            break;
            case WM_COMMAND:
            if (LOWORD(wParam) >= ID_MULTIPLY && LOWORD(wParam) <= ID_SUBTRACT) {
                char buffer1[20], buffer2[20];
                GetWindowText(input1, buffer1, 20);
                GetWindowText(input2, buffer2, 20);

                double num1 = atof(buffer1);
                double num2 = atof(buffer2);
                double result = 0.0;

                switch (LOWORD(wParam)) {
                    case ID_MULTIPLY: result = num1 * num2; break;
                    case ID_DIVIDE: 
                        if (num2 == 0) {
                            MessageBox(hwnd, "Error: Division by zero!", "Error", MB_OK | MB_ICONERROR);
                            return 0;
                        }
                        result = num1 / num2;
                        break;
                    case ID_ADD: result = num1 + num2; break;
                    case ID_SUBTRACT: result = num1 - num2; break;
                }

                char resultText[100];
                sprintf(resultText, " %f", result);
                MessageBox(hwnd, resultText, "Result", MB_OK);
            }
            break;

            break;


        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0)); // Green background
            FillRect(hdc, &ps.rcPaint, hBrush);
            DeleteObject(hBrush);
            EndPaint(hwnd, &ps);
        } break;

	

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {}; // Define window class
    HWND hwnd;
    MSG msg;

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Use white background
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindow("WindowClass", "My Calculator",
                        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, // No resizing
                        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200,
                        NULL, NULL, hInstance, NULL);

    if (!hwnd) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // DEBUG: Console message to confirm window creation
    std::cout << "Window Created Successfully" << std::endl;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}