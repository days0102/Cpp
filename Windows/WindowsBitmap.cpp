// WindowsBitmap.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsBitmap.h"

//添加使用TransparentBlt函数所需的库文件
#pragma comment(lib,"Msimg32.lib")

#define MAX_LOADSTRING 100

VOID Game_Paint(HWND hWnd);

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSBITMAP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSBITMAP));

    MSG msg;

    // 主消息循环:
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSBITMAP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(GetStockObject(GRAY_BRUSH));
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
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
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //调用绘画的函数
   Game_Paint(hWnd);

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
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
        
            //EndPaint(hWnd, &ps);
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

VOID Game_Paint(HWND hWnd)
{
    //1、加载位图
    //使用函数LoadImage
    /*
    HANDLE WINAPI LoadImage(
        _In_opt_ HINSTANCE hInst, //来源实例句柄，若从硬盘文件或资源文件中加载，这个参数为NULL
        _In_ LPCWSTR name,        //名称，被加载资源所在路径与文件名
        _In_ UINT type,           //加载的类型，被加载图像的类型（bmp(IMAGE_BITMAP),cur(IMAGE_CUSOR),ico(IMAGE_ICON)三种）
        _In_ int cx,              //指定存储的宽度，如果为0，表示运用系统预设的SM_CXICON或SM_CXCURSOR值来设定
        _In_ int cy,              //指定存储的高度，如果为0，表示运用系统预设的SM_CXICON或SM_CXCURSOR值来设定
        _In_ UINT fuLoad          //加载的方式，如果是从文件中加载图像，要设成LR_LOADFROMFILE
        );
    */
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"D:\\Dataset\\dota.bmp", IMAGE_BITMAP, 800, 600, LR_LOADFROMFILE);
    /*if (!hBitmap)
    {
        MessageBox(NULL, TEXT("错误"), TEXT("提示"), MB_OK);
        return;
    }*/
    HDC hdc = GetDC(hWnd);

    //建立兼容DC（相当于中转站的作用）
    //创建一个和设备环境兼容的内存设备环境(内存DC)暂时存放位图对象
    /*
    HDC WINAPI CreateCompatibleDC( _In_opt_ HDC hdc);
    */
    //如果参数为空，函数将创建一个与运行程序使用的当前显示器相兼容的DC
    HDC mdc=CreateCompatibleDC(hdc);

    //选用位图对象
    SelectObject(mdc, hBitmap);

    //进行贴图
    /*
    * BOOL  WINAPI BitBlt( 
        _In_ HDC hdc,       //目标设备环境句柄
        _In_ int x,         //目的DC的X坐标
        _In_ int y,         //目的DC的Y坐标
        _In_ int cx,        //贴到目的DC的宽度
        _In_ int cy,        //贴到目的DC的高度
        _In_opt_ HDC hdcSrc,//源设备环境句柄
        _In_ int x1,        //来源DC的X坐标
        _In_ int y1,        //来源DC的Y坐标
        _In_ DWORD rop      //贴图方式
        );
    */
    //SRCCOPY表示将源矩阵区域直接拷贝到目标矩阵区域
    BitBlt(hdc, 0, 0, 800, 600, mdc, 0, 0, SRCCOPY);//在(0,0)处贴图，贴出(800,600)尺寸的图来


    //透明遮罩法贴图（遮罩图和素材图可使用PS进行处理获得）
    //使用BitBlt函数结合光栅操作码实现
    //1.对遮罩图进行AND运算
    HBITMAP chbitmap = (HBITMAP)LoadImage(NULL, L"D:\\Dataset\\character1b.bmp", IMAGE_BITMAP, 300, 200, LR_LOADFROMFILE);
    SelectObject(mdc, chbitmap);
    BitBlt(hdc, 100, 100, 300, 200, mdc, 0, 0, SRCAND);
    //2.对素材图进行OR运算
    chbitmap = (HBITMAP)LoadImage(NULL, L"D:\\Dataset\\character1a.bmp", IMAGE_BITMAP, 300, 200, LR_LOADFROMFILE);
    SelectObject(mdc, chbitmap);
    BitBlt(hdc, 100, 100, 300, 200, mdc, 0, 0, SRCPAINT);


    //透明色彩法贴图
    /*
    * BOOL WINAPI TransparentBlt(
        _In_ HDC hdcDest,      //目标设备的句柄
        _In_ int xoriginDest,  //目标矩阵左上角的X坐标
        _In_ int yoriginDest,  //目标矩阵左上角的X坐标
        _In_ int wDest,        //目标矩阵的宽度
        _In_ int hDest,        //目标矩阵的高度
        _In_ HDC hdcSrc,       //源设备环境的句柄
        _In_ int xoriginSrc,   //源矩阵左上角的X坐标
        _In_ int yoriginSrc,   //源矩阵左上角的Y坐标
        _In_ int wSrc,         //源矩阵的宽度
        _In_ int hSrc,         //源矩阵的高度
        _In_ UINT crTransparent//指定视为透明的RGB颜色值
        );

    */
    //如果是32位的位图可能会达不到效果，32位可以使用AlphaBlend函数
    chbitmap = (HBITMAP)LoadImage(NULL, L"D:\\Dataset\\character1a24.bmp", IMAGE_BITMAP, 350, 350, LR_LOADFROMFILE);
    SelectObject(mdc, chbitmap);
    TransparentBlt(hdc, 200, 200, 350, 350, mdc, 0, 0, 350, 350, RGB(0, 0, 0));

    //使用完内存DC后要释放内存DC
    /*
    BOOL WINAPI DeleteDC( _In_ HDC hdc);
    */
    DeleteDC(mdc);
    DeleteObject(hBitmap);
    ReleaseDC(hWnd,hdc);
}
