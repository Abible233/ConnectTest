// TCPInfoTransfer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConnectTest.h"
#include "TCPInfoTransfer.h"
#include "afxdialogex.h"


// CTCPInfoTransfer �Ի���

IMPLEMENT_DYNAMIC(CTCPInfoTransfer, CDialogEx)

CTCPInfoTransfer::CTCPInfoTransfer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTCPInfoTransfer::IDD, pParent)
{

}

CTCPInfoTransfer::~CTCPInfoTransfer()
{
}

void CTCPInfoTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTCPInfoTransfer, CDialogEx)
END_MESSAGE_MAP()


// CTCPInfoTransfer ��Ϣ�������
