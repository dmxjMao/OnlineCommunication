
// OnlineCommunicationServerDoc.h : interface of the COnlineCommunicationServerDoc class
//


#pragma once
#include "Message.h"
class CChatSocket;

class COnlineCommunicationServerDoc : public CDocument
{
protected: // create from serialization only
	COnlineCommunicationServerDoc();
	DECLARE_DYNCREATE(COnlineCommunicationServerDoc)

// Attributes
public:
	CString m_strType;
	CString m_strMajor;
	CMessage msg;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~COnlineCommunicationServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


	BOOL ConnectSocket(LPCTSTR lpszHandle, LPCTSTR lpszAddress,
		LPCTSTR m_strImage, LPCTSTR m_strMajor, LPCTSTR m_strType, UINT nPort);
	BOOL m_bConnected;
	void ProcessPendingRead();

	void SendMsg();
	void ReceiveMsg();
	void Disconnect();
	BOOL m_bFilter;

protected:
	CChatSocket* m_pSocket;
	CSocketFile* m_pFile;
	CArchive* m_pArchiveIn;
	CArchive* m_pArchiveOut;

	CString  m_strHandle;
	void talk(int type, CString from, CString to, CString str, COLORREF clr);
	void DisplayRecMsg(int type, CString from, CString to, BOOL sec, CString str, COLORREF clr);
	void DisplayMsg(LPCTSTR lpszText);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnUpdateConnections(CCmdUI *pCmdUI);
};
