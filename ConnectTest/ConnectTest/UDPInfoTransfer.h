#pragma once


// CUDPInfoTransfer �Ի���

class CUDPInfoTransfer : public CDialog
{
	DECLARE_DYNAMIC(CUDPInfoTransfer)

public:
	CUDPInfoTransfer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUDPInfoTransfer();

// �Ի�������
	enum { IDD = IDD_UDP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg LRESULT OnUDPRecvData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CString UDP_send_text_;
	CString UDP_receive_text_;
	afx_msg void OnBnClickedUdpSendButton();
	BOOL InitSocket();
	SOCKET UDP_m_socket;
	static DWORD WINAPI UDPRecvProc(LPVOID lpParameter);
	CIPAddressCtrl UDP_m_IP_to;
	CString UDP_to_IP;
	short UDP_m_to_IP_port;
	afx_msg void OnBnClickedButtonSetUDPIP();
};

struct RECVPARAM
{
	SOCKET sock;		// �Ѵ������׽���
	HWND hwnd;			// �Ի�����
};