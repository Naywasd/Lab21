#include <windows.h>

#include <stdio.h>

#include <stdlib.h>



#define ID_ADD 1

#define ID_SUB 2

#define ID_MUL 3

#define ID_DIV 4



HWND hEdit1, hEdit2;



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch(msg) {

        case WM_CREATE: {

            CreateWindow("STATIC", "Please input two numbers",

                         WS_VISIBLE | WS_CHILD | SS_CENTER,

                         20, 20, 200, 25, hwnd, NULL, NULL, NULL);



            hEdit1 = CreateWindow("EDIT", "",

                                  WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,

                                  35, 50, 170, 25, hwnd, NULL, NULL, NULL);



            hEdit2 = CreateWindow("EDIT", "",

                                  WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,

                                  35, 85, 170, 25, hwnd, NULL, NULL, NULL);



            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 50, 125, 30, 30, hwnd, (HMENU)ID_ADD, NULL, NULL);

            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 90, 125, 30, 30, hwnd, (HMENU)ID_SUB, NULL, NULL);

            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 130, 125, 30, 30, hwnd, (HMENU)ID_MUL, NULL, NULL);

            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 170, 125, 30, 30, hwnd, (HMENU)ID_DIV, NULL, NULL);

            break;

        }



        case WM_COMMAND: {

            if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {

                char buffer1[100], buffer2[100], resultStr[100];

                GetWindowText(hEdit1, buffer1, 100);

                GetWindowText(hEdit2, buffer2, 100);



                double num1 = atof(buffer1);

                double num2 = atof(buffer2);

                double result = 0;



                if (LOWORD(wParam) == ID_ADD) result = num1+num2;

                if (LOWORD(wParam) == ID_SUB) result = num1-num2;

                if (LOWORD(wParam) == ID_MUL) result = num1*num2;

                if (LOWORD(wParam) == ID_DIV) result = num1/num2;



                sprintf(resultStr, "%f", result);



                MessageBox(hwnd, resultStr, "Result", MB_OK);

            }

            break;

        }



        case WM_CTLCOLORSTATIC: {

            HDC hdcStatic = (HDC)wParam;

            SetBkColor(hdcStatic, RGB(200, 0, 100));

            SetTextColor(hdcStatic, RGB(255, 255, 255));

            return (LRESULT)CreateSolidBrush(RGB(200, 0, 100));

        }



        case WM_DESTROY: {

            PostQuitMessage(0);

            break;

        }

        default:

            return DefWindowProc(hwnd, msg, wParam, lParam);

    }

    return 0;

}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASS wc = {0};

    wc.lpszClassName = "MyCalcClass";

    wc.lpfnWndProc = WndProc;

    wc.hbrBackground = CreateSolidBrush(RGB(200, 0, 100));

    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClass(&wc);



    HWND hwnd = CreateWindow("MyCalcClass", "My Calculator",

                             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,

                             CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);



    MSG msg;

    while(GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);

        DispatchMessage(&msg);

    }

    return 0;

}
