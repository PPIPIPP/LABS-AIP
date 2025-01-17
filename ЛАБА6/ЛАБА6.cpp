#include <windows.h>
#include <iostream>

enum Shape { RECTANGLE, CIRCLE };


Shape currentShape = RECTANGLE; 
POINT startPoint;
bool drawing = false; 


void drawRectangle(HDC hdc, POINT start, POINT end) 
{
    Rectangle(hdc, start.x, start.y, end.x, end.y);
}


void drawCircle(HDC hdc, POINT start, POINT end) 
{
    int radius = static_cast<int>(sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2)));
    Ellipse(hdc, start.x - radius, start.y - radius, start.x + radius, start.y + radius);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    switch (msg) 
    {
    case WM_CREATE: 
    {
       
        break;
    }
    case WM_LBUTTONDOWN: 
    {
     
        startPoint.x = LOWORD(lParam);  
        startPoint.y = HIWORD(lParam);  
        drawing = true; 
        break;
    }
    case WM_MOUSEMOVE: 
    {
     
        if (drawing) 
        {
            HDC hdc = GetDC(hwnd);
            POINT currentPoint = { LOWORD(lParam), HIWORD(lParam) };

           
            InvalidateRect(hwnd, NULL, TRUE);

       
            if (currentShape == RECTANGLE) 
            {
                drawRectangle(hdc, startPoint, currentPoint);
            }
            else if (currentShape == CIRCLE) 
            {
                drawCircle(hdc, startPoint, currentPoint);
            }
            ReleaseDC(hwnd, hdc);
        }
        break;
    }
    case WM_LBUTTONUP: 
    {

        if (drawing) 
        {
            HDC hdc = GetDC(hwnd);
            POINT endPoint = { LOWORD(lParam), HIWORD(lParam) };


            if (currentShape == RECTANGLE) 
            {
                drawRectangle(hdc, startPoint, endPoint);
            }
            else if (currentShape == CIRCLE) 
            {
                drawCircle(hdc, startPoint, endPoint);
            }
            ReleaseDC(hwnd, hdc);
            drawing = false;
        }
        break;
    }
    case WM_KEYDOWN: 
    {

        if (wParam == 'R') {
            currentShape = RECTANGLE; 
        }
        else if (wParam == 'C') {
            currentShape = CIRCLE; 
        }
        break;
    }
    case WM_PAINT: 
    {
        
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int main() 
{
   
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"DrawingApp";

    if (!RegisterClass(&wc)) 
    {
        std::cout << "Ошибка регистрации класса окна!" << std::endl;
        return 1;
    }

  
    HWND hwnd = CreateWindowEx(
        0,
        L"DrawingApp",
        L"Рисование фигур",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, wc.hInstance, NULL
    );

    if (hwnd == NULL) 
    {
        std::cout << "Ошибка создания окна!" << std::endl;
        return 1;
    }

   
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);

    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
