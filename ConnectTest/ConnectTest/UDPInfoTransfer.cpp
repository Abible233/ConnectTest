// UDPInfoTransfer.cpp : 实现文件
//

#include "stdafx.h"
#include "ConnectTest.h"
#include "UDPInfoTransfer.h"
#include "afxdialogex.h"


// CUDPInfoTransfer 对话框

IMPLEMENT_DYNAMIC(CUDPInfoTransfer, CDialog)

CUDPInfoTransfer::CUDPInfoTransfer(CWnd* pParent /*=NULL*/)
	: CDialog(CUDPInfoTransfer::IDD, pParent)
	, UDP_send_text_(_T(""))
	, UDP_receive_text_(_T(""))
{

}

CUDPInfoTransfer::~CUDPInfoTransfer()
{
}

void CUDPInfoTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_UDP_SEND_TEXT_EDIT, UDP_send_text_);
	DDX_Text(pDX, IDC_UDP_RECEIVE_TEXT_EDIT, UDP_receive_text_);
}


BEGIN_MESSAGE_MAP(CUDPInfoTransfer, CDialog)
	ON_BN_CLICKED(IDC_UDP_SEND_BUTTON, &CUDPInfoTransfer::OnBnClickedUdpSendButton)
END_MESSAGE_MAP()


// CUDPInfoTransfer 消息处理程序


void CUDPInfoTransfer::OnBnClickedUdpSendButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 将控件中的数据保存到对应的变量中
	UpdateData(TRUE);

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD( 1, 1 );

	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {                                 
		return;
	}

	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) {                                 
			WSACleanup( );
			return; 
	}

	// 创建套接字
	SOCKET socket_client = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN address_server;
	address_server.sin_addr.S_un.S_addr = inet_addr("192.168.2.99");
	address_server.sin_family = AF_INET;
	address_server.sin_port = htons(9000);

	char send_buffer[100];

	int len = sizeof(SOCKADDR);

	// 处理数据，将CString转换为char[]
	if ("" == UDP_send_text_)
	{
		send_buffer[0] = '\0';
	} 
	else
	{
		int send_text_length = UDP_send_text_.GetLength();
		for(int i = 0; i < send_text_length; i++)
		{
			send_buffer[i] = UDP_send_text_.GetAt(i);
		}
		send_buffer[send_text_length] = '\0';
	}

	// 发送数据
	sendto(socket_client, send_buffer, strlen(send_buffer)+1, 0, (SOCKADDR*)&address_server, len);

	closesocket(socket_client);
	WSACleanup();
}
