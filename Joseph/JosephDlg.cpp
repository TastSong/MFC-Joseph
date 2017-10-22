
// JosephDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Joseph.h"
#include "JosephDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Circle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJosephDlg 对话框



CJosephDlg::CJosephDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CJosephDlg::IDD, pParent)
	, m_HeadCount(0)
	, m_Start(0)
	, m_Gap(0)
	, m_strText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJosephDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_HEADCOUNT, m_HeadCount);
	DDX_Text(pDX, IDC_START, m_Start);
	DDX_Text(pDX, IDC_GAP, m_Gap);
	//	DDX_Text(pDX, IDC_EDIT1, m_strText);
	DDX_Control(pDX, IDC_JOSEPH, m_btn);
}

BEGIN_MESSAGE_MAP(CJosephDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_JOSEPH, &CJosephDlg::OnBnClickedJoseph)
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CJosephDlg 消息处理程序

BOOL CJosephDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	HICON hicon = AfxGetApp()->LoadIcon(IDI_START);//IDI_ICON1是你添加的ICON文件标号 
	m_btn.SetIcon(hicon); //m_icon是按钮的成员变量 
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJosephDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CJosephDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJosephDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CJosephDlg::OnBnClickedJoseph()
{
	UpdateData();

	CCircle circle(m_HeadCount, m_Start, m_Gap);
	CListCtrl * pList = (CListCtrl *)GetDlgItem(IDC_LIST);
	pList->DeleteAllItems();
	if (!circle.JudgeHeadCount())
	{
		pList->DeleteAllItems();
		AfxMessageBox(_T("总人数应该大于0"));
		return;
	}
	if (!circle.JudgeStart())
	{
		pList->DeleteAllItems();
		AfxMessageBox(_T("起始位置应该大于0且小于总人数"));
		return;
	}
	if (!circle.JudgeGap())
	{
		pList->DeleteAllItems();
		AfxMessageBox(_T("间隔应给大于0"));
		return;
	}
	circle.Run();
	CProgressCtrl* proCtrl = (CProgressCtrl *)GetDlgItem(IDC_PROGRESS1);
	proCtrl->SetRange(0, m_HeadCount);
	proCtrl->SetPos(0);     //初始化进度条

	for (int i = 1; i <= m_HeadCount; i++)
	{
		CString szStr;
		szStr.Format(_T("第%d出局人的编号是%d"), i, circle.roll[i]);
		int nCount = pList->GetItemCount();
		pList->InsertItem(nCount, szStr);
		proCtrl->SetStep(1);   //设置步长
		proCtrl->StepIt();
		//Sleep(1000);
		//编辑框显示进度
		int nPos = (i * 100 / m_HeadCount);
		CString s;
		s.Format(_T("%d"), nPos);
		GetDlgItem(IDC_EDIT1)->SetWindowText((s + (CString)"%"));
		GetDlgItem(IDC_EDIT1)->UpdateWindow();
	}
}