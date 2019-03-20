#include "common.h"
#include "include.h"


uint8 imgbuff[CAMERA_SIZE];                             //定义存储接收图像的数组
uint8 img[CAMERA_W*CAMERA_H];                           //定义存储解压后的图像数组（用于读取像素值，图像处理）

uint8 shexiangtou_flag = 0;         //当标志位为1时跑该标志
uint8 dianci_flag = 1;

//函数声明
extern void PORTA_IRQHandler();
extern void DMA0_IRQHandler();


void main(void)               
{   
    led_init(LED3);                         //初始化LED1
    if(shexiangtou_flag == 1) camera_init(imgbuff); //摄像头初始化
    if(dianci_flag == 1) 
    {
      ad_init(); //ad初始化   
      AD_MAX_MIN(); //获取最大最小值
    }          
    printf("system init success11\n");
    duoji_init();     //舵机初始化
    dianji_init();    //电机初始化
    

    //配置中断服务函数
    set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler);   //设置LPTMR的中断服务函数为 PORTA_IRQHandler
    set_vector_handler(DMA0_DMA16_VECTORn , DMA0_IRQHandler);     //设置LPTMR的中断服务函数为 PORTA_IRQHandler

    while(1)
    {
        if(camera == 1)
        {
            if(ov7725_eagle_img_flag == IMG_FINISH)
            {
                Camera_img_deal();           //图像处理
                camera_get_img();           //摄像头获取图像
            }
            if(ov7725_eagle_img_flag == IMG_FAIL)
            {
                camera_get_img();
            }
        }
        
        if(dianci_flag == 1)
        {
            ad_deal();    //ad处理
        }
        
        //luzhang_deal();      //路障处理
        
    }
}

