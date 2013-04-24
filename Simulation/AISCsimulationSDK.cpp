#include "stdafx.h"
//
#include "resource.h"
#include "AISCsimulationSDK.h"
//#include "SimulationView.h"
#include "Data.h"
#include <math.h>

#include "MainFrm.h"

//#define BM_DATA_RECIVE (WM_USER + 100)



//��ʼ��������
bool createSimulation(LPCTSTR name,  //��Ҫ������ļ���
					  int data_num   //���ݸ���
					  )
{
	Data* my_data=Data::shareData(name);
	my_data->configureData(data_num);
	return true;

}



//���÷�����
bool configureSimulation(bool enabled,               //�Ƿ�����������
						 bool write_to_file,		  //�Ƿ񱣴�������Ϣ���ļ�
						 bool real_time_simulation   //�Ƿ��������ʵʱ����
						)
{
	sendMessageToSimulation(0x9001,0);
	return true;
}



//���ñ�����Ϣ
bool configureValue(LPCTSTR value_name, //��������
					int ID,				//����ID��ID0Ϊʱ���ź�
					int weight,			//λ��
					bool sigh,			//�Ƿ��з���
					COLORREF color
					)
{
	Data *pData=Data::shareData();

	int max,min;

	max=pow(2.0,weight-1);
	min=0-max;

	pData->configureValueInfo(value_name,ID,max,min,color);

	return true;
}








//���ͱ���
bool sendMessageToSimulation(int index,  //����ID
							 int data    //��������
							 )
{
	Data* pData=Data::shareData();
	int new_data=0;
	if(pData->pData_info[index].node_sigh==true)
	{
		new_data=data;
	}else
	{
		new_data=data-(int)pow(2.0,pData->pData_info[index].node_len);
	}


	pData->addData((int)index,(int)data);

	

	if(index==0)
	{
		pData->moveNext();
	}



	/*CMainFrame* pFrame  =  (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	::SendMessage(pFrame->GetSafeHwnd(),BM_DATA_RECIVE,index,new_data);*/
	return true;

}















//�ú�������
bool setValueMaxAndMin(LPCTSTR value_name, //��������
					   int ID,				//����ID��ID0Ϊʱ���ź�
					   int max,
					   int min,
					   COLORREF color)
{
	Data *pData=Data::shareData();
	pData->configureValueInfo(value_name,ID,max,min,color);
	return true;

}