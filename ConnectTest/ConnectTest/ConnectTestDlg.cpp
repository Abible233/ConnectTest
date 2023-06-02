
// ConnectTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ConnectTest.h"
#include "ConnectTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

	//afx_msg void OnBnClickedButtonSetIP();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON_SET_IP, &CAboutDlg::OnBnClickedButtonSetIP)
END_MESSAGE_MAP()


// CConnectTestDlg 对话框




CConnectTestDlg::CConnectTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConnectTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConnectTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, member_tab_);
}

BEGIN_MESSAGE_MAP(CConnectTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CConnectTestDlg::OnTcnSelchangeTab1)
	//ON_MESSAGE(WM_RECVDATA, OnRecvData)
END_MESSAGE_MAP()


// CConnectTestDlg 消息处理程序

BOOL CConnectTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	// 标签控件客户区的位置和大小
	CRect tab_rectangle_;
	// 插入第一个标签“UDP”
	member_tab_.InsertItem(0, _T("UDP"));
	// 插入第二个标签“TCP”
	member_tab_.InsertItem(1, _T("TCP"));

	// 创建第一个标签页
	member_UDP_information_transfer_.Create(IDD_UDP_DIALOG, &member_tab_);
	// 创建第二个标签页
	member_TCP_information_transfer_.Create(IDD_TCP_DIALOG, &member_tab_);

	// 获取标签控件客户区Rect
	member_tab_.GetClientRect(&tab_rectangle_);

	// 调整tab_rectangle_
	tab_rectangle_.left += 1;
	tab_rectangle_.right -= 1;
	tab_rectangle_.top += 25;
	tab_rectangle_.bottom -= 1;

	// 将调整好的tab_rectangle_放置member_UDP_information_transfer_
	// 并设置为显示
	member_UDP_information_transfer_.SetWindowPos(NULL, 
												  tab_rectangle_.left, 
												  tab_rectangle_.top, 
												  tab_rectangle_.Width(), 
												  tab_rectangle_.Height(),
												  SWP_SHOWWINDOW);
	// 将调整好的tab_rectangle_放置member_TCP_information_transfer_
	// 并设置为隐藏
	member_TCP_information_transfer_.SetWindowPos(NULL, 
												  tab_rectangle_.left, 
												  tab_rectangle_.top, 
												  tab_rectangle_.Width(), 
												  tab_rectangle_.Height(),
												  SWP_HIDEWINDOW);

	//// 创建并初始化套接字
	//InitSocket();

	//RECVPARAM *pRecvParam = new RECVPARAM;
	//pRecvParam->sock = m_socket;
	//pRecvParam->hwnd = m_hWnd;
	//// 创建接收线程
	//HANDLE hThread = CreateThread(NULL, 0, RecvProc, (LPVOID)pRecvParam, 0, NULL);
	//// 关闭该接收程句柄，释放其引用计数
	//CloseHandle(hThread);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CConnectTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CConnectTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CConnectTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CConnectTestDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	// 标签控件客户区的Rect
	CRect tab_rectangle_;

	// 获取标签控件客户区Rect，并对其调整，以合适放置标签页
	member_tab_.GetClientRect(&tab_rectangle_);
	tab_rectangle_.left += 1;
	tab_rectangle_.right -= 1;
	tab_rectangle_.top += 25;
	tab_rectangle_.bottom -= 1;

	// 切换标签页
	switch (member_tab_.GetCurSel())
	{
		// 如果标签控件当前选择标签为“UDP”，则显示member_UDP_information_transfer_对话框
		// 隐藏member_TCP_information_transfer_对话框
	case 0:
		member_UDP_information_transfer_.SetWindowPos(NULL, 
													  tab_rectangle_.left, 
													  tab_rectangle_.top, 
													  tab_rectangle_.Width(), 
													  tab_rectangle_.Height(),
													  SWP_SHOWWINDOW);
		member_TCP_information_transfer_.SetWindowPos(NULL, 
													  tab_rectangle_.left, 
													  tab_rectangle_.top, 
													  tab_rectangle_.Width(), 
													  tab_rectangle_.Height(),
													  SWP_HIDEWINDOW);
		break;
		// 如果标签控件当前选择标签为“TCP”，则显示member_TCP_information_transfer_对话框
		// 隐藏member_UDP_information_transfer_对话框
	case 1:
		member_UDP_information_transfer_.SetWindowPos(NULL, 
													  tab_rectangle_.left, 
													  tab_rectangle_.top, 
													  tab_rectangle_.Width(), 
													  tab_rectangle_.Height(),
													  SWP_HIDEWINDOW);
		member_TCP_information_transfer_.SetWindowPos(NULL, 
													  tab_rectangle_.left, 
													  tab_rectangle_.top, 
													  tab_rectangle_.Width(), 
													  tab_rectangle_.Height(),
													  SWP_SHOWWINDOW);
		break;
	default:
		break;
	}

}


//
//BOOL CConnectTestDlg::InitSocket()
//{
//	// WSAStartup初始化
//	WORD wVersionRequested;
//	WSADATA wsaData;
//	int err;
//
//	wVersionRequested = MAKEWORD(1, 1);
//
//	err = WSAStartup(wVersionRequested, &wsaData);
//	if (err != 0) {
//		return FALSE;
//	}
//
//	if (LOBYTE(wsaData.wVersion) != 1 ||
//		HIBYTE(wsaData.wVersion) != 1) {
//		WSACleanup();
//		return FALSE;
//	}
//	// 创建套接字
//	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
//	if(INVALID_SOCKET == m_socket)
//	{
//		MessageBox(_T("套接字创建失败！"));
//		return FALSE;
//	}
//	SOCKADDR_IN addrSock;
//	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	addrSock.sin_family = AF_INET;
//	addrSock.sin_port = htons(9001);
//
//	// 绑定套接字
//	int retval;
//	retval = bind(m_socket, (SOCKADDR*)&addrSock, sizeof(SOCKADDR));
//	if(SOCKET_ERROR == retval)
//	{
//		closesocket(m_socket);
//		MessageBox(_T("绑定失败！"));
//		return FALSE;
//	}
//	return TRUE;
//}
//
//
//DWORD WINAPI CConnectTestDlg::RecvProc(LPVOID lpParameter)
//{
//	// 获得主线程传递的套接字和句柄
//	SOCKET sock = ((RECVPARAM*)lpParameter)->sock;
//	HWND hwnd = ((RECVPARAM*)lpParameter)->hwnd;
//	delete lpParameter;
//
//	SOCKADDR_IN addrFrom;
//	int len = sizeof(SOCKADDR);
//
//	char receive_buffer[200];
//
//	int retval;
//	while (TRUE)
//	{
//		// 接收数据
//		retval = recvfrom(sock, receive_buffer, 200, 0, (SOCKADDR*)&addrFrom, &len);
//		if (SOCKET_ERROR == retval)
//		{
//			break;
//		}
//		::PostMessage(hwnd, WM_RECVDATA, 0, (LPARAM)receive_buffer);
//	}
//	return 0;
//}
//
//LRESULT CConnectTestDlg::OnRecvData(WPARAM wPara, LPARAM lParam)
//{
//	CString str;
//	USES_CONVERSION;
//	str = A2T((char*)lParam);
//	CString strTemp;
//	// 获得已有数据
//	GetDlgItemText(IDC_UDP_RECEIVE_TEXT_EDIT, strTemp);
//	str += "\r\n";
//	str += strTemp;
//	// 显示所有接收到的数据
//	SetDlgItemText(IDC_UDP_RECEIVE_TEXT_EDIT, str);
//
//	return 0;
//}
//
