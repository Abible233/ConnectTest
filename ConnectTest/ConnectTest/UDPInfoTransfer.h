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

	DECLARE_MESSAGE_MAP()
public:
	CString UDP_send_text_;
	CString UDP_receive_text_;
	afx_msg void OnBnClickedUdpSendButton();
};
