#pragma once

#include "UserList.h"

// CUserPane

class CUserPane : public CDockablePane
{
	DECLARE_DYNAMIC(CUserPane)

public:
	CUserPane();
	virtual ~CUserPane();

protected:
	DECLARE_MESSAGE_MAP()

	CUserList		m_userList;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	virtual BOOL FloatPane(CRect rectFloat, AFX_DOCK_METHOD dockMethod = DM_UNKNOWN, bool bShow = true) { return FALSE; }
	virtual BOOL CanFloat() const { return FALSE; }
	virtual BOOL CanBeClosed() const { return FALSE; }

};


