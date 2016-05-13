
// ServerView.cpp : implementation of the CServerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Server.h"
#endif

#include "ServerDoc.h"
#include "ServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CServerView

IMPLEMENT_DYNCREATE(CServerView, CView)

BEGIN_MESSAGE_MAP(CServerView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CServerView construction/destruction

CServerView::CServerView()
{
	// TODO: add construction code here

}

CServerView::~CServerView()
{
}

BOOL CServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CServerView drawing

void CServerView::OnDraw(CDC* /*pDC*/)
{
	CServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CServerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CServerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CServerView diagnostics

#ifdef _DEBUG
void CServerView::AssertValid() const
{
	CView::AssertValid();
}

void CServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CServerDoc* CServerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CServerDoc)));
	return (CServerDoc*)m_pDocument;
}
#endif //_DEBUG


// CServerView message handlers
