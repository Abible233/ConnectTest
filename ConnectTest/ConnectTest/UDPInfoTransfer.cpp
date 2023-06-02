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
	, UDP_m_to_IP_port(0)
{
	// 创建并初始化套接字
	InitSocket();

	RECVPARAM *pRecvParam = new RECVPARAM;
	pRecvParam->sock = UDP_m_socket;
	pRecvParam->hwnd = m_hWnd;
	// 创建接收线程
	HANDLE hThread = CreateThread(NULL, 0, UDPRecvProc, (LPVOID)pRecvParam, 0, NULL);
	// 关闭该接收程句柄，释放其引用计数
	CloseHandle(hThread);
}

CUDPInfoTransfer::~CUDPInfoTransfer()
{
}

void CUDPInfoTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_UDP_SEND_TEXT_EDIT, UDP_send_text_);
	DDX_Text(pDX, IDC_UDP_RECEIVE_TEXT_EDIT, UDP_receive_text_);
	DDX_Control(pDX, IDC_IPADDRESS_TO, UDP_m_IP_to);
	DDX_Text(pDX, IDC_EDIT_TO_IP_PORT, UDP_m_to_IP_port);
}


BEGIN_MESSAGE_MAP(CUDPInfoTransfer, CDialog)
	ON_BN_CLICKED(IDC_UDP_SEND_BUTTON, &CUDPInfoTransfer::OnBnClickedUdpSendButton)
	ON_MESSAGE(WM_UDP_RECVDATA, OnUDPRecvData)
	ON_BN_CLICKED(IDC_BUTTON_SET_IP, &CUDPInfoTransfer::OnBnClickedButtonSetUDPIP)
END_MESSAGE_MAP()


// CUDPInfoTransfer 消息处理程序


void CUDPInfoTransfer::OnBnClickedUdpSendButton()
{
	// TODO: 在此添加控件通知处理程序代码
	// 将控件中的数据保存到对应的变量中
	UpdateData(TRUE);
	USES_CONVERSION;

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
	address_server.sin_addr.S_un.S_addr = inet_addr(T2A(UDP_to_IP));
	address_server.sin_family = AF_INET;
	address_server.sin_port = htons(UDP_m_to_IP_port);

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


BOOL CUDPInfoTransfer::InitSocket()
{
	// WSAStartup初始化
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(1, 1);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return FALSE;
	}

	if (LOBYTE(wsaData.wVersion) != 1 ||
		HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup();
		return FALSE;
	}
	// 创建套接字
	UDP_m_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(INVALID_SOCKET == UDP_m_socket)
	{
		MessageBox(_T("UDP套接字创建失败！"));
		return FALSE;
	}
	SOCKADDR_IN addrSock;
	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSock.sin_family = AF_INET;
	addrSock.sin_port = htons(9001);

	// 绑定套接字
	int retval;
	retval = bind(UDP_m_socket, (SOCKADDR*)&addrSock, sizeof(SOCKADDR));
	if(SOCKET_ERROR == retval)
	{
		closesocket(UDP_m_socket);
		MessageBox(_T("绑定失败！"));
		return FALSE;
	}
	//WSACleanup();
	return TRUE;
}


DWORD WINAPI CUDPInfoTransfer::UDPRecvProc(LPVOID lpParameter)
{
	// 获得主线程传递的套接字和句柄
	SOCKET sock = ((RECVPARAM*)lpParameter)->sock;
	HWND hwnd = ((RECVPARAM*)lpParameter)->hwnd;
	delete lpParameter;

	SOCKADDR_IN addrFrom;
	int len = sizeof(SOCKADDR);

	char receive_buffer[200];

	int retval;
	while (TRUE)
	{
		// 接收数据
		retval = recvfrom(sock, receive_buffer, 200, 0, (SOCKADDR*)&addrFrom, &len);
		if (SOCKET_ERROR == retval)
		{
			break;
		}
		::PostMessage(hwnd, WM_UDP_RECVDATA, 0, (LPARAM)receive_buffer);
	}
	return 0;
}

LRESULT CUDPInfoTransfer::OnUDPRecvData(WPARAM wPara, LPARAM lParam)
{
	CString str;
	USES_CONVERSION;
	str = A2T((char*)lParam);
	CString strTemp;
	// 获得已有数据
	GetDlgItemText(IDC_UDP_RECEIVE_TEXT_EDIT, strTemp);
	str += "\r\n";
	str += strTemp;
	// 显示所有接收到的数据
	SetDlgItemText(IDC_UDP_RECEIVE_TEXT_EDIT, str);

	return 0;
}

void CUDPInfoTransfer::OnBnClickedButtonSetUDPIP()
{
	// TODO: 在此添加控件通知处理程序代码
	BYTE ip_value[4];
	//CString ip_string;

	UpdateData(TRUE);

	if (UDP_m_IP_to.IsBlank())
	{
		MessageBox(_T("请输入IP地址"), _T("提示"), MB_OK);
	}
	else
	{
		//m_ip.ClearAddress();
		UDP_m_IP_to.GetAddress(ip_value[0], ip_value[1], ip_value[2], ip_value[3]);
		UDP_to_IP.Format(_T("%d.%d.%d.%d"), ip_value[0], ip_value[1], ip_value[2], ip_value[3]);
		UDP_m_IP_to.SetFocus();
		MessageBox(_T("设置完成，可以传送消息！"), _T("提示"), MB_OK);
	}
}