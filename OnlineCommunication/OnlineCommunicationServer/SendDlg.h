#pragma once


// CSendDlg dialog
class COnlineCommunicationServerDoc;
class CSendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSendDlg)

public:
	CSendDlg(CWnd* pParent = NULL);
	CSendDlg(COnlineCommunicationServerDoc* pDoc, CWnd* pParent = NULL);   // standard constructor
	virtual ~CSendDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	COnlineCommunicationServerDoc*		m_pDoc;
	afx_msg void OnClickedButtonColor();
	afx_msg void OnPaint();
};
