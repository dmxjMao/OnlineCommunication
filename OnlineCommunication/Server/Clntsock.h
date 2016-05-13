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
	int m_nMsgCount;//��Ϣ���� 
	CSocketFile* m_pFile;//���л��ļ�����
	CArchive* m_pArchiveIn;//���л��������
	CArchive* m_pArchiveOut;//���л��������
	CServerDoc* m_pDoc;//CServerDoc����ָ��
    bool needdel;//�Ƿ�����
	CString name;// �û���
	WORD image;//�û�ͷ��
	WORD major;//�û�רҵ
	WORD type;//��Ϣ����
	WORD type1;//��̳����
// Operations
public:
	//�û��Ƿ�Ͽ�����
	BOOL IsAborted() { return m_pArchiveOut == NULL; }
	BOOL HasConnectionDropped( void );//�Ƿ����
	void Init();//��ʼ��
	void Abort();//�Ͽ�����
	void SendMsg(CMessage* pMsg);//������Ϣ
	void ReceiveMsg(CMessage* pMsg);//������Ϣ
// �����麯�����Խ��յ���Ϣ���д���
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
