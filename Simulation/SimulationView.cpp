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

// SimulationView.cpp : CSimulationView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Simulation.h"
#endif

#include "SimulationDoc.h"
#include "SimulationView.h"

#include "MainFrm.h"


#include "Data.h"

#include "AISCTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSimulationView

IMPLEMENT_DYNCREATE(CSimulationView, CScrollView)

BEGIN_MESSAGE_MAP(CSimulationView, CScrollView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSimulationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON2, &CSimulationView::OnZoomOut)
	ON_COMMAND(ID_BUTTON3, &CSimulationView::OnZoomIn)
	ON_COMMAND(ID_BUTTON4, &CSimulationView::OnButton4)
	ON_COMMAND(ID_BUTTON5, &CSimulationView::OnButton5)
	ON_COMMAND(ID_BUTTON6, &CSimulationView::OnButton6)
	ON_COMMAND(ID_BUTTON7, &CSimulationView::OnButton7)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_32777, &CSimulationView::OnUnDo)
//	ON_WM_LBUTTONDBLCLK()
ON_MESSAGE(BM_GOTDATA_MSG, &CSimulationView::OnBmGotdataMsg)
ON_COMMAND(ID_BUTTON8, &CSimulationView::OnButton8)
ON_COMMAND(ID_BUTTON12, &CSimulationView::OnButton12)
ON_COMMAND(ID_32786, &CSimulationView::OnDisplayX)
ON_COMMAND(ID_32787, &CSimulationView::OnDisplayY)
ON_COMMAND(ID_32788, &CSimulationView::OnDisplayVarName)
ON_COMMAND(ID_32790, &CSimulationView::OnRefuse)
END_MESSAGE_MAP()

// CSimulationView ����/����

CSimulationView::CSimulationView()
{
	// TODO: �ڴ˴���ӹ������

}

CSimulationView::~CSimulationView()
{
}

BOOL CSimulationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	mouse_x=0;
	mouse_y=0;
	mouse_left_x=0;
	mouse_left_y=0;
	left_down=false;
	b_display_name=false;
	return CScrollView::PreCreateWindow(cs);
}

// CSimulationView ����

void CSimulationView::OnDraw(CDC* pDC)
{
	CSimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Data *pData=Data::shareData();
	int left,right,top,bottom;
	CRect rect;
	GetClientRect(&rect);
	
	left=rect.left+GetScrollPos(SB_HORZ);
	right=rect.right+GetScrollPos(SB_HORZ);
	top=rect.top+GetScrollPos(SB_VERT);
	bottom=rect.bottom+GetScrollPos(SB_VERT);
	
	CRect rect2;
	rect2.SetRect(left,top,right,bottom);

	for(int i=0;i<pData->data_num;i++)
	{
		pDC->SetTextColor(RGB(255,0,0));
		CPen* pPen ; //����һ֧�µı�
		pPen=new CPen ;
		pPen->CreatePen(PS_SOLID,1,pData->pData_info[i].color) ;
		pDC->SelectObject(pPen) ;
		bool b_name=false;
		for(int j=0;j<MAX_DATA_NUM;j++)
		{
			
			int x,y,x1,y1,data;
			bool res;
			
			res=pData->getPointFromIndex(i,j,&x1,&y1,&x,&y,&data);
			if(rect2.PtInRect(CPoint(x,y)) || rect2.PtInRect(CPoint(x1,y1)))
			{
				
				pDC->MoveTo(x1,y1);
				pDC->LineTo(x,y1);
				pDC->LineTo(x,y);
				if(res==true)
				{
					CString str;
					str.Format(_T("%d"),data);
					
					pDC->TextOutW(x+5,y-20,str);
				}

				if(b_name==false && b_display_name ==true)
				{
					
					b_name=true;
					pDC->TextOutW(x+5,y-20,pData->pData_info[i].node_name);
				}
				
			}
		}
		pPen->DeleteObject();
		delete pPen;
		pData->drawXY(i,pDC,rect2);
		
	}

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CSimulationView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CRect rect;
	GetClientRect(&rect);
	CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = rect.right;
	sizeTotal.cy = rect.bottom;
	SetScrollSizes(MM_TEXT, sizeTotal);
	scroll_pos_x=0;
	scroll_pos_y=0;
	SetScrollPos(SB_VERT,scroll_pos_y);
	SetScrollPos(SB_HORZ,scroll_pos_x);
	//printf("cx:%d,cy:%d,x:%d,y%d\n",sizeTotal.cx,sizeTotal.cx,scroll_pos_x,scroll_pos_y);
}


// CSimulationView ��ӡ


void CSimulationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSimulationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CSimulationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSimulationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


