#pragma once


// CTCPInfoTransfer �Ի���

class CTCPInfoTransfer : public CDialogEx
{
	DECLARE_DYNAMIC(CTCPInfoTransfer)

public:
	CTCPInfoTransfer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTCPInfoTransfer();

// �Ի�������
	enum { IDD = IDD_TCP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
