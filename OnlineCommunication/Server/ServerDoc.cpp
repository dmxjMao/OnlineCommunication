
// ServerDoc.cpp : implementation of the CServerDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Server.h"
#endif

#include "ServerDoc.h"

#include "ServerView.h"
#include <propkey.h>

#include "Message.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CServerDoc

IMPLEMENT_DYNCREATE(CServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CServerDoc, CDocument)
END_MESSAGE_MAP()


// CServerDoc construction/destruction

CServerDoc::CServerDoc()
{
	// TODO: add one-time construction code here
	m_pSocket = nullptr;
}

CServerDoc::~CServerDoc()
{
}

BOOL CServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_pSocket = new CListeningSocket(this);
	if (m_pSocket->Create(PORT))
	{
		if (m_pSocket->Listen())
			return TRUE;
	}

	DWORD err = GetLastError();

	return FALSE;
}




// CServerDoc serialization

void CServerDoc::Serialize(CArchive& ar)
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
void CServerDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CServerDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CServerDoc::SetSearchContent(const CString& value)
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

// CServerDoc diagnostics

#ifdef _DEBUG
void CServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CServerDoc commands


void CServerDoc::UpdateClients()
{
	CMessage* pMsg = AssembleMsg(NULL);
	if (pMsg->type >= 0)
		int a = 0;
		//m_lCount++;
	for (POSITION pos = m_connectionList.GetHeadPosition(); pos != NULL;)
	{
		CClientSocket* pSocket = (CClientSocket*)m_connectionList.GetNext(pos);

		if (pMsg != NULL)
			SendMsg(pSocket, pMsg);
	}
}


void CServerDoc::ProcessPendingAccept()
{
	//����ͨ���׽���
	CClientSocket* pSocket = new CClientSocket(this);
	if (m_pSocket->Accept(*pSocket))
	{
		pSocket->Init();//��ʼ��
	}
	else
		delete pSocket;//ɾ��
}



//�ú������пͻ�����ʱ�رշ�����ʱ����
void CServerDoc::DeleteContents()
{
	delete m_pSocket;
	m_pSocket = NULL;

	CString temp;
	temp = "�������Ѿ��ص�!";

	CMessage* pMsg = new CMessage;
	while (!m_connectionList.IsEmpty())
	{
		CClientSocket* pSocket = (CClientSocket*)m_connectionList.RemoveHead();
		if (pSocket == NULL) continue;
		if (pMsg == NULL) continue;
		pMsg->m_bClose = TRUE;
		pMsg->from = pSocket->name;
		pMsg->m_strText = _TEXT("�������ѹر�");
		pMsg->to = _TEXT("������");
		pMsg->type = -3;

		SendMsg(pSocket, pMsg);

		if (!pSocket->IsAborted())
		{
			pSocket->ShutDown();
			BYTE Buffer[50];
			while (pSocket->Receive(Buffer, 50) > 0);
			delete pSocket;
		}
	}
	delete pMsg;

	if (!m_viewList.IsEmpty())
		((CEditView*)m_viewList.GetHead())->SetWindowText(_T(""));

	CDocument::DeleteContents();
}



void CServerDoc::UpdateList(CClientSocket* pSocket)
{
	CMessage* pMsg = new CMessage;
	for (POSITION pos = m_connectionList.GetHeadPosition(); pos != NULL;)
	{
		CClientSocket* pSock = (CClientSocket*)m_connectionList.GetNext(pos);
		pMsg->from = pSock->name;
		pMsg->type = -8;//�����û��б�
		pMsg->image = pSock->image;
		pMsg->major = pSock->major;
		pMsg->type1 = pSock->type1;
		SendMsg(pSocket, pMsg);//���͸����û��б���Ϣ
	}
}

BOOL CServerDoc::CanCloseFrame(CFrameWnd* pFrame)
{
	// TODO: Add your specialized code here and/or call the base class
	SetModifiedFlag(FALSE);
	return CDocument::CanCloseFrame(pFrame);
}


void CServerDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDocument::OnCloseDocument();
}

void CServerDoc::ProcessPendingRead(CClientSocket* pSocket)
{
	if (pSocket != NULL)
	{
		do {
			CMessage* pMsg = ReadMsg(pSocket);//������
			if (pMsg == NULL)
				return;
			if (pMsg->m_bClose)	//�����ˡ������������ɼ�
			{
				CloseSocket(pSocket);
				pMsg->m_bClose = FALSE;
				break;
			}
			if (pMsg->type == -1)//��������û�����
			{
				pSocket->name = pMsg->from;
				pSocket->type = pMsg->type;
				pSocket->image = pMsg->image;
				pSocket->major = pMsg->major;
				pSocket->type1 = pMsg->type1;
				m_connectionList.AddTail(pSocket);
				UpdateList(pSocket);
			}
		} while (!pSocket->m_pArchiveIn->IsBufferEmpty());
	}
	UpdateClients();
}



CMessage* CServerDoc::AssembleMsg(CClientSocket* pSocket)
{
	static CMessage msg;//��Ϣ����	
	CMessage* tmp;
	tmp = m_lsMsg.RemoveHead();//��Ϣ����ͷ
	if (tmp != NULL)
		memcpy(&msg, tmp, sizeof(CMessage));//�õ���Ϣ
	return &msg;
}

