#include <windows.h>
#include <stdio.h>


#define ID_BTN_ADD 1
#define ID_BTN_SUB 2
#define ID_BTN_MUL 3
#define ID_BTN_DIV 4
 

HWND hEdit1, hEdit2;


void RunCalculation(HWND hwnd, int operation) {
    char t1[100], t2[100], resStr[100];
    GetWindowText(hEdit1, t1, 100);
    GetWindowText(hEdit2, t2, 100);

    double x = atof(t1);
    double y = atof(t2);
    double result = 0;

    if (operation == ID_BTN_ADD) result = x + y;
    else if (operation == ID_BTN_SUB) result = x - y;
    else if (operation == ID_BTN_MUL) result = x * y;
    else if (operation == ID_BTN_DIV) {
        if (y != 0) result = x / y;
        else {
            MessageBox(hwnd, "Error: Divide by Zero", "Result", MB_OK | MB_ICONERROR);
            return;
        }
    }

    sprintf(resStr, "%f", result);
    MessageBox(hwnd, resStr, "Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {
        
        case WM_CREATE: {
           
            CreateWindow("STATIC", "Please input numbers", WS_VISIBLE | WS_CHILD, 25, 10, 200, 20, hwnd, NULL, NULL, NULL);

            
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 25, 40, 185, 25, hwnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 25, 75, 185, 25, hwnd, NULL, NULL, NULL);

           
            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 25, 115, 40, 30, hwnd, (HMENU)ID_BTN_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 75, 115, 40, 30, hwnd, (HMENU)ID_BTN_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 125, 115, 40, 30, hwnd, (HMENU)ID_BTN_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 175, 115, 40, 30, hwnd, (HMENU)ID_BTN_DIV, NULL, NULL);
            break;
        }

        case WM_COMMAND: {
            
            int wmId = LOWORD(wParam);
            if (wmId >= 1 && wmId <= 4) {
                RunCalculation(hwnd, wmId);
            }
            break;
        }

        case WM_DESTROY: {
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
    MSG msg;

    memset(&wc,0,sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc;
    wc.hInstance     = hInstance;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    
    wc.hbrBackground = CreateSolidBrush(RGB(50, 205, 50)); 
    
    wc.lpszClassName = "MyCalculatorClass";
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "MyCalculatorClass", "My Calculator", 
        WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, 
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}