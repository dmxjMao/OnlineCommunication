
// ServerDoc.h : interface of the CServerDoc class
//


#pragma once
#include "lstnsock.h"
#include "clntsock.h"
#include <afxtempl.h>

#define	PORT 2310
class CMessage;

class CServerDoc : public CDocument
{
protected: // create from serialization only
	CServerDoc();
	DECLARE_DYNCREATE(CServerDoc)

// Attributes
public:
	CListeningSocket*		m_pSocket;
	CTypedPtrList<CPtrList, CMessage*> m_lsMsg;
	CPtrList m_connectionList;

// Operations
public:
	void UpdateClients();
	void ProcessPendingAccept();
	void ProcessPendingRead(CClientSocket* pSocket);
	CMessage* AssembleMsg(CClientSocket* pSocket);
	CMessage* ReadMsg(CClientSocket* pSocket);
	void SendMsg(CClientSocket* pSocket, CMessage* pMsg);
	void CloseSocket(CClientSocket* pSocket);
	void Message(LPCTSTR lpszMessage);
	void Message1(LPCTSTR lpszMessage);
	void talk(int type2, CString from1, CString to1, CString str1);

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void DeleteContents();
	virtual void OnCloseDocument();
	virtual BOOL CanCloseFrame(CFrameWnd* pFrame);
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	void Clean();
	void DelSocket();
	virtual ~CServerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void UpdateList(CClientSocket* pSocket);

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
