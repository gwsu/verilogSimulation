// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// SimulationDoc.cpp : CSimulationDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Simulation.h"
#endif

#include "SimulationDoc.h"

#include "MainFrm.h"
#define BM_GOTDATA_MSG (WM_USER + 200)

#include "Data.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSimulationDoc

IMPLEMENT_DYNCREATE(CSimulationDoc, CDocument)

BEGIN_MESSAGE_MAP(CSimulationDoc, CDocument)
	ON_COMMAND(ID_BUTTON10, &CSimulationDoc::OnButton10)
	ON_COMMAND(ID_BUTTON13, &CSimulationDoc::OnReadNext)
END_MESSAGE_MAP()


// CSimulationDoc ����/����

CSimulationDoc::CSimulationDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CSimulationDoc::~CSimulationDoc()
{
}

BOOL CSimulationDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CSimulationDoc ���л�

void CSimulationDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
		pData=Data::shareData(_T("d:\\a.dat"));
		pData->configureData(20);
		pData->ReadFile();
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CSimulationDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CSimulationDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CSimulationDoc::SetSearchContent(const CString& value)
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

// CSimulationDoc ���

#ifdef _DEBUG
void CSimulationDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSimulationDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSimulationDoc ����


void CSimulationDoc::OnButton10()
{
	// TODO: �ڴ���������������
	pData=Data::shareData();
	//pData->configureData(20);
	pData->ReadNextFile(Data::kStart);
	CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	pFrame->SendMessage(BM_DATA_RECIVE,0x9001,0);
	pFrame->GetActiveView()->SendMessage(BM_GOTDATA_MSG);
}


void CSimulationDoc::OnReadNext()
{
	// TODO: �ڴ���������������
	pData=Data::shareData();
	//pData->configureData(20);
	pData->ReadNextFile(Data::kNext);
	CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	pFrame->GetActiveView()->SendMessage(BM_GOTDATA_MSG);
}
