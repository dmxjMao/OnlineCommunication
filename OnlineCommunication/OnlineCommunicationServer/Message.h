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
	void Serialize(CArchive& ar);//���л�
	CMessage();//���캯��
	virtual ~CMessage();//��������
//	void Reset();//����
public:	
	CString m_strText;//��Ϣ�ı�
	CString from;//�����û�
	CString to;//�����û�
	COLORREF color;//������ɫ
	BOOL secret;//�����ġ���־λ
	BOOL m_bClose;//�����ˡ���ʶ
	int type;//��Ϣ��ʶ
	WORD image;//ͷ���ʶ
	WORD major;//רҵ��ʶ
	WORD type1;//��̳���ͱ�ʶ
};

#endif // !defined(AFX_MESSAGE_H__A0DEE46E_8D70_4E1D_B26A_A7CA33DCFE07__INCLUDED_)
