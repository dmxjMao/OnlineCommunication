
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
	ON_UPDATE_COMMAND_UI(ID_CONNECTIONS, &COnlineCommunicationServerDoc::OnUpdateConnections)
END_MESSAGE_MAP()


// COnlineCommunicationServerDoc construction/destruction

COnlineCommunicationServerDoc::COnlineCommunicationServerDoc()
{
	// TODO: add one-time construction code here
	m_bConnected = FALSE;
	m_pSocket = nullptr;
	m_pFile = nullptr;
	m_pArchiveIn = nullptr;
	m_pArchiveOut = nullptr;

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
	//switch (msg.type1)//��̳����
	//{
	//case 1:
	//	strWindowText = m_strHandle + _T("(") + _T("Ӳ����̳") + _T(")");
	//	break;
	//case 2:
	//	strWindowText = m_strHandle + _T("(") + _T("���������̳") + _T("(");
	//	break;
	//case 3:
	//	strWindowText = m_strHandle + _T("(") + _T("Ƕ��ʽϵͳ��̳") + _T("(");
	//}
	SendMsg();//������Ϣ
	m_bConnected = TRUE;//���ӱ�־
	//GetView()->GetParent()->SetWindowText(strWindowText);//���ô��ڱ���
	return TRUE;
}


void COnlineCommunicationServerDoc::ProcessPendingRead()
{
	do
	{
		ReceiveMsg();//������Ϣ
		if (m_pSocket == NULL)
			return;
	} while (!m_pArchiveIn->IsBufferEmpty());
}


void COnlineCommunicationServerDoc::Disconnect()
{
	//����CMessage����
	msg.type = -2;//�û��뿪
	msg.m_bClose = TRUE;
	msg.from = m_strHandle;
	msg.to = "������";
	msg.secret = FALSE;
	msg.m_strText = "Hello";
	msg.color = RGB(0, 136, 255);
	msg.major = (WORD)_ttoi(m_strMajor);
	msg.type1 = (WORD)_ttoi(m_strType);
	SendMsg();//�������������Ϣ
	m_bConnected = FALSE;
	msg.from = "DUMP";//ɾ�������û�
	//GetView()->GetParent()->SetWindowText("������̳");//���ô��ڱ���
	//CComboBox* pTo = (CComboBox*)((CMainFrame*)GetView()->GetParent())->m_wndSend.GetDlgItem(IDC_TO);
	//pTo->Clear();//����������
	//			 //������Ϣ������û��б�
	//GetView()->GetParent()->SendMessage(WM_ADDLIST + 1, (LPARAM)&(msg.from), msg.image);
}


void COnlineCommunicationServerDoc::DisplayMsg(LPCTSTR lpszText)
{
	//CChatClientView* pView = (CChatClientView*)GetView();

	//if (pView != NULL)
	//	pView->TextOut(lpszText, RGB(128, 0, 0));
}

void COnlineCommunicationServerDoc::DisplayRecMsg(int type, CString from, CString to,
	BOOL sec, CString str, COLORREF clr)
{
	//CChatClientView* pView = (CChatClientView*)GetView();//�õ�������ͼ
	//if (msg.type1 != (WORD)atoi(m_strType))//�뱾�û�����һ����̳
	//	return;//����
	//if (type == -7)//����Ա�����Ż�
	//{
	//	pView->TextOut(_T("ϵͳ��Ϣ������Ա��һ��'��ɽ��Ӱ��',��"), RGB(0, 0, 0));
	//	if (from == m_strHandle)//�û��Լ�
	//	{
	//		pView->TextOut(_T("��"), RGB(0, 0, 255));
	//	}
	//	else
	//		pView->TextOut(from, RGB(0, 0, 255));
	//	pView->TextOut(_T("�߳�����\r\n"), RGB(0, 0, 0));
	//}
	////	if(type == -5)//
	////	{
	////		return;	
	////	}
	//if (type == -3)//ϵͳ�������ر�
	//{
	//	pView->TextOut(_T("ϵͳ��Ϣ���������ѹر�!"), RGB(0, 0, 0));
	//	return;
	//}
	//if (type == -1)//�û�����������
	//{
	//	pView->TextOut(from, RGB(0, 0, 255));
	//	pView->TextOut(_TEXT("�糾���͵����Ŷ���\r\n"), RGB(255, 0, 0));

	//}
	//if (type == -2)//�û��뿪������
	//{
	//	pView->TextOut(from, RGB(0, 0, 255));
	//	pView->TextOut(_TEXT("�������뿪����̳����Ӱ�Եø�������\r\n"), RGB(255, 0, 0));
	//}
	//if (type >= 0)//��ʱ����
	//{
	//	if (from == m_strHandle || to == m_strHandle || sec == FALSE || to == "������")
	//		talk(type, from, to, str, clr);
	//}
}

