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

// SimulationView.h : CSimulationView ��Ľӿ�
//

#pragma once

#define BM_GOTDATA_MSG (WM_USER + 200)

class CSimulationView : public CScrollView
{
protected: // �������л�����
	CSimulationView();
	DECLARE_DYNCREATE(CSimulationView)

// ����
public:
	CSimulationDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CSimulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


private:
	int mouse_y;
	int mouse_x;

	//����������ʱ������
	//CPoint left_down_point;
	int mouse_left_x;
	int mouse_left_y;
	bool left_down;


	//scrollλ��
	long scroll_pos_x;
	long scroll_pos_y;

	void updatePaint(bool undo=false);

	//��ʾ������
	bool b_display_name;


	//������Ϣ��outputWnd
	void sendMessageToOutput(int num,LPCTSTR info,bool display);

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnZoomOut();
	afx_msg void OnZoomIn();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnUnDo();
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT OnBmGotdataMsg(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnButton8();
	afx_msg void OnButton12();
	afx_msg void OnDisplayX();
	afx_msg void OnDisplayY();
	afx_msg void OnDisplayVarName();
	afx_msg void OnRefuse();
};

#ifndef _DEBUG  // SimulationView.cpp �еĵ��԰汾
inline CSimulationDoc* CSimulationView::GetDocument() const
   { return reinterpret_cast<CSimulationDoc*>(m_pDocument); }
#endif

