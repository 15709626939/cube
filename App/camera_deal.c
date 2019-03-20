#include "include.h"
#include "common.h"

uint8 send_buff[camera_height*camera_width/GER/8] = {0};

/****************************************************************
*��������img_deal
*���ܣ�ͼ����
*��ע��   
*****************************************************************/
void Camera_img_deal()
{
   img_copy();            //�����160*70
   Center_line_deal();    //���ߴ�����
   duoji_control();       //���
   dianji_control();      //���   ������ 94% pwm
             
#if 1      //1Ϊ��������ͼ��Ĺ���  0��ر�ͼ����
  img_reduce(img,imgbuff,camera_height*camera_width/GER);      //ͼ���˲�
  vcan_sendimg(imgbuff,camera_height*camera_width/GER/8);  //����ͼ��  
#endif
}


/****************************************************************
*��������img_copy
*���ܣ�ͼ���˲�
*��ע��
*****************************************************************/
void img_copy() 
{
    int copy_count = 0;
    for(copy_count = 0;copy_count <camera_height/GER;copy_count++)
    {
        img_extract(&img[copy_count*camera_width],&imgbuff[((28 + 3*copy_count)*OV7725_EAGLE_W)/8],camera_width/8);  //����ͷ��ֵ��ͼ���ѹ
    }
}

/**************************�˲�����*********************************
* �������ƣ�img_reduce
* ����˵����
* ��ע��    
***********************************************************************/
void img_reduce(uint8 *aim,uint8 *get,uint32 length)
{
    while(length>0)
    {
      *get = 0;
      *get += ((*aim++) & 0x80) >> 0;
      *get += ((*aim++) & 0x80) >> 1;
      *get += ((*aim++) & 0x80) >> 2;
      *get += ((*aim++) & 0x80) >> 3;
      *get += ((*aim++) & 0x80) >> 4;
      *get += ((*aim++) & 0x80) >> 5;
      *get += ((*aim++) & 0x80) >> 6;
      *get += ((*aim++) & 0x80) >> 7;
      *get =~ *get;
      get++;
      length -= 8;
  }
}

