

#ifndef _AISC_SIM_SDK_
#define _AISC_SIM_SDK_



#define DISPLAY_VAULE	0x9001




//��ɫ����
#define COLOR_RED	RGB(255,0,0)
#define COLOR_BLUE	RGB(0,0,255)
#define COLOR_GREEN RGB(0,255,0)
#define COLOR_BLACK	RGB(0,0,0)
#define COLOR_PALEV RGB(219,112,147) //palevioletred������ĵ��Ϻ죩  
#define COLOR_PINK  RGB(255,105,180) //pink������ķۺ죩   




//��ʼ��������
bool createSimulation(LPCTSTR name,  //��Ҫ������ļ���
					  int data_num   //���ݸ���
					  );



//���÷�����
bool configureSimulation(bool enabled=true,               //�Ƿ�����������
						 bool write_to_file=true,		  //�Ƿ񱣴�������Ϣ���ļ�
						 bool real_time_simulation=true   //�Ƿ��������ʵʱ����
						);




//���ñ�����Ϣ
bool configureValue(LPCTSTR value_name, //��������
					int ID,				//����ID��ID0Ϊʱ���ź�
					int weight,			//λ��
					bool sigh,			//�Ƿ��з���
					COLORREF color=RGB(255,0,0)	//��ɫ
					);



//���ͱ���
bool sendMessageToSimulation(int index,  //����ID
							 int data    //��������
							 );






//���ñ����������Сֵ���Ѿ�����
bool setValueMaxAndMin(LPCTSTR value_name, //��������
					   int ID,				//����ID��ID0Ϊʱ���ź�
					   int max,
					   int min,
					   COLORREF color=RGB(255,0,0));




#endif