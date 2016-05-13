
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
	//switch (msg.type1)//论坛类型
	//{
	//case 1:
	//	strWindowText = m_strHandle + _T("(") + _T("硬件论坛") + _T(")");
	//	break;
	//case 2:
	//	strWindowText = m_strHandle + _T("(") + _T("软件开发论坛") + _T("(");
	//	break;
	//case 3:
	//	strWindowText = m_strHandle + _T("(") + _T("嵌入式系统论坛") + _T("(");
	//}
	SendMsg();//发送消息
	m_bConnected = TRUE;//连接标志
	//GetView()->GetParent()->SetWindowText(strWindowText);//设置窗口标题
	return TRUE;
}


void COnlineCommunicationServerDoc::ProcessPendingRead()
{
	do
	{
		ReceiveMsg();//接收信息
		if (m_pSocket == NULL)
			return;
	} while (!m_pArchiveIn->IsBufferEmpty());
}


void COnlineCommunicationServerDoc::Disconnect()
{
	//设置CMessage对象
	msg.type = -2;//用户离开
	msg.m_bClose = TRUE;
	msg.from = m_strHandle;
	msg.to = "所有人";
	msg.secret = FALSE;
	msg.m_strText = "Hello";
	msg.color = RGB(0, 136, 255);
	msg.major = (WORD)_ttoi(m_strMajor);
	msg.type1 = (WORD)_ttoi(m_strType);
	SendMsg();//向服务器发送消息
	m_bConnected = FALSE;
	msg.from = "DUMP";//删除所有用户
	//GetView()->GetParent()->SetWindowText("网上论坛");//设置窗口标题
	//CComboBox* pTo = (CComboBox*)((CMainFrame*)GetView()->GetParent())->m_wndSend.GetDlgItem(IDC_TO);
	//pTo->Clear();//清空聊天对象
	//			 //发送消息，清空用户列表
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
	//CChatClientView* pView = (CChatClientView*)GetView();//得到关联视图
	//if (msg.type1 != (WORD)atoi(m_strType))//与本用户不在一个论坛
	//	return;//返回
	//if (type == -7)//管理员清理门户
	//{
	//	pView->TextOut(_T("系统消息：管理员以一招'佛山无影脚',将"), RGB(0, 0, 0));
	//	if (from == m_strHandle)//用户自己
	//	{
	//		pView->TextOut(_T("你"), RGB(0, 0, 255));
	//	}
	//	else
	//		pView->TextOut(from, RGB(0, 0, 255));
	//	pView->TextOut(_T("踢出门外\r\n"), RGB(0, 0, 0));
	//}
	////	if(type == -5)//
	////	{
	////		return;	
	////	}
	//if (type == -3)//系统服务器关闭
	//{
	//	pView->TextOut(_T("系统消息：服务器已关闭!"), RGB(0, 0, 0));
	//	return;
	//}
	//if (type == -1)//用户进入聊天室
	//{
	//	pView->TextOut(from, RGB(0, 0, 255));
	//	pView->TextOut(_TEXT("风尘仆仆地推门而入\r\n"), RGB(255, 0, 0));

	//}
	//if (type == -2)//用户离开聊天室
	//{
	//	pView->TextOut(from, RGB(0, 0, 255));
	//	pView->TextOut(_TEXT("静静地离开了论坛，背影显得格外潇洒\r\n"), RGB(255, 0, 0));
	//}
	//if (type >= 0)//即时聊天
	//{
	//	if (from == m_strHandle || to == m_strHandle || sec == FALSE || to == "所有人")
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
			second += "：";
		}
		else {
			second = "：";
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
		second = "： ";
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
		msg.Serialize(*m_pArchiveIn);//读取消息
	if (msg.type1 != (WORD)_ttoi(m_strType)) //不在同一论坛
		return;//返回
			   //显示收到的消息
	DisplayRecMsg(msg.type, msg.from, msg.to, msg.secret,
		msg.m_strText, msg.color);
	//符合断开连接条件
	if (msg.type == -7 || msg.type == -2 || msg.type == -9)
		m_bConnected = FALSE;
	if (msg.type == -9)//用户名已有人使用
		DisplayMsg(_T("该用户名已经有人使用，请更名重新登录!\n"));
	}
		CATCH(CFileException, e)//捕捉异常
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
			//初始化各对象
			SAFEDELETE(m_pArchiveIn);
			SAFEDELETE(m_pArchiveOut);
			SAFEDELETE(m_pFile);
			SAFEDELETE(m_pSocket);
			m_bConnected = FALSE;
		}
	CString strText, strMajor;
	/*	switch(((WORD)atoi(m_strMajor)))//用户专业
	{
	case 1:
	strText=m_strHandle+", "+"计算机工程";
	break;
	case 2:
	strText=m_strHandle+", "+"软件工程";
	break;
	case 3:
	strText=m_strHandle+", "+"计算机设计";
	}	*/
	//添加用户列表
	if ((msg.type == -1 && msg.from != m_strHandle) || (msg.type == -8))
	{
		switch (msg.type1)//用户专业
		{
		case 1:
			strText = msg.from + _T(", ") + _T("计算机工程");
			break;
		//case 2:
		//	strText = msg.from + ", " + "软件工程";
		//	break;
		//case 3:
		//	strText = msg.from + ", " + "计算机设计";
		}
		//GetView()->GetParent()->SendMessage(WM_ADDLIST, (LPARAM)&(strText), msg.image);
	}
	//从用户列表删除用户
	if ((msg.type == -7) || (msg.type == -2))//有人离开
	{
		//GetView()->GetParent()->SendMessage(WM_ADDLIST + 1, (LPARAM)&(msg.from), msg.image);
	}
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
