
// ConnectTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "TCPInfoTransfer.h"
#include "UDPInfoTransfer.h"


// CConnectTestDlg �Ի���
class CConnectTestDlg : public CDialogEx
{
// ����
public:
	CConnectTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CONNECTTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
//	SOCKET sock;		// �Ѵ������׽���
//	HWND hwnd;			// �Ի�����
//};

//#define WM_RECVDATA WM_USER+1