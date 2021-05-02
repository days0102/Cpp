// WindowsGame2.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsGame2.h"
//#include<string.h>


// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

VOID Game_Paint(HWND);
BOOL Game_Clean(HWND);
BOOL Game_Init(HWND);

HBITMAP picture[5];
HDC hdc = nullptr;
HDC mdc = nullptr;
int num = 0;
HWND hWnd = nullptr;
DWORD now = 0, pre = 0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
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

    return (int) msg.wParam;
}

//
//  函数: MyRegisterClass()
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSGAME2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(GetStockObject(GRAY_BRUSH));
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = TEXT("WindowsGame");
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   //创建定时器
   /*
   * UINT_PTR WINAPI SetTimer(
        _In_opt_ HWND hWnd,            //接受定时器消息的窗口句柄
        _In_ UINT_PTR nIDEvent,        //定时器代号（在同一个窗口中必须是唯一的，且值不为零）
        _In_ UINT uElapse,             //时间间隔（单位毫秒）
        _In_opt_ TIMERPROC lpTimerFunc //处理相应函数（用于指定响应函数，为NULL时使用消息处理函数）
        );
   */
   //SetTimer(hWnd, 1, 1000, nullptr);//每1秒发出WM_TIMER消息

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
    //定时器动画显示
    case WM_TIMER://使用消息处理函数中的响应代码时要将SetTimer函数的第四个参数设为NULL
        //Game_Paint(hWnd);
        break;

    case WM_DESTROY:

        //删除定时器
        /*
        * 定时器建立后就会一直在自动运行使用，要停止定时器必须使用删除定时器函数KillTimer
        * BOOL WINAPI KillTimer(
            _In_opt_ HWND hWnd,    
            _In_ UINT_PTR uIDEvent //定时器代号
            );
        */
        //KillTimer(hWnd, 1);
        Game_Clean(hWnd);
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
    wchar_t filename[30];
    for (int i = 0; i < 5; i++)
    {
        memset(filename, 0, sizeof(filename));
        /*
        * int swprintf_s(
            wchar_t *buffer,      //宽字符型指针
            size_t sizeofBuffer,  //存储的最大字符数，可省略不填
            const wchar_t *format,//需要处理的字符串
            [argument]        //可选参数
            )
        */
        swprintf_s(filename, L"D:\\Dataset\\BMP\\%d.bmp",i);
        picture[i] = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
    }
    mdc = CreateCompatibleDC(hdc);
    num = 0;
    SetTimer(hWnd, 1, 100, nullptr);
    return TRUE;
}
VOID Game_Paint(HWND hWnd)
{
    if (num == 4)
        num = 0;
    SelectObject(mdc, picture[num]);
    BitBlt(hdc, 0, 0, 800, 600, mdc, 0, 0, SRCCOPY);
    pre = GetTickCount();
    num++;
}
BOOL Game_Clean(HWND hWnd)
{
    KillTimer(hWnd, 1);
    for (int i = 0; i < 5; i++)
    {
        DeleteObject(picture[i]);
    }
    DeleteDC(mdc);
    ReleaseDC(hWnd, hdc);
    return TRUE;
}