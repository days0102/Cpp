// MyWindows.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "MyWindows.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   PSTR    lpCmdLine,
                   int       nCmdShow)
{
    WNDCLASS wndclass;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYWINDOWS));
    wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszMenuName = NULL;//不显示菜单
    wndclass.lpszClassName = TEXT("MyWindows");

    
    if (!RegisterClass(&wndclass))
    {

        MessageBox(NULL, TEXT("窗口创建失败"), TEXT("提示"), MB_ICONEXCLAMATION);
        return 0;
    }
    //获取窗口的尺寸用于创建窗口
    //int width = GetSystemMetrics(SM_CXSCREEN);
    //int height = GetSystemMetrics(SM_CXSCREEN);
    
    HWND hWnd = CreateWindow(TEXT("MyWindows"), TEXT("MyWindows"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0 , CW_USEDEFAULT, 100, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
    }
    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:       
        PostQuitMessage(0);
        break;
 
    /*
    假如Caps Lock没有锁定，按下再释放A，相应窗口过程会接收：
    1）WM_KEYDOWN：’Ａ‘　的虚拟键代码（0x41)
    2）WM_CHAR：  'a'的字符编码(0x61)
    3）WM_KEYUP： 'A' 的虚拟键代码(0x41)

    按下Shift+A，释放A，再释放Shift：
    1）WM_KEYDOWN：虚拟键代码VK_SHIFT(0x10)
    2）WM_KEYDOWN：’Ａ‘　的虚拟键代码（0x41)
    3）WM_CHAR：  'A' 的字符编码(0x41)
    4）WM_KEYUP： 'A' 的虚拟键代码(0x41)
    5）WM_UP：虚拟键代码VK_SHIFT（0x10)

    连续按住A：
    1）WM_KEYDOWN：’Ａ‘　的虚拟键代码（0x41)
    2）WM_CHAR：  'a'的字符编码(0x61)
    3）WM_KEYDOWN：’Ａ‘　的虚拟键代码（0x41)
    4）WM_CHAR：  'a'的字符编码(0x61)
    ……
    n）WM_KEYUP： 'A' 的虚拟键代码(0x41)
    */
    /*
    //键盘消息
    WM_KEYDOWN     //非系统按键
    WM_KEYUP       //非系统键释放
    WM_SYSKEYDOWN  //系统按键（Alt和F10两个系统键）
    WM_SYSKEYUP    //系统按键释放
    */
    case WM_KEYDOWN:
        /*
        WM_KEYUP参数：
        1.wParam:非系统键的虚拟键代码。Virtual-Key代码
        2.lParam:重复次数、扫描代码、扩展键标志、上下文代码、上一个键状态标志和转换状态标志
        */
        /*
        Virtual-Key代码:
        0x30   0键
        0x31   1键
        0x32   2键
        ......
        0x39   9键
        0x41   A键
        0x42   B键
        ......
        0x59   Y键
        0x5A   Z键
        VK_NUMPAD0    0x60     数字键盘0键
        VK_NUMPAD1    0x61     数字键盘1键
        VK_NUMPAD2    0x62     数字键盘2键
        ......
        VK_NUMPAD9    0x69     数字键盘9键
        VK_LBUTTON    0x01     鼠标左键(不在WM_KEYDOWN中)
        VK_RBUTTON    0x02     鼠标右键(不在WM_KEYDOWN中)
        VK_PAGEUP     PaUp键
        */
        //也可以WM_CHAR直接对应相应字符
        if(wParam==VK_SPACE)
            MessageBox(NULL, TEXT("你按下了一个按键"), TEXT("提示"), MB_OKCANCEL);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}