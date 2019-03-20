#include "include.h"
#include "common.h"

uint8 send_buff[camera_height*camera_width/GER/8] = {0};

/****************************************************************
*函数名：img_deal
*功能：图像处理
*备注：   
*****************************************************************/
void Camera_img_deal()
{
   img_copy();            //处理成160*70
   Center_line_deal();    //中线处理函数
   duoji_control();       //舵机
   dianji_control();      //电机   定速跑 94% pwm
             
#if 1      //1为开启发送图像的功能  0则关闭图像发送
  img_reduce(img,imgbuff,camera_height*camera_width/GER);      //图像滤波
  vcan_sendimg(imgbuff,camera_height*camera_width/GER/8);  //发送图像  
#endif
}


/****************************************************************
*函数名：img_copy
*功能：图像滤波
*备注：
*****************************************************************/
void img_copy() 
{
    int copy_count = 0;
    for(copy_count = 0;copy_count <camera_height/GER;copy_count++)
    {
        img_extract(&img[copy_count*camera_width],&imgbuff[((28 + 3*copy_count)*OV7725_EAGLE_W)/8],camera_width/8);  //摄像头二值化图像解压
    }
}

/**************************滤波函数*********************************
* 函数名称：img_reduce
* 功能说明：
* 备注：    
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

