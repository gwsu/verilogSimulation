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

#include "stdafx.h"
#include "ViewTree.h"

#include "Data.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTree

CViewTree::CViewTree()
{
	g_fDragging=FALSE;
}

CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, &CViewTree::OnTvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTree ��Ϣ�������

BOOL CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}


void CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CTreeCtrl* pTreeCtrl = this;
 //CPoint ptCurSel(0,0);
 //TVHITTESTINFO HitTestInfo;
 //// ͨ������ڿͻ����е�λ��
 //GetCursorPos(&ptCurSel);
 //pTreeCtrl->ScreenToClient(&ptCurSel);  
 //// ��ȡ��ǰѡ�������һ��
 //HitTestInfo.pt = ptCurSel;  
 //HTREEITEM hSelect = pTreeCtrl->HitTest(&HitTestInfo);
 //
 //if(hSelect != NULL)
 //{
 // CString strItem = pTreeCtrl->GetItemText(hSelect);
 // ::AfxMessageBox( strItem);
 //}
 //// ���ø���Ϊѡ��״̬
 //pTreeCtrl->SelectItem(hSelect);
  
 //���·�����ȡ������һ�δ���ѡ��״̬�������Ƚ�����Ķ���ѡ��
 //CTreeCtrl* pTreeCtrl = this;
 //HTREEITEM hSelect = pTreeCtrl->GetSelectedItem();
 //HTREEITEM hLight = pTreeCtrl->GetDropHilightItem();
 //if((hLight != NULL) && (hSelect != hLight))
 // hSelect = hLight;
 //if(hSelect   ==   NULL)
 // return;
 //pTreeCtrl->SelectItem(hSelect);
 //
 ////pTreeCtrl->GetIndent();
 //printf("hSelect:%d\n",hSelect);
 ////�༭��ǰѡ�ж�������
 //pTreeCtrl->EditLabel(hSelect);
 //if( NULL != hSelect )
 //{
 // CString strItem = pTreeCtrl->GetItemText(hSelect);
 // /*if(strItem == _T("������"));
 // {
 //  pTreeCtrl->SetItemText(hSelect, _T("�ı��Ŀ�����"));
 // }*/
 // ::AfxMessageBox( strItem); 
 //}
 
 *pResult = 0;
	
}


void CViewTree::OnTvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

	//����������϶������������
	if( (GetTickCount() - m_dwDragStart) < DRAG_DELAY )
		return;

	m_hItemDragS = pNMTreeView->itemNew.hItem;
	m_hItemDragD = NULL;

	//�õ������϶�ʱ��ʾ��ͼ���б�
	m_pDragImage = CreateDragImage( m_hItemDragS );
	if( !m_pDragImage )
		return;

	m_bDragging = true;
	m_pDragImage->BeginDrag ( 0,CPoint(8,8) );
	CPoint  pt = pNMTreeView->ptDrag;
	ClientToScreen( &pt );
	m_pDragImage->DragEnter ( this,pt );  //"this"���϶����������ڸô���
	SetCapture();

	m_nScrollTimerID = SetTimer( 2,40,NULL );
}


void CViewTree::Main_OnBeginDrag(HWND hwndTV, LPNMTREEVIEW lpnmtv) 
{ 
    
    return;
}

void CViewTree::Main_OnMouseMove(HWND hwndParent, HWND hwndTV, LONG xCur, LONG yCur) 
{ 
    
    return; 
}

void CViewTree::OnMouseMove(UINT nFlags, CPoint point)
{
	HTREEITEM  hItem;
	UINT       flags;

	//���������ж�ʱ���Ƿ����,���������ɾ��,ɾ�����ٶ�ʱ
	if( m_nHoverTimerID )
	{
		KillTimer( m_nHoverTimerID );
		m_nHoverTimerID = 0;
	}
	m_nHoverTimerID = SetTimer( 1,800,NULL );  //��ʱΪ 0.8 �����Զ�չ��
	m_HoverPoint = point;

	if( m_bDragging )
	{
		CPoint  pt = point;
		CImageList::DragMove( pt );

		//��꾭��ʱ������ʾ
		CImageList::DragShowNolock( false );  //������꾭��ʱ�����ѿ��ĺۼ�
		if( (hItem = HitTest(point,&flags)) != NULL )
		{
			SelectDropTarget( hItem );
			m_hItemDragD = hItem;
		}
		CImageList::DragShowNolock( true );

		//����Ŀ����ҷ�����Եʱ������Ŀ���ڸ���
		CRect  rect;
		GetClientRect( &rect );
		if( point.x < rect.left + 20 )
			m_hItemDragD = NULL;
	}
	CTreeCtrl::OnMouseMove(nFlags, point);
}


void CViewTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	CTreeCtrl::OnLButtonUp(nFlags, point);

	if( m_bDragging )
	{
		m_bDragging = FALSE;
		CImageList::DragLeave( this );
		CImageList::EndDrag();
		ReleaseCapture();
		delete m_pDragImage;

		SelectDropTarget( NULL );
		
		if( m_hItemDragS == m_hItemDragD )
		{
			KillTimer( m_nScrollTimerID );
			return;
		}

		Expand( m_hItemDragD,TVE_EXPAND );
		HTREEITEM  htiParent = m_hItemDragD;
		htiParent = GetParentItem(htiParent);

		/*MessageBox(GetItemText(m_hItemDragD));
		MessageBox(GetItemText(GetChildItem(m_hItemDragD)));
		MessageBox(GetItemText(GetChildItem(m_hItemDragD)));
		MessageBox(GetItemText(GetChildItem(m_hItemDragD)));
		MessageBox(GetItemText(GetChildItem(m_hItemDragD)));*/
		////������ɸ��ڵ������ӽڵ�
		//while( (htiParent = GetParentItem(htiParent)) != NULL )
		//{
		//	if( htiParent == m_hItemDragS )
		//	{
		//		//����һ����ʱ�ڵ�����ɲ���
		//		HTREEITEM  htiNewTemp = CopyBranch( m_hItemDragS,NULL,TVI_LAST );
		//		HTREEITEM  htiNew = CopyBranch( htiNewTemp,m_hItemDragD,TVI_LAST );
		//		DeleteItem( htiNewTemp );
		//		SelectItem( htiNew );
		//		KillTimer( m_nScrollTimerID );
		//		return;
		//	}
		//}

		HTREEITEM  htiNew = CopyBranch( m_hItemDragS,htiParent,m_hItemDragD );
		HTREEITEM  oldNew = CopyBranch( m_hItemDragD,htiParent,m_hItemDragS );
		
		Data *pDate=Data::shareData();
		int tmp=pDate->pData_info[_ttoi(GetItemText(GetChildItem(htiNew)))].node_sort;
		pDate->pData_info[_ttoi(GetItemText(GetChildItem(htiNew)))].node_sort=pDate->pData_info[_ttoi(GetItemText(GetChildItem(oldNew)))].node_sort;
		pDate->pData_info[_ttoi(GetItemText(GetChildItem(oldNew)))].node_sort=tmp;

		//AfxGetMainWnd()->GetActiveView()->SendMessage()
		CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
		pFrame->GetActiveView()->SendMessage(BM_GOTDATA_MSG);
		DeleteItem( m_hItemDragS );
		DeleteItem( m_hItemDragD );
		SelectItem( htiNew );
		KillTimer( m_nScrollTimerID );
	}
	CTreeCtrl::OnLButtonUp(nFlags, point);
}



//������Ŀ
HTREEITEM CViewTree::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	TV_INSERTSTRUCT  tvstruct;
	HTREEITEM        hNewItem;
	CString          sText;

	//�õ�Դ��Ŀ����Ϣ
	tvstruct.item.hItem = hItem;
	tvstruct.item.mask  = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	GetItem( &tvstruct.item );
	sText = GetItemText( hItem );
	tvstruct.item.cchTextMax = sText.GetLength ();
	tvstruct.item.pszText    = sText.LockBuffer ();

	//����Ŀ���뵽���ʵ�λ��
	tvstruct.hParent         = htiNewParent;
	tvstruct.hInsertAfter    = htiAfter;
	tvstruct.item.mask       = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	hNewItem = InsertItem( &tvstruct );
	sText.ReleaseBuffer ();

	//���ƿ�����Ŀ���ݺ���Ŀ״̬
	SetItemData( hNewItem,GetItemData(hItem) );
	SetItemState( hNewItem,GetItemState(hItem,TVIS_STATEIMAGEMASK),TVIS_STATEIMAGEMASK);

	return hNewItem;
}

//������֧
HTREEITEM CViewTree::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
	HTREEITEM  hChild;
	HTREEITEM  hNewItem = CopyItem( htiBranch,htiNewParent,htiAfter );
	hChild = GetChildItem( htiBranch );
	
	//printf("%s",GetItemText(hChild));
	while( hChild != NULL )
	{
		CopyBranch( hChild,hNewItem,htiAfter );
		hChild = GetNextSiblingItem( hChild );
		
	}

	return  hNewItem;
}

