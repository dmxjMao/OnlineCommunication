
// OnlineCommunicationServerView.h : interface of the COnlineCommunicationServerView class
//

#pragma once


class COnlineCommunicationServerView : public CView
{
protected: // create from serialization only
	COnlineCommunicationServerView();
	DECLARE_DYNCREATE(COnlineCommunicationServerView)

// Attributes
public:
	COnlineCommunicationServerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~COnlineCommunicationServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnConnect();
};

#ifndef _DEBUG  // debug version in OnlineCommunicationServerView.cpp
inline COnlineCommunicationServerDoc* COnlineCommunicationServerView::GetDocument() const
   { return reinterpret_cast<COnlineCommunicationServerDoc*>(m_pDocument); }
#endif

