
// MainFrm.h : interface of the CMainFrame class
//

#pragma once

#include "SendPane.h"
#include "UserPane.h"

//#define WM_SYSTRAY	WM_USER + 1001


class CMainFrame : public CFrameWndEx
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CMFCMenuBar       m_wndMenuBar;
	CMFCToolBar       m_wndToolBar;
	CMFCStatusBar     m_wndStatusBar;
	CSendPane		m_sendPane;
	CUserPane		m_userPane;

	//NOTIFYICONDATA	pnid;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarCreateNew(WPARAM wp, LPARAM lp);
	//afx_msg LRESULT OnSysTray(WPARAM wp, LPARAM lp);
	DECLARE_MESSAGE_MAP()

	//virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


