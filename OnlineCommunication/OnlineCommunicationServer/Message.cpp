// Message.cpp: implementation of the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ChatClient.h"
#include "Message.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessage::CMessage()//初始化参数
{
	image = 1;
	major = 0;
	type1 = 0;
	type = 0;
	secret = FALSE;
	color = RGB(0,136,255);
	m_bClose = FALSE;
	from = to = m_strText = _T("");
}

CMessage::~CMessage()
{

}

void CMessage::Serialize(CArchive &ar)//序列化
{
	if (ar.IsStoring())//
	{
		ar << type;
		ar << (WORD)m_bClose;
		ar << m_strText;
		ar << (WORD)secret;
		ar << from;
		ar << to;
		ar << (DWORD)color;
		ar << image;
		ar << major;
		ar << type1;
	}
	else
	{
		WORD wd;
		DWORD dwTmp;
		ar >> type;
		ar >> wd;
		m_bClose = (BOOL)wd;
		ar >> m_strText;
		ar >> wd;
		secret = (BOOL)wd;
		ar >> from;
		ar >> to;
		ar >> dwTmp;
		color = (COLORREF)dwTmp;
		ar >> image;
		ar >> major;
		ar >> type1;
	}
/*	
	m_msgList.Serialize(ar);
	fromlist.Serialize(ar);
	tolist.Serialize(ar);
	seclist.Serialize(ar);
	typelist.Serialize(ar);
	clrlist.Serialize(ar); 
*/}

/*void CMessage::Reset()//重置参数
{
	image = 1;
	type = 0;
	secret = FALSE;
	color = RGB(0,136,255);
	m_bClose = FALSE;
	from = to = m_strText = _T("");
	major = 0;
	type1 = 0;
}*/
