// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OnlineCommunicationServer.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg dialog

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_strType(_T("1 硬件论坛"))
	, m_strImage(_T("1"))
	, m_strName(_T("李大嘴"))
	, m_strServerIP(_T("127.0.0.1"))
	, m_strMajor(_T("1 计算机工程"))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_FORUM, m_strType);
	DDX_CBString(pDX, IDC_IMAGE, m_strImage);
	DDX_CBString(pDX, IDC_NAME, m_strName);
	//  DDX_IPAddress(pDX, IDC_IPADDRESS1, m_strServerIP);
	DDX_CBString(pDX, IDC_MAJOR, m_strMajor);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
END_MESSAGE_MAP()


// CLoginDlg message handlers
