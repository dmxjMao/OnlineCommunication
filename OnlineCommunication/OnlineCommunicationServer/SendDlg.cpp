// SendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OnlineCommunicationServer.h"
#include "SendDlg.h"
#include "afxdialogex.h"


// CSendDlg dialog

IMPLEMENT_DYNAMIC(CSendDlg, CDialogEx)

CSendDlg::CSendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SEND, pParent)
{

}

CSendDlg::CSendDlg(COnlineCommunicationServerDoc* pDoc, CWnd* pParent /*=NULL*/)
	: m_pDoc(pDoc), CDialogEx(IDD_SEND, pParent)
{

}

CSendDlg::~CSendDlg()
{
}

void CSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSendDlg, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CSendDlg::OnBnClickedButtonColor)
ON_BN_CLICKED(IDC_BUTTON_COLOR, &CSendDlg::OnClickedButtonColor)
ON_WM_PAINT()
END_MESSAGE_MAP()


// CSendDlg message handlers



void CSendDlg::OnClickedButtonColor()
{
	// TODO: Add your control notification handler code here
	CColorDialog clr;
	if (IDOK == clr.DoModal())
	{

	}
}


void CSendDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CDialogEx::OnPaint() for painting messages
	CRect rc;
	GetClientRect(rc);
	dc.FillSolidRect(rc, RGB(255, 255, 255));
	dc.FillPath();

}
