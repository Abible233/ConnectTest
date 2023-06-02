
// ConnectTestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ConnectTest.h"
#include "ConnectTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CConnectTestDlg �Ի���




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


// CConnectTestDlg ��Ϣ�������

BOOL CConnectTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// ��ǩ�ؼ��ͻ�����λ�úʹ�С
	CRect tab_rectangle_;
	// �����һ����ǩ��UDP��
	member_tab_.InsertItem(0, _T("UDP"));
	// ����ڶ�����ǩ��TCP��
	member_tab_.InsertItem(1, _T("TCP"));

	// ������һ����ǩҳ
	member_UDP_information_transfer_.Create(IDD_UDP_DIALOG, &member_tab_);
	// �����ڶ�����ǩҳ
	member_TCP_information_transfer_.Create(IDD_TCP_DIALOG, &member_tab_);

	// ��ȡ��ǩ�ؼ��ͻ���Rect
	member_tab_.GetClientRect(&tab_rectangle_);

	// ����tab_rectangle_
	tab_rectangle_.left += 1;
	tab_rectangle_.right -= 1;
	tab_rectangle_.top += 25;
	tab_rectangle_.bottom -= 1;

	// �������õ�tab_rectangle_����member_UDP_information_transfer_
	// ������Ϊ��ʾ
	member_UDP_information_transfer_.SetWindowPos(NULL, 
												  tab_rectangle_.left, 
												  tab_rectangle_.top, 
												  tab_rectangle_.Width(), 
												  tab_rectangle_.Height(),
												  SWP_SHOWWINDOW);
	// �������õ�tab_rectangle_����member_TCP_information_transfer_
	// ������Ϊ����
	member_TCP_information_transfer_.SetWindowPos(NULL, 
												  tab_rectangle_.left, 
												  tab_rectangle_.top, 
												  tab_rectangle_.Width(), 
												  tab_rectangle_.Height(),
												  SWP_HIDEWINDOW);

	//// ��������ʼ���׽���
	//InitSocket();

	//RECVPARAM *pRecvParam = new RECVPARAM;
	//pRecvParam->sock = m_socket;
	//pRecvParam->hwnd = m_hWnd;
	//// ���������߳�
	//HANDLE hThread = CreateThread(NULL, 0, RecvProc, (LPVOID)pRecvParam, 0, NULL);
	//// �رոý��ճ̾�����ͷ������ü���
	//CloseHandle(hThread);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CConnectTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CConnectTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CConnectTestDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	// ��ǩ�ؼ��ͻ�����Rect
	CRect tab_rectangle_;

	// ��ȡ��ǩ�ؼ��ͻ���Rect��������������Ժ��ʷ��ñ�ǩҳ
	member_tab_.GetClientRect(&tab_rectangle_);
	tab_rectangle_.left += 1;
	tab_rectangle_.right -= 1;
	tab_rectangle_.top += 25;
	tab_rectangle_.bottom -= 1;

	// �л���ǩҳ
	switch (member_tab_.GetCurSel())
	{
		// �����ǩ�ؼ���ǰѡ���ǩΪ��UDP��������ʾmember_UDP_information_transfer_�Ի���
		// ����member_TCP_information_transfer_�Ի���
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
		// �����ǩ�ؼ���ǰѡ���ǩΪ��TCP��������ʾmember_TCP_information_transfer_�Ի���
		// ����member_UDP_information_transfer_�Ի���
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
//	// WSAStartup��ʼ��
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
//	// �����׽���
//	m_socket = socket(AF_INET, SOCK_DGRAM, 0);
//	if(INVALID_SOCKET == m_socket)
//	{
//		MessageBox(_T("�׽��ִ���ʧ�ܣ�"));
//		return FALSE;
//	}
//	SOCKADDR_IN addrSock;
//	addrSock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	addrSock.sin_family = AF_INET;
//	addrSock.sin_port = htons(9001);
//
//	// ���׽���
//	int retval;
//	retval = bind(m_socket, (SOCKADDR*)&addrSock, sizeof(SOCKADDR));
//	if(SOCKET_ERROR == retval)
//	{
//		closesocket(m_socket);
//		MessageBox(_T("��ʧ�ܣ�"));
//		return FALSE;
//	}
//	return TRUE;
//}
//
//
//DWORD WINAPI CConnectTestDlg::RecvProc(LPVOID lpParameter)
//{
//	// ������̴߳��ݵ��׽��ֺ;��
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
//		// ��������
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
//	// �����������
//	GetDlgItemText(IDC_UDP_RECEIVE_TEXT_EDIT, strTemp);
//	str += "\r\n";
//	str += strTemp;
//	// ��ʾ���н��յ�������
//	SetDlgItemText(IDC_UDP_RECEIVE_TEXT_EDIT, str);
//
//	return 0;
//}
//
