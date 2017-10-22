
// JosephDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CJosephDlg 对话框
class CJosephDlg : public CDialogEx
{
// 构造
public:
	CJosephDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JOSEPH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_HeadCount;
	int m_Start;
	int m_Gap;
	afx_msg void OnBnClickedJoseph();
	CString m_strText;
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CButton m_btn;
};
