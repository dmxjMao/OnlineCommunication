#pragma once

#include "SendDlg.h"

// CSendPane

class CSendPane : public CDockablePane
{
	DECLARE_DYNAMIC(CSendPane)

public:
	CSendPane();
	virtual ~CSendPane();

protected:
	DECLARE_MESSAGE_MAP()

	CSendDlg		m_sendDlg;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


