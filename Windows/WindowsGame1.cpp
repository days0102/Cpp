// WindowsGame1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsGame1.h"
#include<playsoundapi.h>

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//_In_字样可以理解为一个宏，表示需要我们进行自行输入的一个参数
//与之对应的是_Out，表示指定的这个参数是函数本身向外输出的一个参数
//多了_opt说明参数是可选的。表示这个参数我们可以自己填内容，不填具体内容的话直接填NULL也行。
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,//MSDN中表示在Win32环境下总是取NULL
                     _In_ LPWSTR    lpCmdLine,//他是一个一空终止的字符串，指定传递个运行程序的命令行参数
                     _In_ int       nCmdShow)//表示窗口应该如何显示
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSGAME1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSGAME1));

    

    MSG msg;

    // 主消息循环:
    //也可以使用PeekMessage函数,该函数能取到消息会放回非零值
    //GetMessage接到WM_PAINT返回零
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    //WNDCLASSEXW是WNDCLASS的升级版
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);//表示该结构体的字节数大小

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;//他是一个函数指针，指向窗口的回调函数
    wcex.cbClsExtra     = 0;      //表示窗口类附加内存，一般设置为零
    wcex.cbWndExtra     = 0;      //表示窗口的附加内存，一般设置为零
    wcex.hInstance      = hInstance;//把WinMain中的实例句柄传给他
    /*
    HICON WINAPI loadIcon(_In_opt HINSTANCE hInstance,_In_ LPCTSTR lpIconName);
    用于加载图标资源，如果加载的是系统图标第一个参数必须是NULL
    */
    //wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSGAME1));
    //通常是用LoadImage()函数来从文件直接加载一个图标资源
    //从全局的::LoadImage函数从本地加载自定义的图标
    wcex.hIcon =(HICON)::LoadImage(NULL, _T("D:\\BaiduNetdiskDownload\\那些花儿\\bg.png"), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    //可以调用GetStockObject函数来获得系统的标准画刷
    /*
    HGDIOBJ GetStockObject(_In_ int fnObject);
    参数指定要获取的对象的类型，这个函数也可以获取画笔、字体和调色板的句柄
    */
    //wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);//窗口背景置为灰色
    wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSGAME1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));//指定窗口类的小图标句柄

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
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      //MessageBox()函数
       MessageBox(nullptr, TEXT("创建窗口失败"), TEXT("提示"),MB_OK);
       return FALSE;
   }
   
   MessageBox(nullptr, TEXT("创建窗口成功"), TEXT("提示"), MB_OK);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);//发送一条WM_PAINT消息


    //改变窗口位置与大小
    /*
    BOOL WINAPI MoveWindow(
        _In_ HWND hWnd,      //窗口句柄
        _In_ int X,          //窗口左方相对屏幕左上角的新位置
        _In_ int Y,          //窗口上方相对屏幕左上角的新位置
        _In_ int nWidth,     //窗口的新宽度
        _In_ int nHeight,    //窗口的新高度
        _In_ BOOL bRepaint); //指定是否要重画窗口,为真消息处理函数会收到WM_PAINT消息
    */
   Sleep(1000);
   MoveWindow(hWnd, 200, 50, 800, 600, true);//窗口左上角位于屏幕坐标（200，50）处

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

//WPARAM类型的两个参数会随着消息类型的不同而不同
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
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
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
