
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
	m_strHandle = lpszHandle; //�û���
	m_strMajor = lpszMajor; //רҵ����
	m_strType = lpszType;  //��̳���ʹ���
						   //��ո�����
	SAFEDELETE(m_pArchiveIn);
	SAFEDELETE(m_pArchiveOut);
	SAFEDELETE(m_pFile);
	SAFEDELETE(m_pSocket);
	if (m_pSocket == NULL)
	{
		m_pSocket = new CChatSocket(this);//�����׽��ֶ���
		ASSERT(m_pSocket != NULL);
	}

	if (!m_pSocket->Create())//�����׽���ʧ��
	{
		delete m_pSocket;//ɾ���׽��ֶ���
		m_pSocket = NULL;
		TRACE("Create Socket Error!\n");
		return FALSE;
	}

	while (!m_pSocket->Connect(lpszAddress, nPort))//���ӷ�����ʧ��
	{
		//if (AfxMessageBox(IDS_RETRYCONNECT, MB_YESNO) == IDNO)
		//{
		//	delete m_pSocket;//ɾ���׽��ֶ���
		//	m_pSocket = NULL;
		//	return FALSE;
		//}
	}
	m_pFile = new CSocketFile(m_pSocket);//����CSocketFile����
	m_pArchiveIn = new CArchive(m_pFile, CArchive::load);//���չ鵵����
	m_pArchiveOut = new CArchive(m_pFile, CArchive::store);//���͹鵵����
														   //����CMessage�����Ա����
	msg.type = -1;//���ӷ�����
	msg.m_bClose = FALSE;
	msg.from = m_strHandle;//
	msg.to = "������";
	msg.secret = FALSE;
	msg.m_strText = "Hello";
	msg.color = RGB(0, 136, 255);
	msg.image = _ttoi(m_strImage);
	msg.major = _ttoi(m_strMajor);
	msg.type1 = _ttoi(m_strType);
	CString strWindowText;
	switch (msg.type1)//��̳����
	{
	case 1:
		strWindowText = m_strHandle + _T("(") + _T("Ӳ����̳") + _T(")");
		break;
	case 2:
		strWindowText = m_strHandle + _T("(") + _T("���������̳") + _T("(");
		break;
	case 3:
		strWindowText = m_strHandle + _T("(") + _T("Ƕ��ʽϵͳ��̳") + _T("(");
	}
	//SendMsg();//������Ϣ
	m_bConnected = TRUE;//���ӱ�־
	//GetView()->GetParent()->SetWindowText(strWindowText);//���ô��ڱ���
	return TRUE;
}


void COnlineCommunicationServerDoc::SendMsg()//������Ϣ
{
	//	msg.from = m_strHandle;
	//	msg.major = (WORD)atoi(m_strMajor);
	//	msg.type1 = (WORD)atoi(m_strType);
	if (m_pArchiveOut != NULL)
	{
		TRY
		{
			msg.Serialize(*m_pArchiveOut);//���л���Ϣ
		m_pArchiveOut->Flush();//������Ϣ
		}
		CATCH(CFileException, e)//��׽�쳣
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