// clntsock.h : interface of the CClientSocket class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __CLNTSOCK_H__
#define __CLNTSOCK_H__

class CMessage;
class CServerDoc;

class CClientSocket : public CSocket
{
	DECLARE_DYNAMIC(CClientSocket);
private:
	CClientSocket(const CClientSocket& rSrc);         // no implementation
	void operator=(const CClientSocket& rSrc);		  // no implementation

// Construction
public:
	CClientSocket(CServerDoc* m_pDoc);

// Attributes
public:
	int m_nMsgCount;//消息个数 
	CSocketFile* m_pFile;//串行化文件对象
	CArchive* m_pArchiveIn;//串行化输入对象
	CArchive* m_pArchiveOut;//串行化输出对象
	CServerDoc* m_pDoc;//CServerDoc对象指针
    bool needdel;//是否屏蔽
	CString name;// 用户名
	WORD image;//用户头像
	WORD major;//用户专业
	WORD type;//消息代码
	WORD type1;//论坛类型
// Operations
public:
	//用户是否断开连接
	BOOL IsAborted() { return m_pArchiveOut == NULL; }
	BOOL HasConnectionDropped( void );//是否吊线
	void Init();//初始化
	void Abort();//断开连接
	void SendMsg(CMessage* pMsg);//发送消息
	void ReceiveMsg(CMessage* pMsg);//接收消息
// 重载虚函数，对接收的消息进行处理
protected:
	virtual void OnReceive(int nErrorCode);

// Implementation
public:		
	virtual ~CClientSocket();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

#endif // __CLNTSOCK_H__