void COnlineCommunicationServerDoc::talk(int type, CString form, CString to,
	CString str, COLORREF clr)
{
	/*CChatClientView* pView = (CChatClientView*)GetView();

	if (form != m_strHandle && to != m_strHandle && m_bFilter)
		return;
	CString temp, to2, first, second;
	temp.LoadString(IDS_TALK0 + type);
	int i = temp.Find(",");
	if (i != -1) {
		first = temp.Left(i);
		if (i != temp.GetLength() - 1) {
			second = temp.Mid(i + 1);
			second += "��";
		}
		else {
			second = "��";
		}
		pView->TextOut((LPCTSTR)form, RGB(0, 0, 255));
		pView->TextOut((LPCTSTR)first, RGB(0, 0, 0));
		pView->TextOut((LPCTSTR)to, RGB(0, 0, 255));
		pView->TextOut((LPCTSTR)second, RGB(0, 0, 0));
		pView->TextOut((LPCTSTR)str, clr);
		pView->TextOut((LPCTSTR)"\r\n", clr);
	}
	else {
		first = temp;
		second = "�� ";
		pView->TextOut(form, RGB(0, 0, 255));
		pView->TextOut(first, RGB(0, 0, 0));
		pView->TextOut(second, RGB(0, 0, 0));
		pView->TextOut(str, clr);
		pView->TextOut("\r\n", clr);
	}*/
}

void COnlineCommunicationServerDoc::ReceiveMsg()
{
	TRY
	{
		msg.Serialize(*m_pArchiveIn);//��ȡ��Ϣ
	if (msg.type1 != (WORD)_ttoi(m_strType)) //����ͬһ��̳
		return;//����
			   //��ʾ�յ�����Ϣ
	DisplayRecMsg(msg.type, msg.from, msg.to, msg.secret,
		msg.m_strText, msg.color);
	//���϶Ͽ���������
	if (msg.type == -7 || msg.type == -2 || msg.type == -9)
		m_bConnected = FALSE;
	if (msg.type == -9)//�û���������ʹ��
		DisplayMsg(_T("���û����Ѿ�����ʹ�ã���������µ�¼!\n"));
	}
		CATCH(CFileException, e)//��׽�쳣
	{
		msg.m_bClose = TRUE;
		m_pArchiveOut->Abort();
		CString strTemp;
		//if (strTemp.LoadString(IDS_SERVERRESET))
		//	DisplayMsg(strTemp);
		//if (strTemp.LoadString(IDS_CONNECTIONCLOSED))
		//	DisplayMsg(strTemp);
	}
	END_CATCH
		if (msg.m_bClose && (msg.from == m_strHandle))
		{
			//��ʼ��������
			SAFEDELETE(m_pArchiveIn);
			SAFEDELETE(m_pArchiveOut);
			SAFEDELETE(m_pFile);
			SAFEDELETE(m_pSocket);
			m_bConnected = FALSE;
		}
	CString strText, strMajor;
	/*	switch(((WORD)atoi(m_strMajor)))//�û�רҵ
	{
	case 1:
	strText=m_strHandle+", "+"���������";
	break;
	case 2:
	strText=m_strHandle+", "+"�������";
	break;
	case 3:
	strText=m_strHandle+", "+"��������";
	}	*/
	//����û��б�
	if ((msg.type == -1 && msg.from != m_strHandle) || (msg.type == -8))
	{
		switch (msg.type1)//�û�רҵ
		{
		case 1:
			strText = msg.from + _T(", ") + _T("���������");
			break;
		//case 2:
		//	strText = msg.from + ", " + "�������";
		//	break;
		//case 3:
		//	strText = msg.from + ", " + "��������";
		}
		//GetView()->GetParent()->SendMessage(WM_ADDLIST, (LPARAM)&(strText), msg.image);
	}
	//���û��б�ɾ���û�
	if ((msg.type == -7) || (msg.type == -2))//�����뿪
	{
		//GetView()->GetParent()->SendMessage(WM_ADDLIST + 1, (LPARAM)&(msg.from), msg.image);
	}
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

void COnlineCommunicationServerDoc::OnUpdateConnections(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(TRUE);
	CString fmt(_T("online users:%d"));
	CString str;
	wsprintf(str.GetBuffer(50), fmt, 5);
	str.ReleaseBuffer();
	pCmdUI->SetText(str);
}