//�ػ溯��
void CSimulationView::updatePaint(bool undo)
{
	if(undo==false)
	{
	SCROLLINFO sizeTotal_old_y;
	SCROLLINFO sizeTotal_old_x;
	
	GetScrollInfo(SB_VERT,&sizeTotal_old_y);
	GetScrollInfo(SB_HORZ,&sizeTotal_old_x);
	scroll_pos_y=sizeTotal_old_y.nPos;
	scroll_pos_x=sizeTotal_old_x.nPos;
	float posX=((float)scroll_pos_x/sizeTotal_old_x.nMax);
	float posY=((float)scroll_pos_y/sizeTotal_old_y.nMax);
	
	CSize sizeTotal;	
	Data *pData=Data::shareData();
	pData->getScrollRange(&sizeTotal.cx,&sizeTotal.cy);
	SetScrollSizes(MM_TEXT, sizeTotal);

	SetScrollPos(SB_VERT,(int)(sizeTotal.cy*posY));
	SetScrollPos(SB_HORZ,(int)(sizeTotal.cx*posX));


	}else
	{
		CSize sizeTotal;	
		Data *pData=Data::shareData();
		pData->getScrollRange(&sizeTotal.cx,&sizeTotal.cy);
		SetScrollSizes(MM_TEXT, sizeTotal);

		SetScrollPos(SB_VERT,scroll_pos_y);
		SetScrollPos(SB_HORZ,scroll_pos_x);
	}

	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect);
}



// CSimulationView ���

#ifdef _DEBUG
void CSimulationView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSimulationView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}






CSimulationDoc* CSimulationView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimulationDoc)));
	return (CSimulationDoc*)m_pDocument;
}
#endif //_DEBUG


// CSimulationView ��Ϣ�������

//Y�Ŵ�
void CSimulationView::OnZoomOut()
{
	// TODO: �ڴ���������������
	Data *pData=Data::shareData();
	
	

	pData->scanlingYplus();

	//Invalidate();
	updatePaint();

}

//Y��С
void CSimulationView::OnZoomIn()
{
	// TODO: �ڴ���������������
	Data *pData=Data::shareData();

	pData->scanlingYsub();

	//Invalidate();
	updatePaint();
}

//X�Ŵ�
void CSimulationView::OnButton4()
{
	// TODO: �ڴ���������������
	Data *pData=Data::shareData();

	pData->scanlingXplus();
;
	//Invalidate();
	updatePaint();
}

//X��С
void CSimulationView::OnButton5()
{
	// TODO: �ڴ���������������
	Data *pData=Data::shareData();

	pData->scanlingXsub();

	//Invalidate();
	updatePaint();

}

//����Ŵ�
void CSimulationView::OnButton6()
{
	// TODO: �ڴ���������������
	Data *pData=Data::shareData();

	pData->scanlingXplus();
	pData->scanlingYplus();


	updatePaint();
}


//������С
void CSimulationView::OnButton7()
{
	// TODO: �ڴ���������������
	Data *pData=Data::shareData();

	pData->scanlingXsub();
	pData->scanlingYsub();

	//Invalidate();
	updatePaint();

}



//����ƶ�
void CSimulationView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ


	CDC *pDC=GetDC();
	CRect rect;
	GetClientRect(&rect); 

	int nDrawmode = pDC->SetROP2(R2_NOT);
	if(rect.PtInRect(point) && left_down==true)
	{
		
		
		
		pDC->MoveTo(0,mouse_y);
		pDC->LineTo(5000,mouse_y);

		pDC->MoveTo(mouse_x,0);
		pDC->LineTo(mouse_x,8000);
		
		pDC->MoveTo(0,point.y);
		pDC->LineTo(5000,point.y);

		pDC->MoveTo(point.x,0);
		pDC->LineTo(point.x,8000);


		mouse_x=point.x;
		mouse_y=point.y;
		CString str;
		str.Format(_T("�ƶ�����: X:%ld Y:%ld"),point.x,point.y);
		sendMessageToOutput(1,str,false);
		
		
	}
	
	pDC->SetROP2(nDrawmode);
	ReleaseDC(pDC);
	
	CScrollView::OnMouseMove(nFlags, point);
}


void CSimulationView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC=GetDC();
	CRect rect;
	GetClientRect(&rect); 
	if(rect.PtInRect(point))
	{
		
		
		
		pDC->MoveTo(0,point.y);
		pDC->LineTo(5000,point.y);

		pDC->MoveTo(point.x,0);
		pDC->LineTo(point.x,8000);

		mouse_left_x=point.x;
		mouse_left_y=point.y;
		
		left_down=true;
		CString str;
		str.Format(_T("��ʼ����: X:%ld Y:%ld"),point.x,point.y);
		sendMessageToOutput(1,str,true);

		sendMessageToOutput(1,_T(" "),true);
	}
	
	ReleaseDC(pDC);
	CScrollView::OnLButtonDown(nFlags, point);
	
	//COutputList* prt =RUNTIME_CLASS(COutputList);
	
	
}


