// UserPane.cpp : implementation file
//

#include "stdafx.h"
#include "OnlineCommunicationServer.h"
#include "UserPane.h"


// CUserPane

IMPLEMENT_DYNAMIC(CUserPane, CDockablePane)

CUserPane::CUserPane()
{

}

CUserPane::~CUserPane()
{
}


BEGIN_MESSAGE_MAP(CUserPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CUserPane message handlers




int CUserPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CRect rc;
	rc.SetRectEmpty();

	const DWORD style = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | LVS_REPORT;
	if (!m_userList.Create(style, rc, this, 2))
	{
		TRACE0("Failed to create userlist!\n");
		return -1;
	}

	return 0;
}


void CUserPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if(GetSafeHwnd())
	{
		CRect rc;
		GetClientRect(rc);

		m_userList.SetWindowPos(nullptr, rc.left, rc.top,
			rc.Width(), rc.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
	}
}
