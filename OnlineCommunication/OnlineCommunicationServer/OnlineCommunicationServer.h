
// OnlineCommunicationServer.h : main header file for the OnlineCommunicationServer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COnlineCommunicationServerApp:
// See OnlineCommunicationServer.cpp for the implementation of this class
//

class COnlineCommunicationServerApp : public CWinAppEx
{
public:
	COnlineCommunicationServerApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COnlineCommunicationServerApp theApp;
