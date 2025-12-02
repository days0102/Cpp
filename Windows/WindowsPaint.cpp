// MyWindows.cpp : 定义应用程序的入口点。
//

#pragma once 

#include "framework.h"
#include "WindowsPaint.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
VOID Game_Paint(HWND hWnd);


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
    wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPAINT));
    wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszMenuName = NULL;//不显示菜单
    wndclass.lpszClassName = TEXT("MyWindows");

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("窗口创建失败"), TEXT("提示"), MB_ICONEXCLAMATION | MB_OKCANCEL);
        return 0;
    }

    HWND hWnd = CreateWindow(TEXT("MyWindows"), TEXT("MyWindows"), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 100, nullptr, nullptr, hInstance, nullptr);

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
    //获取设备环境句柄(HDC)的两种方式
    case WM_PAINT:
    {
        
        /*
        typedef struct tagPAINTSTRUCT {
        HDC         hdc;      //用于绘制的句柄
        BOOL        fErase;   //非零值则擦除背景，否则不擦除
        RECT        rcPaint;  //通过指定坐标确定一个要绘制的矩形范围
        BOOL        fRestore;        //系统预留，一般用不到
        BOOL        fIncUpdate;      //系统预留，一般用不到
        BYTE        rgbReserved[32]; //系统预留，一般用不到
        } PAINTSTRUCT, *PPAINTSTRUCT, *NPPAINTSTRUCT, *LPPAINTSTRUCT;
        */
        PAINTSTRUCT ps;
        //第一种获取方式
        /*
        * WINAPI
        BeginPaint(
            _In_ HWND hWnd,
            _Out_ LPPAINTSTRUCT lpPaint //LP意为远指针，PAINTSTRUCT为结构体
            );
        */
        HDC hdc = BeginPaint(hWnd, &ps);
        
        LineTo(hdc, 100, 100);//绘制直线
        Ellipse(hdc, 200, 200, 300, 300);
        EndPaint(hWnd, &ps);
        
        
    }
    break;
    case WM_KEYUP:
    {
        //第二种获取方法
        /*
        WINUSERAPI HDC WINAPI GetDC(_In_opt_ HWND hWnd);
        使用完之后必须及时将设备环境释放掉，不然其他应用程序就会无法使用
        int WINAPI ReleaseDC(
            _In_opt_ HWND hWnd,
            _In_ HDC hDC
            );
        */
        HDC hdc = GetDC(hWnd);
        Rectangle(hdc, 100, 100, 200, 50);
        //使用函数ValidateRect更新指定窗口的无效矩形区域
        /*
        BOOL WINAPI ValidateRect(
            _In_opt_ HWND hWnd,           //表示一个想要改变状态的窗口，若为NULL则更新所有窗口,然后函数返回前发送WM_ERASEBKGND和WM_NCPAINT消息个回调函数
            _In_opt_ CONST RECT *lpRect   //指向一个包含需要生效的矩阵的更新区域坐标的RECT结构体，若为NULL,所有客户区域将会生效
            );
        */
        ValidateRect(hWnd, nullptr);
        ReleaseDC(hWnd, hdc);//释放环境句柄
        Game_Paint(hWnd);
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

//画笔是线条的样式，画刷是封闭图形内部填充的样式
//在GDI中，系统预设的画笔样式为BLACK_PEN，预设画刷为NULL_BRUSH
VOID Game_Paint(HWND hWnd)
{
    //创建画笔，HPEN是画笔的句柄类型，用于标识一个画笔对象
    //使用CreatePen函数创建画笔
    /*
    HPEN WINAPI CreatePen(
        _In_ int iStyle,     //画笔样式
        //微软定义的样式：PS_SOLID(实线),PS_DASH(短虚线),PS_DOT(点虚线),PS_DASHDOT(短线和点间隔),PS_DASHDOTDOT(短线间间隔)

        _In_ int cWidth,     //线条宽度
        _In_ COLORREF color  //线条颜色
        );
    */

    /*
    COLORREF类型是一个32位整型数值，代表一种颜色，通常使用RGB宏来定义
    COLORREF RGB(
        BYTE byRed,    //颜色的红色分量值，在0~255之间
        BYTE byGreen,  //颜色的录色分量值，在0~255之间
        BYTE byBlue    //颜色的蓝色分量值，在0~255之间
        );
    */
    COLORREF Colorred = RGB(255, 0, 0);//红色
    COLORREF Colorblue = RGB(0, 0, 255);
    HPEN Bluepen = CreatePen(PS_SOLID, 20, Colorblue);
    //另外可以使用ExtCreatePen函数和CreatePenIndirect函数来创建画笔

    //创建画刷
    //使用函数CreateSolidBrush或CreateHatchBrush
    /*
    * 实心画刷
    HBRUSH  WINAPI CreateSolidBrush( _In_ COLORREF color//指定画刷的颜色);

    * 阴影画刷
    HBRUSH  WINAPI CreateHatchBrush( 
        //HS_BDIAGONAL:表示45度向上，从左至右的阴影
        //HS_CROSS:水平和垂直交叉阴影
        //HS_DIAGCROSS:45度交叉阴影
        //HS_FDIAGONAL:表示45度向下，从左至右的阴影
        //HS_HORIZONTAL:水平阴影
        //HS_VERTICAL:垂直阴影
        _In_ int iHatch,     //阴影样式
        _In_ COLORREF color  //前景色颜色值
        );
    */
    HBRUSH RedBrush = CreateHatchBrush(HS_VERTICAL, Colorred);


    //图形对象的选择
    /*
    * 一个设备环境中同一时刻只能有一个画笔对象
    * HGDIOBJ WINAPI SelectObject(
        _In_ HDC hdc,    //环境设备句柄（需要使用该函数的句柄）
        _In_ HGDIOBJ h   //被选用对象的句柄（GDI对象，画笔画刷位图字体区域及调色板）
        );
    */
    HDC hdc = GetDC(hWnd);
    HGDIOBJ obj = SelectObject(hdc, RedBrush);

    //绘制图形和线条

    //绘制线条通常使用函数LineTo或MoveToEx
    /*
    * 不能指定起点，在画笔当前点开始画
    * BOOL WINAPI LineTo( 
        _In_ HDC hdc,  //设备环境句柄
        _In_ int x,    //线条终点x坐标
        _In_ int y     //线条终点y坐标
        );
    */
    LineTo(hdc, 100, 100);

    /*
    * 移动画笔的当前点
    * BOOL  WINAPI MoveToEx(
        _In_ HDC hdc,          //设备上下文句柄
        _In_ int x,            //新位置的X坐标
        _In_ int y,            //新位置的Y坐标
        //LPPOINT是一个指向POINT结构的指针，用来存放上一个点的位置，若为NULL则不保存上个点的位置
        _Out_opt_ LPPOINT lppt
        );
    */

    //绘制矩阵
    /*
    * BOOL WINAPI Rectangle(
        _In_ HDC hdc,    
        _In_ int left,    //矩阵左上角X坐标
        _In_ int top,     //矩阵左上角Y坐标
        _In_ int right,   //矩阵右下角X坐标
        _In_ int bottom   //矩阵右下角Y坐标
        );
    */
    Rectangle(hdc, 20, 20, 50, 50);

    //删除GDI对象
    /*
    * BOOL WINAPI DeleteObject( _In_ HGDIOBJ ho//要删除的GDI句柄);
    */
    DeleteObject(obj);
    ReleaseDC(hWnd, hdc);
}