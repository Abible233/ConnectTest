
// ConnectTestDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "TCPInfoTransfer.h"
#include "UDPInfoTransfer.h"


// CConnectTestDlg 对话框
class CConnectTestDlg : public CDialogEx
{
// 构造
public:
	CConnectTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CONNECTTEST_DIALOG };

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
	//afx_msg LRESULT OnRecvData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl member_tab_;
	CUDPInfoTransfer member_UDP_information_transfer_;
	CTCPInfoTransfer member_TCP_information_transfer_;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	/*BOOL InitSocket();
	SOCKET m_socket;
	static DWORD WINAPI RecvProc(LPVOID lpParameter);*/
};

//struct RECVPARAM
//{
//	SOCKET sock;		// 已创建的套接字
//	HWND hwnd;			// 对话框句柄
//};

//#define WM_RECVDATA WM_USER+1