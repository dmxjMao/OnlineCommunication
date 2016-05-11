#pragma once


// CUserList

class CUserList : public CListCtrl
{
	DECLARE_DYNAMIC(CUserList)

public:
	CUserList();
	virtual ~CUserList();

	void AddItem();
	void RemoveItem();

protected:
	DECLARE_MESSAGE_MAP()

	CImageList		m_imgList;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
};


