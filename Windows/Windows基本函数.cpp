
#include <windows.h>

//窗口回调函数
LRESULT CALLBACK WndProc(
	HWND,    //当前窗口句柄(相当于unsigned long类型)
	UINT,    //无符号整数类型(相当于unsigned int),代表所处理消息的消息值
	WPARAM,  //消息的附加参数,相当于UINT
	LPARAM   //消息的附加参数,相当于LONG
	);

//入口函数,必须返回一个int型的值
int WINAPI WinMain(
	HINSTANCE hInstance,//应用程序当前实例句柄
	HINSTANCE hPrevInstance,//引用程序其他实例句柄
	PSTR szCmdLine, //指向程序命令行参数的指针
	int iCmdShow)  //应用程序开始执行时窗口显示方式的整数值
{
	/*
	窗口类定义
	typedef struct tagWNDCLASSW {
    UINT        style;         //窗口类的样式，一般设置为0（用或的方式组合）
    WNDPROC     lpfnWndProc;   //指向窗口函数的指针（最重要的一个参数）
    int         cbClsExtra;    //分配在窗口类结构后的字节数
    int         cbWndExtra;    //分配在窗口实例后的字节数
    HINSTANCE   hInstance;     //定义窗口类的应用程序的实例句柄
    HICON       hIcon;         //窗口类的图标（窗口左上角的那图标）
    HCURSOR     hCursor;       //窗口类的光标
    HBRUSH      hbrBackground; //窗口类的背景刷
    LPCWSTR     lpszMenuName;  //窗口类的菜单名
    LPCWSTR     lpszClassName; //窗口类名（必须给的类名）
	}WNDCLASSW;
	*/

	//TCHAR可自动变成字符串或宽字节型字符串
	static TCHAR szAppName[] = TEXT("MyWindows");

	//初始化窗口类
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;//这些CS为前缀的标识符在winuser.h中定义
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//使用LoadIcon()函数载入图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//使用LoadCursor()函数载入鼠标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//指定窗口的背景色，GetStockObject()获取Windows标准的刷子
	wndclass.lpszMenuName = NULL;//说明窗口类的菜单，NULL为不设菜单
	wndclass.lpszClassName = szAppName;//必须给的类名

	//函数RegisterClass()用于注册窗体类
	if (!RegisterClass(&wndclass))
	{
		//MessageBox()函数返回所按下按钮的ID值,即Windows用一个无符号整数唯一表示某个资源(对话框、按钮、菜单等)
		/*
		四个参数:
		1.该窗口的父窗口,NULL为没有父窗口
		2.对话框要显示的字符串
		3.对话框标题栏上要显示的字符串
		4.对话框中显示的按钮及风格
		*/
		//MB为前缀的参数表示按钮类型表或图标类型表
		/*
		按钮类型表:
		MB_ABORTRETRYIGNORE   //消息框中显示Abort,Retry,Ignore按钮
		MB_OK                 //消息框显示OK按钮
		MB_OKCANCEL           //消息框显示OK,Cancel按钮
		MB_RETRYCANCEL        //消息框显示Retry,Cancel按钮
		MB_YESNO              //消息框显示Yes,No按钮
		MB_YESNOCANCEL        //消息框显示Yes,No,Cancel按钮

		图标类型表:
		MB_ICONEXCLAMATION    //显示一个感叹号,表示警告
		MB_ICONINFORMATION    //显示一个i图标,表示提示
		MB_ICONSTOP           //显示手形图标,表示 警告或严重错误
		MB_ICONQUESTION       //显示问号图标,表示疑问
		MB_ICONERROR          //显示一个错误图标
		*/
		MessageBox(NULL, TEXT("这个程序需要在 Windows NT 才能执行！"), szAppName, MB_ICONERROR);
		return 0;
	}

	/*
	CreateWindow()函数的声明式
	CreateWindow(
    LPCTSTR lpClassName, //窗口类名
    LPCSTR lpWindowName, //窗口标题名称
    DWORD dwStyle,       //窗口样式
    int X,               //窗口左上角横坐标
    int Y,               //窗口左上角纵坐标
    int nWidth,          //窗口宽度
    int nHeight,         //窗口高度
    HWND hWndParent,     //该窗口的父窗口句柄
    HMENU hMenu,         //窗口主菜单句柄
    HINSTANCE hInstance, //创建窗口的应用程序当前句柄
    LPVOID lpParam);     //指向一个传递给窗口的参数值的指针
	*/
	HWND hwnd = CreateWindow(szAppName,
		TEXT("贪食🐍"),

		/*
		常用窗口样式
		WS_OVERLAPPED   //带有标题栏和边界的重叠式窗口,类似WS_TILED类型
		WS_CAPTION      //有标题栏的窗口(包括WS_BORDER样式)
		WS_SYSMENU      //标题栏上有窗口菜单的窗口,WS_CAPTION必须也被指定
		WS_THICKFRAME   //边界可以变化的窗口
		WS_MINIMIZEBOX  //具有最小化按钮的窗口,不能和WS_EX_CONTEXTHELP样式合用。WS_SYSMENU必须指定
		WS_MAXIMIZEBOX  //具有最大化按钮的窗口,不能和WS_EX_CONTEXTHELP样式合用。WS_SYSMENU必须指定
		WS_MINMIZE      //开始就最小化的窗口
		WS_MANMIZE      //开始就最大化的窗口
		WS_ICONIC       //开始就最小化的窗口

		WS_POPUP        //弹出式窗口
		WS_BORDER       //有细线边界的窗口
		WS_SYSMENU      //标题栏上有窗口菜单的窗口,WS_CAPTION必须也被指定
		
		WS_SIZEBOX      //边界可以变化的窗口,和WS_THICKFRAME类型类似
		WS_CHILD

		WS_OVERLAPPEDWINDOW //带有WS_OVERLAPPED、WS_CAPTION、WS_SYSMENU、WS_THICKFRAME、WS_MINIMIZEBOX和WS_MAXIMIZEBOX样式的重叠窗口
		*/
		WS_OVERLAPPEDWINDOW,
		//也可用GetSysMetrics()函数获取注册窗口的尺寸用于创建窗口
    		//int width = GetSystemMetrics(SM_CXSCREEN);
    		//int height = GetSystemMetrics(SM_CXSCREEN);
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	//显示窗口
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//消息循环
	/*
	MSG 结构体
	HWND        hwnd;		主窗口句柄
	UINT        message;	具体的消息
	WPARAM      wParam;		附加消息，通常是键盘消息
	LPARAM      lParam;		附加消息，通过是鼠标消息
	DWORD       time;		消息产生的时间
	POINT       pt;			附加消息，鼠标坐标信息
	*/
	MSG msg;//定义一个MSG类型的变量
	//GetMessage()取消息成功的话会返回一个非零值
	/*
	GetMessage(LPMSG ,HWND ,UINT ,UINT );
	参数:
	1.存放消息的MSG结构指针
	2.接收消息的窗口句柄
	3.表示要获取的最大消息值
	4.表示要获取的最小消息值
	*/
	while (GetMessage(&msg, NULL, 0, 0))//产生一个消息循环,从消息队列中取消息,遇到VW_QUIT则退出
	{
		/*
		TranslateMessage()函数负责键盘消息转换
		击键消息除字符键消息外,其他击键操作产生的虚拟消息(包括WM_KEYDOWN、
		WMKEYUP、WM_SYSKEYDOWN、WM_SYSKEYUP都必须转换成字符消息程序才能响应)
		*/
		TranslateMessage(&msg);//翻译消息,键盘消息传递

		/*
		DispatchMessage()函数负责将消息派送到相应的窗口函数
		它根据MSG结构中的HWND句柄成员找到相应的窗口类,然后根据注册窗口时WNDCLASS类结构
		找到相应的窗口函数WndPorc()
		*/
		DispatchMessage(&msg); //将消息传递给窗口函数,以便处理相应的消息
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)//根据消息值转相应的消息处理
	{
	case WM_PAINT://重画窗口客户区消息

		HDC hdc;//设备环境句柄类型,相当于unsigned long
		PAINTSTRUCT ps;
		RECT rect;

		/*
		BeginPaint 函数为指定窗口进行绘画作准备，并用将和绘画有关的信息填充到一个 PAINTSTRUCT 结构中
		
		HDC BeginPaint(
			HWND hwnd,            //需要重新绘制的窗口句柄
			LPPAINTSTRUCT lpPaint //指向 PAINTSTRUCT 结构的指针，用于存放绘画相关的信息
		);

		1. 如果函数成功，返回值是指定窗口的“显示设备描述表”句柄；
		2. 如果函数失败，返回值是 NULL，表明没有得到显示设备的内容。
		*/
		hdc = BeginPaint(hwnd, &ps);//获取要重画窗口的设备描述句柄
		/*
		GetClientRect用于取得指定窗口的客户区域大小。
		用于显示内容的区域叫Client区（客户区），
		NonClient（非客户区）用于显示命令按钮及窗口标题等。
		BOOL GetClientRect(
			HWND hWnd, // 窗口句柄
			LPRECT lpRect //是一个指针，指向一个RECT类型的rectangle结构。
			//该结构有四个LONG字段,分别为left、top、right和bottom。
			//GetClientRect将这四个字段设定为窗口显示区域的尺寸。
			//left和top字段通常设定为0。right和bottom字段设定为显示区域的宽度和高度（像素点数）。
			//也可以是一个CRect对象指针。CRect对象有多个参数，与RECT用法相同。
		);
		函数的作用总的来说就是把客户区的大小写进第二个参数所指的Rect结构当中
		*/
		GetClientRect(hwnd, &rect);
		/*
		*DrawText()函数的功能是在指定的矩形里写入格式化文本，根据指定的方法对文本格式化（扩展的制表符，字符对齐、折行等）
		int DrawText(
		HDC hDC,          // 设备描述表句柄
		LPCTSTR lpString, // 将要绘制的字符串
		int nCount,       // 字符串的长度(字符串以\0结束用-1会自动计算)
		LPRECT lpRect,    // 指向矩形结构RECT的指针
		UINT uFormat      // 正文的绘制选项
		);
		调用成功返回正文的高度,调用失败返回0
		*/
		DrawText(hdc, TEXT("大家好，这是我的第一个窗口程序！"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		//也可用TextOut()函数,客户区坐标(20,60)处显示文本,限制为35个字母
		//TextOut(hdc, 20, 60, TEXT("The First Windows Application Showing Window!"), 35);
		/*
		EndPaint函数标记指定窗口的绘画过程结束；这个函数在每次调用BeginPaint函数之后被请求，但仅仅在绘画完成以后。
		BOOL EndPaint(
			HWND hWnd,                  // handle to window
			CONST PAINTSTRUCT *lpPaint  // paint data
		);
		参数：
		hWnd：[输入]已经被重画的窗口的HANDLE
		lpPaint：[输入]指向一个PAINTSTRUCT结构，该结构包含了绘画信息，是BeginPaint函数返回的
		返回值：
		返回值始终是非0*/
		EndPaint(hwnd, &ps);//结束要重画的窗口
		return 0;

	//关闭窗口时,系统会发出WM_CLOSE,窗口函数不拦截此消息,由DefWindowProc()函数处理
	//DefWindowProc()收到WM_CLOSE后,调用函数DestroyWindow()把窗口消除
	//函数DestroyWindow()本身又会发出WM_DESTROY,程序对WM_DESTROY反应是调用PostQuitMessage()函数
	//PostQuitMessage()函数只发出WM_QUIT消息,使消息循环结束
	case WM_DESTROY://撤销窗口消息
		PostQuitMessage(0);//产生退出程序消息VW_QUIT
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);//其他转默认函数窗口
}
