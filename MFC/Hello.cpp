#include<afxwin.h>//包含afxwin.h头文件，引入MFC类库

//从CWinApp类中派生出一个自己定义的类
class CMyApp :public CWinApp
{
public:
	//覆盖CWinApp::InitInstance函数，因为在应用程序的生存期内InitInstance函数调用较早，在程序开始运行以后而窗口创建之前。
	//但窗口由InitInstance创建，否则应用程序不会有窗口
	
	virtual BOOL InitInstance();

};

class CMainWindow :public CFrameWnd
{
public:
	CMainWindow();
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP();
};
CMyApp myApp;


BOOL CMyApp::InitInstance()
{
	//构建一个CMainWindow对象，并赋值给应用程序对象m_pMainWnd数据成员中
	//原型 CWnd* m_pMainWnd;    // main window (usually same AfxGetApp()->m_pMainWnd)
	m_pMainWnd = new CMainWindow;

	//创建后调用ShowWindow和UpdateWindow函数
	m_pMainWnd->ShowWindow(m_nCmdShow);//m_nCmdShow为一个整数，表示窗口的状态
	m_pMainWnd->UpdateWindow();
	//如果要在MFC程序中调用Window的API,要在函数前加上全局运算符::
	//如::UpdateWindow(hWnd);
	return TRUE;
}

//消息映射
BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)//表示消息映射所属的类和该类的基类
	ON_WM_PAINT()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	/*
	virtual BOOL Create(LPCTSTR lpszClassName,   //指定窗口基于WNDCLASS类的名称
				         //设为NULL将创建一个基于有主结构注册的WNDCLASS类的默认框架窗口

				LPCTSTR lpszWindowName,          //标题栏出现的文字
				DWORD dwStyle = WS_OVERLAPPEDWINDOW, //指定窗口样式
				const RECT& rect = rectDefault,   //C中Rect结构的引用，指定窗口在屏幕的初始位置和尺寸
				CWnd* pParentWnd = NULL,        // != NULL for popups //指定父类窗口
				LPCTSTR lpszMenuName = NULL,    //窗口菜单
				DWORD dwExStyle = 0,            
				CCreateContext* pContext = NULL
				);
	*/
	Create(NULL, _T("Hello!"));
	/*
	"Hello"编译器将从ANSI字符组成该字符串
	L"Hello"编译器将使用Unicode字符
	_T("Hello")如果预处理程序符号_UNICODE，编译器将使用Unicode字符，如果没有预处理程序符号，将使用ANSI
	*/
}

void CMainWindow::OnPaint()
{
	/*
	* 专门用途的设备描述表类：（可直接实例化）
	CPaintDC  //用于在窗口客户区画图（仅限于OnPaint处理程序）
	CClientDC //用于在窗口客户区画图（除OnPaint外的任何处理程序）
	CWindowDC //用于在窗口内任意地方画图，包括非客户区
	CMetaFileDC  //用于向GDI元文件中画图
	*/
	//BeginPaint和EndPaint分别在CPaintDC等对象的构造函数和析构函数中

	//栈中构造时会自动回收，在堆中new创建时要亲自delete释放
	CPaintDC dc(this);//只能在OnPaint处理程序中使用

	//代表矩阵的CRect对象
	CRect rect;
	//CWnd::GetClientRect()
	GetClientRect(&rect);
	/*
	int DrawText(
		LPCTSTR lpchText,  //字符串指针
		int cchText,       //字符串字符数，-1时要字符串以NULL结尾
		LPRECT lprc,       //指定格式矩阵的一个RECT对象或地址
		UINT format        //显示格式
    )*/
	dc.DrawText(_T("Hello World!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	/*
	使用_T宏修饰字符串常量时要注意：
	1、将字符声明为TCHAR类型而不是char类型，如果定义了_UNICODE符号，TCHAR将求值为wchar_t，他是一个
		16为的Unicode字符。如果没有定义_UNICODE，TCHAR将变为普通的char。
	2、不要使用char*或者wchar_t*来声明TCHAR字符串的指针，而应当使用TCHAR*或者更佳的LPTSTR(指向TCHAR字符串的指针)
		和LPCTSTR(指向const TCHAR字符串的指针)数据类型
	3、一个字符不一定只有8位宽。如果要将以字节表示的缓冲区长度转变为以字符表示的缓冲区大小，可以借助sizeof(TCHAR)划分缓冲区长度。
	*/
}

