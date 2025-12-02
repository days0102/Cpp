// WindowsGame2.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsGame3.h"
//#include<string.h>
#pragma comment(lib,"Msimg32.lib")

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

VOID Game_Paint(HWND);
BOOL Game_Clean(HWND);
BOOL Game_Init(HWND);


HDC hdc = nullptr;
HDC mdc = nullptr;
HDC bdc = nullptr;//背景
int num = 0;
HWND hWnd = nullptr;
DWORD now = 0, pre = 0;
HBITMAP bg = nullptr;
HBITMAP people = nullptr;
int x = 0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    MSG msg;


    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {

        TranslateMessage(&msg);
        DispatchMessage(&msg);

        //循环动画显示
        /*
        * DWORD WINAPI GetTickCount(VOID);//取得系统开始到目前经过的时间
        * 单位为毫秒
        */
        now = GetTickCount();
        if (now - pre >= 100)
        {
            Game_Paint(hWnd);
        }
    }
    return (int)msg.wParam;
}

//
//  函数: MyRegisterClass()
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSGAME3));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(GetStockObject(GRAY_BRUSH));
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = TEXT("WindowsGame");
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    MyRegisterClass(hInstance);

    hWnd = CreateWindow(TEXT("WindowsGame"), TEXT("Game"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        MessageBox(nullptr, TEXT("创建窗口失败"), TEXT("提示"), MB_OKCANCEL);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    Game_Init(hWnd);

    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//  目标: 处理主窗口的消息。
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL Game_Init(HWND hWnd)
{
    hdc = GetDC(hWnd);
    bdc = CreateCompatibleDC(hdc);
    mdc = CreateCompatibleDC(hdc);
    bg = (HBITMAP)LoadImage(nullptr, L"D:\\BaiduNetdiskDownload\\【配套源代码】逐梦旅程：Windows游戏编程之从零开始\\2.篇章二：初探 • GDI 2D游戏编程\\第6章\\GDIdemo8\\GDIdemo8\\bg.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
    people = (HBITMAP)LoadImage(nullptr, L"D:\\BaiduNetdiskDownload\\【配套源代码】逐梦旅程：Windows游戏编程之从零开始\\2.篇章二：初探 • GDI 2D游戏编程\\第6章\\GDIdemo8\\GDIdemo8\\goright.bmp", IMAGE_BITMAP, 480, 108, LR_LOADFROMFILE);
    return TRUE;
}
VOID Game_Paint(HWND hWnd)
{
    if (num == 8)
        num = 0;
    //贴背景
    SelectObject(bdc, bg);
    BitBlt(hdc, 0, 0, 800, 600, bdc, 0, 0, SRCCOPY);
    SelectObject(mdc, people);
    TransparentBlt(hdc, x, 350, 60, 108, mdc, num*60, 0, 60, 108, RGB(255,0,0));
    pre = GetTickCount();
    num++;
    x += 10;
    if (x >= 800)
        x -= 60;
}
BOOL Game_Clean(HWND hWnd)
{
    
    DeleteDC(mdc);
    ReleaseDC(hWnd, hdc);
    return TRUE;
}