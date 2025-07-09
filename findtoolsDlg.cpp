
// findtoolsDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "findtools.h"
#include "findtoolsDlg.h"
#include "afxdialogex.h"
#include <tlhelp32.h>
#include "FindProcess.h"
#include "FindFiles.h"
#include "FindRemoteIP.h"
#include "CheckRegistryPathsExist.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CfindtoolsDlg 对话框



CfindtoolsDlg::CfindtoolsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINDTOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfindtoolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editShow);
}

BEGIN_MESSAGE_MAP(CfindtoolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CfindtoolsDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CfindtoolsDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CfindtoolsDlg 消息处理程序

BOOL CfindtoolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 创建字体（50 表示字号为 5 pt × 10 = 50）
	m_fontStatic.CreatePointFont(200, _T("华文琥珀"));  // 120 = 12pt
	// 设置给静态文本控件
	GetDlgItem(IDC_STATIC)->SetFont(&m_fontStatic);

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 禁止调整窗口大小
	LONG style = GetWindowLong(m_hWnd, GWL_STYLE);
	style &= ~WS_THICKFRAME;  // 移除可调整大小的边框
	SetWindowLong(m_hWnd, GWL_STYLE, style);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CfindtoolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CfindtoolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//CDialogEx::OnPaint();
		CPaintDC dc(this); // device context for painting

		CRect rect;
		GetClientRect(&rect);

		// 创建兼容的内存DC
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		// 创建兼容的位图
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

		// 加载图片
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1); 
		BITMAP bm;
		bmpBackground.GetBitmap(&bm);

		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&memDC);
		CBitmap* pOldBmp = dcBmp.SelectObject(&bmpBackground);

		// 设置高质量缩放模式
		memDC.SetStretchBltMode(HALFTONE); 
		memDC.StretchBlt(0, 0, rect.Width(), rect.Height(),
			&dcBmp, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

		// 恢复设备环境
		dcBmp.SelectObject(pOldBmp);

		// 将内存中的内容拷贝到主DC
		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		// 清理
		memDC.SelectObject(pOldBitmap);
		bitmap.DeleteObject();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CfindtoolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CfindtoolsDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CfindtoolsDlg::OnBnClickedButton1()
{
	//指定进程名
	CStringArray targetProcesses;
	targetProcesses.Add(_T("explorer.exe"));
	targetProcesses.Add(_T("firefox.exe"));
	FindProcesses(targetProcesses, m_editShow); 


	//指定路径
	CStringArray filePaths;
	filePaths.Add(_T("C:\\Windows\\notepad.exe"));
	filePaths.Add(_T("C:\\Program Files\\"));
	filePaths.Add(_T("C:\\NonExistent\\test.txt"));
	FindFiles(filePaths, m_editShow);

	//指定IP
	CStringArray expectedIPs;
	expectedIPs.Add(_T("79.133.170.11"));
	expectedIPs.Add(_T("40.79.141.153"));
	FindRemoteIP(expectedIPs, m_editShow);

	//指定注册表路径
	CStringArray registryPaths;
	registryPaths.Add(_T("Software\\Microsoft\\Windows\\CurrentVersion"));
	registryPaths.Add(_T("Software\\360"));
	registryPaths.Add(_T("Software\\NonExistent\\Test"));
	CheckRegistryPathsExist(HKEY_CURRENT_USER, registryPaths, m_editShow);


	CString oldText;
	m_editShow.GetWindowText(oldText);
	m_editShow.SetWindowText(oldText + _T("\r\n————检查完毕!————\r\n")); 
}


HBRUSH CfindtoolsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetTextColor(RGB(150, 150, 150));    //设置控件字体颜色
		pDC->SetBkMode(TRANSPARENT);   //设置透明属性
		return (HBRUSH)GetStockObject(NULL_BRUSH);   //返回空画刷
	}
	if (pWnd->GetDlgCtrlID() == IDC_EDIT1 && nCtlColor == CTLCOLOR_EDIT)
	{
		pDC->SetBkColor(RGB(255, 255, 255));     // 设置文字背景色
		pDC->SetTextColor(RGB(0, 0, 0));         // 设置文字颜色（可选）
		return (HBRUSH)::GetStockObject(WHITE_BRUSH); // 返回白色画刷
	}
}
