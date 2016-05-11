// Message.h: interface for the CMessage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
#define AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMessage : public CObject  
{
public:
	void Serialize(CArchive& ar);//序列化
	CMessage();//构造函数
	virtual ~CMessage();//析构函数
//	void Reset();//重置
public:	
	CString m_strText;//消息文本
	CString from;//发送用户
	CString to;//接收用户
	COLORREF color;//字体颜色
	BOOL secret;//“悄悄”标志位
	BOOL m_bClose;//“过滤”标识
	int type;//消息标识
	WORD image;//头像标识
	WORD major;//专业标识
	WORD type1;//论坛类型标识
};

#endif // !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
