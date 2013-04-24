#pragma once


//���ݸ�ʽ
typedef struct _node_
{
	int data_x;
	int data_y;
	int pos_x;
	int pos_y;

}NODE,*PNODE;


//������Ϣ
typedef struct _node_info_
{
	LPCTSTR node_name; //����
	int node_id;		//ID
	int node_sort;		//����λ��
	COLORREF color;		//��ɫ
	int node_max;		//���ֵ
	int node_min;		//��Сֵ
	int node_len;		//λ��
	bool node_sigh;		//�Ƿ��з���
	bool display;		//�Ƿ���ʾ

}NODE_INFO,*PNODE_INFO;

//������ݶ�ȡ����
#define MAX_DATA_NUM	100000






class Data
{
public:
	Data(void);
	~Data(void);
	Data(LPCTSTR m_file_name);

	typedef enum
	{
		kStart=0,
		kNext,
		kPre
	}FileReadStatus;

	//�������ݸ�ʽ
	bool configureData(int m_data_num);

	//���ñ�����Ϣ
	bool configureValueInfo(LPCTSTR value_name, //��������
							int ID,				//����ID��ID0Ϊʱ���ź�
							int max,			//���ֵ
							int min,				//��Сֵ
							COLORREF color);

	//��ȡ�ļ�
	bool ReadFile();

	//��ȡ��һ���ļ�
	bool ReadNextFile(FileReadStatus type);


	//�ļ�ƫ��
	long file_offset;
	//x����ƫ��
	int  pos_x_offset;

	//д���ļ�
	bool WriteFile();

	//�������
	bool addData(int index,int data);

	//�ƶ�����һ����
	bool moveNext();

	//���������ᣬ���ݷŴ���С�ʾ������ƾ���
	bool drawXY(int m_index_num,CDC *pDC,CRect rect);



	//��ȡָ����������Ļ����
	bool getPointFromIndex(int m_index_num,   //����������
						   int m_index_data,  //��������
						   int *x1,			  //ǰһ��x����
						   int *y1,			  //ǰһ��y����
						   int *x,			  //x����
						   int *y,			  //y����
						   int *data          //yֵ
						   );			 


	static Data *shareData(LPCTSTR m_file_name=NULL);


	void scanlingYplus(){scaling_old_y=scaling_y;scaling_y=scaling_y*1.2F;};
	void scanlingYsub(){scaling_old_y=scaling_y;scaling_y=scaling_y*0.8F;};
	void scanlingXplus(){scaling_old_x=scaling_x;scaling_x=scaling_x*1.2F;};
	void scanlingXsub(){scaling_old_x=scaling_x;scaling_x=scaling_x*0.8F;};
	void scalingXY(float sx,float sy){scaling_old_y=scaling_y;scaling_old_x=scaling_x;scaling_x=scaling_x*sx;scaling_y=scaling_y*sy;}
	void scalingUndo(){scaling_x=scaling_old_x;scaling_y=scaling_old_y;};



	//��������ֵ�Ƿ���ʾ
	void EnableX(){if(display_x==true)display_x=false;else display_x=true;};
	void EnableY(){if(display_y==true)display_y=false;else display_y=true;};

	void getScrollRange(long *height,long *weith);


public:

	

	//���ݸ���
	int data_num;
	//������Ϣ
	NODE_INFO *pData_info;


private:
	LPCTSTR file_name;


	//����
	NODE *pData;

	//д�ļ�����
	NODE *pWriteData;
	//��ʱ���ݣ����ڻ���һ������
	NODE *pTmpData;
	//���ݼ���
	int count;

	

	//�Ŵ���С����
	float scaling_x;
	float scaling_y;

	float scaling_old_x;
	float scaling_old_y;



	//�Ƿ���ʾ������
	bool display_x;

	//�Ƿ���ʾ����ֵ
	bool display_y;

private:
	//�任����
	//ƽ�Ʊ任����
	bool translateTransformedMatrix(int m_index_num,   //����������
									int m_index_data   //��������;
									);


	bool scalingMatrix(int m_index_num,   //����������
					   int m_index_data   //��������;
					   );




};

