// RealPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Simulation.h"
#include "RealPage.h"
#include "afxdialogex.h"


// CRealPage �Ի���

IMPLEMENT_DYNAMIC(CRealPage, CPropertyPage)

CRealPage::CRealPage()
	: CPropertyPage(CRealPage::IDD)
{

}

CRealPage::~CRealPage()
{
}

void CRealPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}



void CRealPage::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPropertyPage::OnPaint();
	}
}



BEGIN_MESSAGE_MAP(CRealPage, CPropertyPage)
END_MESSAGE_MAP()


// CRealPage ��Ϣ�������
