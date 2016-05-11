
// OnlineCommunicationServerDoc.cpp : implementation of the COnlineCommunicationServerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OnlineCommunicationServer.h"
#endif

#include "OnlineCommunicationServerDoc.h"

#include <propkey.h>
#include "ChatSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// COnlineCommunicationServerDoc

IMPLEMENT_DYNCREATE(COnlineCommunicationServerDoc, CDocument)

BEGIN_MESSAGE_MAP(COnlineCommunicationServerDoc, CDocument)
END_MESSAGE_MAP()


// COnlineCommunicationServerDoc construction/destruction

COnlineCommunicationServerDoc::COnlineCommunicationServerDoc()
{
	// TODO: add one-time construction code here

}

COnlineCommunicationServerDoc::~COnlineCommunicationServerDoc()
{
}

BOOL COnlineCommunicationServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// COnlineCommunicationServerDoc serialization

void COnlineCommunicationServerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void COnlineCommunicationServerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void COnlineCommunicationServerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void COnlineCommunicationServerDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// COnlineCommunicationServerDoc diagnostics

#ifdef _DEBUG
void COnlineCommunicationServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COnlineCommunicationServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COnlineCommunicationServerDoc commands



BOOL COnlineCommunicationServerDoc::ConnectSocket(LPCTSTR lpszHandle, LPCTSTR lpszAddress,
	LPCTSTR m_strImage, LPCTSTR lpszMajor, LPCTSTR lpszType, UINT nPort)
{
	if (m_bConnected)
		return FALSE;
	m_strHandle = lpszHandle; //用户名
	m_strMajor = lpszMajor; //专业代码
	m_strType = lpszType;  //论坛类型代码
						   //清空各对象
	SAFEDELETE(m_pArchiveIn);
	SAFEDELETE(m_pArchiveOut);
	SAFEDELETE(m_pFile);
	SAFEDELETE(m_pSocket);
	if (m_pSocket == NULL)
	{
		m_pSocket = new CChatSocket(this);//构造套接字对象
		ASSERT(m_pSocket != NULL);
	}

	if (!m_pSocket->Create())//创建套接字失败
	{
		delete m_pSocket;//删除套接字对象
		m_pSocket = NULL;
		TRACE("Create Socket Error!\n");
		return FALSE;
	}

	while (!m_pSocket->Connect(lpszAddress, nPort))//连接服务器失败
	{
		//if (AfxMessageBox(IDS_RETRYCONNECT, MB_YESNO) == IDNO)
		//{
		//	delete m_pSocket;//删除套接字对象
		//	m_pSocket = NULL;
		//	return FALSE;
		//}
	}
	m_pFile = new CSocketFile(m_pSocket);//创建CSocketFile对象
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);//接收归档对象
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);//发送归档对象
														   //设置CMessage对象成员变量
	msg.type = -1;//连接服务器
	msg.m_bClose = FALSE;
	msg.from = m_strHandle;//
	msg.to = "所有人";
	msg.secret = FALSE;
	msg.m_strText = "Hello";
	msg.color = RGB(0, 136, 255);
	msg.image = _ttoi(m_strImage);
	msg.major = _ttoi(m_strMajor);
	msg.type1 = _ttoi(m_strType);
	CString strWindowText;
	switch (msg.type1)//论坛类型
	{
	case 1:
		strWindowText = m_strHandle + _T("(") + _T("硬件论坛") + _T(")");
		break;
	case 2:
		strWindowText = m_strHandle + _T("(") + _T("软件开发论坛") + _T("(");
		break;
	case 3:
		strWindowText = m_strHandle + _T("(") + _T("嵌入式系统论坛") + _T("(");
	}
	//SendMsg();//发送消息
	m_bConnected = TRUE;//连接标志
	//GetView()->GetParent()->SetWindowText(strWindowText);//设置窗口标题
	return TRUE;
}


void COnlineCommunicationServerDoc::SendMsg()//发送消息
{
	//	msg.from = m_strHandle;
	//	msg.major = (WORD)atoi(m_strMajor);
	//	msg.type1 = (WORD)atoi(m_strType);
	if (m_pArchiveOut != NULL)
	{
		TRY
		{
			msg.Serialize(*m_pArchiveOut);//序列化消息
		m_pArchiveOut->Flush();//发送消息
		}
		CATCH(CFileException, e)//捕捉异常
		{
			m_pArchiveOut->Abort();
			delete m_pArchiveOut;
			m_pArchiveOut = NULL;
			CString strTemp;
			//if (strTemp.LoadString(IDS_SERVERRESET))
			//	DisplayMsg(strTemp);
		}
		END_CATCH
	}
}