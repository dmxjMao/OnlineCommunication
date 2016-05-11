
// OnlineCommunicationServerView.cpp : implementation of the COnlineCommunicationServerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OnlineCommunicationServer.h"
#endif

#include "OnlineCommunicationServerDoc.h"
#include "OnlineCommunicationServerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COnlineCommunicationServerView

IMPLEMENT_DYNCREATE(COnlineCommunicationServerView, CView)

BEGIN_MESSAGE_MAP(COnlineCommunicationServerView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// COnlineCommunicationServerView construction/destruction

COnlineCommunicationServerView::COnlineCommunicationServerView()
{
	// TODO: add construction code here

}

COnlineCommunicationServerView::~COnlineCommunicationServerView()
{
}

BOOL COnlineCommunicationServerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COnlineCommunicationServerView drawing

void COnlineCommunicationServerView::OnDraw(CDC* /*pDC*/)
{
	COnlineCommunicationServerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void COnlineCommunicationServerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COnlineCommunicationServerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COnlineCommunicationServerView diagnostics

#ifdef _DEBUG
void COnlineCommunicationServerView::AssertValid() const
{
	CView::AssertValid();
}

void COnlineCommunicationServerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COnlineCommunicationServerDoc* COnlineCommunicationServerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COnlineCommunicationServerDoc)));
	return (COnlineCommunicationServerDoc*)m_pDocument;
}
#endif //_DEBUG


// COnlineCommunicationServerView message handlers