void CSimulationView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//printf("X:%d,Y:%d\n",point.x,point.y);
	CDC *pDC=GetDC();
	left_down=false;
	if(abs(point.x-mouse_left_x)>10)
	{
		int scal_x=abs(point.x-mouse_left_x);
		int scal_y=abs(point.y-mouse_left_y);
		
		
		float left,top;
		CRect rect;
		GetClientRect(&rect); 


		Data *pData=Data::shareData();
		pData->scalingXY((float)rect.right/scal_x,(float)rect.bottom/scal_y);

		int nDrawmode = pDC->SetROP2(R2_NOT);
		if(rect.PtInRect(point))
		{
		
		
		
			pDC->MoveTo(0,mouse_left_y);
			pDC->LineTo(5000,mouse_left_y);

			pDC->MoveTo(mouse_left_x,0);
			pDC->LineTo(mouse_left_x,8000);
		

			pDC->MoveTo(0,mouse_y);
			pDC->LineTo(5000,mouse_y);

			pDC->MoveTo(mouse_x,0);
			pDC->LineTo(mouse_x,8000);

		
			mouse_x=0;
			mouse_y=0;
			CString str;
			str.Format(_T("��������: X:%ld Y:%ld"),point.x,point.y);
			sendMessageToOutput(1,str,false);
			sendMessageToOutput(1,_T(" "),true);
		
		}
	
		pDC->SetROP2(nDrawmode);
		ReleaseDC(pDC);
		CScrollView::OnLButtonUp(nFlags, point);

	
		left=(float)(rect.left+GetScrollPos(SB_HORZ)+mouse_left_x);
		top=(float)(rect.top+GetScrollPos(SB_VERT)+mouse_left_y);
	
		SCROLLINFO si_v;
		GetScrollInfo(SB_VERT,&si_v);

		SCROLLINFO si_h;
		GetScrollInfo(SB_HORZ,&si_h);

		scroll_pos_x=si_h.nPos;
		scroll_pos_y=si_v.nPos;


		left=left/si_h.nMax;
		top=top/si_v.nMax;
		CSize sizeTotal;	
		pData->getScrollRange(&sizeTotal.cx,&sizeTotal.cy);
		SetScrollSizes(MM_TEXT, sizeTotal);
		SetScrollPos(SB_VERT,(int)(top*sizeTotal.cy));
		SetScrollPos(SB_HORZ,(int)(left*sizeTotal.cx));

		mouse_left_x=0;
		mouse_left_y=0;
		
		
		InvalidateRect(rect);
		//updatePaint();
	}else
	{
		int nDrawmode = pDC->SetROP2(R2_NOT);
		pDC->MoveTo(0,mouse_left_y);
		pDC->LineTo(5000,mouse_left_y);

		pDC->MoveTo(mouse_left_x,0);
		pDC->LineTo(mouse_left_x,8000);
		

		pDC->MoveTo(0,mouse_y);
		pDC->LineTo(5000,mouse_y);

		pDC->MoveTo(mouse_x,0);
		pDC->LineTo(mouse_x,8000);

		
		mouse_x=0;
		mouse_y=0;
		mouse_left_x=0;
		mouse_left_y=0;
		pDC->SetROP2(nDrawmode);
		ReleaseDC(pDC);
	}
}



//����
void CSimulationView::OnUnDo()
{
	// TODO: �ڴ���������������
	Data *pData=Data::shareData();
	pData->scalingUndo();
	
	updatePaint(true);
	sendMessageToOutput(1,_T("��������..."),true);

}


void CSimulationView::sendMessageToOutput(int num,LPCTSTR info,bool display)
{
	CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	pFrame->sendInformation(num,info,display);
}


//void CSimulationView::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CScrollView::OnLButtonDblClk(nFlags, point);
//}


afx_msg LRESULT CSimulationView::OnBmGotdataMsg(WPARAM wParam, LPARAM lParam)
{
	updatePaint(true);
	return 0;
}


//����Ӧ�ó���
void CSimulationView::OnButton8()
{
	// TODO: �ڴ���������������
	AISCTest();

}


void CSimulationView::OnButton12()
{
	// TODO: �ڴ���������������
	AISCTestStop();
}


void CSimulationView::OnDisplayX()
{
	// TODO: �ڴ���������������// TODO: �ڴ���������������
	Data *pData=Data::shareData();
	pData->EnableX();
	updatePaint();
	
}


void CSimulationView::OnDisplayY()
{
	// TODO: �ڴ���������������
	Data *pData=Data::shareData();
	pData->EnableY();
	updatePaint();
}


void CSimulationView::OnDisplayVarName()
{
	// TODO: �ڴ���������������
	if(b_display_name)
		b_display_name=false;
	else
		b_display_name=true;

	updatePaint();
}


void CSimulationView::OnRefuse()
{
	// TODO: �ڴ���������������
	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(rect);
}
