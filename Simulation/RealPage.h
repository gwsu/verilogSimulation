#pragma once

#include "resource.h"
// CRealPage �Ի���

class CRealPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CRealPage)

public:
	CRealPage();
	virtual ~CRealPage();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_MEDIUM };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()
};
