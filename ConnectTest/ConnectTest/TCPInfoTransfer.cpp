// TCPInfoTransfer.cpp : 实现文件
//

#include "stdafx.h"
#include "ConnectTest.h"
#include "TCPInfoTransfer.h"
#include "afxdialogex.h"


// CTCPInfoTransfer 对话框

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


// CTCPInfoTransfer 消息处理程序
