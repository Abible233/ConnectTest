#pragma once


// CUDPInfoTransfer 对话框

class CUDPInfoTransfer : public CDialog
{
	DECLARE_DYNAMIC(CUDPInfoTransfer)

public:
	CUDPInfoTransfer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUDPInfoTransfer();

// 对话框数据
	enum { IDD = IDD_UDP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString UDP_send_text_;
	CString UDP_receive_text_;
	afx_msg void OnBnClickedUdpSendButton();
};
