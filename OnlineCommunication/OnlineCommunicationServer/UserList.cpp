// UserList.cpp : implementation file
//

#include "stdafx.h"
#include "OnlineCommunicationServer.h"
#include "UserList.h"


// CUserList

IMPLEMENT_DYNAMIC(CUserList, CListCtrl)

CUserList::CUserList()
{

}

CUserList::~CUserList()
{
}


BEGIN_MESSAGE_MAP(CUserList, CListCtrl)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CUserList::OnNMDblclk)
END_MESSAGE_MAP()



// CUserList message handlers




int CUserList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_imgList.Create(IDB_USERLIST, 16, 1, ILC_COLOR4);
	SetImageList(&m_imgList, LVSIL_NORMAL);

	CString title[] = { _T("Ãû³Æ"),_T("×¨Òµ") };
	int len = sizeof(title) / sizeof(title[0]);
	for (int i = 0; i < len; ++i)
	{
		InsertColumn(i, title[i], LVCFMT_LEFT, 70);
	}

	return 0;
}


void CUserList::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