CMessage* CServerDoc::ReadMsg(CClientSocket* pSocket)
{
	static CMessage msg;//��Ϣ����
	CClientSocket* pSock;//�ͻ��׽��ֶ���
	TRY
	{
		pSocket->ReceiveMsg(&msg);//����Ϣ
	if (msg.type == -1)//�����û���¼
	{
		bool found = false;
		for (POSITION posname = m_connectionList.GetHeadPosition(); posname;)
		{
			pSock = (CClientSocket*)m_connectionList.GetNext(posname);
			if (pSock->name == msg.from)//�û����ѵ�¼
			{
				found = true;
				pSocket->needdel = true;//��ϴ����
				DelSocket();//ɾ���׽���
				return NULL;
			}
		}
		//ɾ���׽��֣���ѯ�����û��б���ĳ�˵Ŀͻ������׽��ֵ�needdelΪtrue����ϵͳ������������䷢����Ϣ��Ȼ��رո��׽���
		if (found == false)//���û�������
		{
			//����ͻ��׽���
			pSocket->name = msg.from;
			pSocket->image = msg.image;
			pSocket->major = msg.major;
			pSocket->type = msg.type1;
			Message1(msg.from);//��ʾ�û�
			Message1(_T("�糾���͵����Ŷ���\r\n"));//��ʾ
		}
	}
	if (msg.type == -2)//�뿪
	{
		Message1(msg.from);//�û���
		Message1(_T("�������뿪�ˣ��µ��ı�Ӱ�Եø�������\r\n"));
	}
	int i = msg.type;
	if (i >= 0 && i <= 32)
	{
		talk(i,msg.from,msg.to,msg.m_strText);//������������ʾ��Ϣ
	}
	if (i >= -2 && i <= 32)//�����Ϣ�б�
	{
		m_lsMsg.AddTail(&msg);
	}
	}
		CATCH(CFileException, e)//�쳣
	{
		CString strTemp(_T("IDS_READERROR"));
		//if (strTemp.LoadString(IDS_READERROR))
		Message(strTemp);//��ʾ�쳣��Ϣ

		msg.m_bClose = TRUE;
		pSocket->Abort();//�ر��׽���
	}
	END_CATCH
		return &msg;//������Ϣ����
}





void CServerDoc::SendMsg(CClientSocket* pSocket, CMessage* pMsg)
{
	TRY
	{
		pSocket->SendMsg(pMsg);//������Ϣ
	}
		CATCH(CFileException, e)//��׽�쳣
	{
		pSocket->Abort();//�ر�
		CString strTemp(_T("IDS_SENDERROR"));
		//if (strTemp.LoadString(IDS_SENDERROR))
		Message(strTemp);
	}
	END_CATCH
}

void CServerDoc::CloseSocket(CClientSocket* pSocket)
{
	pSocket->Close();

	POSITION pos, temp;
	for (pos = m_connectionList.GetHeadPosition(); pos != NULL;)
	{
		temp = pos;
		CClientSocket* pSock = (CClientSocket*)m_connectionList.GetNext(pos);
		if (pSock == pSocket) {
			m_connectionList.RemoveAt(temp);
			break;
		}
	}

	delete pSocket;
}

void CServerDoc::Message(LPCTSTR lpszMessage)
{
	//((CServerView*)m_viewList.GetHead())->Message(lpszMessage);
}

void CServerDoc::Message1(LPCTSTR lpszMessage)
{
	//((CServerView*)m_viewList.GetHead())->Message1(lpszMessage);
}



void CServerDoc::talk(int type2, CString from1, CString to1, CString str1)
{
	CString temp, to2, first, second;

	if (type2 > 32 || type2 < 0)
		return;
	temp = _T("IDS_TALK0");
	//temp.LoadString(IDS_TALK0 + type2);
	int i = temp.Find(',');
	if (i != -1) {
		first = temp.Left(i);
		if (i != temp.GetLength() - 1) {
			second = temp.Mid(i + 1);
			second += "��";
		}
		else {
			second = "��";
		}
		Message1(from1);
		Message1(first);
		Message1(to1);
		Message1(second);
		Message1(str1);
		Message1(_T("\r\n"));
	}
	else {
		first = temp;
		second = "�� ";
		Message1(from1);
		Message1(first);
		Message1(second);
		Message1(str1);
		Message1(_T("\r\n"));
	}
}

void CServerDoc::DelSocket()
{
	CClientSocket* pSock;
	POSITION pos, temp;
	for (pos = m_connectionList.GetHeadPosition(); pos != NULL;)
	{
		temp = pos;
		pSock = (CClientSocket*)m_connectionList.GetNext(pos);
		if (pSock->needdel == true)
		{
			m_connectionList.RemoveAt(temp);
			break;
		}
	}
	if (pSock == NULL)
		return;
	CMessage* pMsg = new CMessage;
	pMsg->from = _TEXT("ϵͳ");
	pMsg->to = _TEXT("��");
	pMsg->m_bClose = TRUE;
	pMsg->type = -9;
	pMsg->color = RGB(128, 0, 222);
	pMsg->major = pSock->major;
	pMsg->type1 = pSock->type;

	SendMsg(pSock, pMsg);
	if (!pSock->IsAborted()) {
		pSock->ShutDown();
		BYTE Buffer[50];
		while (pSock->Receive(Buffer, 50) > 0);
		delete pSock;
	}
}