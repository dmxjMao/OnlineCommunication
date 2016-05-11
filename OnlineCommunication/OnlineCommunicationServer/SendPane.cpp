// SendPane.cpp : implementation file
//

#include "stdafx.h"
#include "OnlineCommunicationServer.h"
#include "SendPane.h"


// CSendPane

IMPLEMENT_DYNAMIC(CSendPane, CDockablePane)

CSendPane::CSendPane()
{

}

CSendPane::~CSendPane()
{
}


BEGIN_MESSAGE_MAP(CSendPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CSendPane message handlers




int CSendPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_sendDlg.Create(IDD_SEND, this);
	m_sendDlg.ShowWindow(SW_SHOW);

	return 0;
}


void CSendPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_sendDlg.GetSafeHwnd()) {
		CRect rc;
		GetClientRect(rc);

		m_sendDlg.SetWindowPos(nullptr, rc.left, rc.top, rc.Width(), rc.Height(), /*SWP_NOMOVE | */SWP_NOACTIVATE | SWP_NOZORDER);
		m_sendDlg.ShowWindow(SW_SHOW);
	}
}
