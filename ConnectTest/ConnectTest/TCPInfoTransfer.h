#pragma once


// CTCPInfoTransfer 对话框

class CTCPInfoTransfer : public CDialogEx
{
	DECLARE_DYNAMIC(CTCPInfoTransfer)

public:
	CTCPInfoTransfer(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTCPInfoTransfer();

// 对话框数据
	enum { IDD = IDD_TCP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
