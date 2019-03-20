#include "include.h"
#include "common.h"

uint16 leftline_x[camera_height],rightline_x[camera_height],midline_x[camera_height];
uint8 shizi_flag;
float Piancha,cishu,piancha,zhong,before_zhong;
int zhongcha;
int i,j,k;//设i为行，j为列

#define FIND_LEFT		1
#define FIND_RIGHT		2
#define FIND_CENTER		0
#define POINT_COUNT		10
 
void Center_line_deal()       //中线处理
{   
    //int16 temp;
    i=0;j=0;k=0;              
    Piancha=0;cishu=0;piancha=0;before_zhong=zhong;zhong=0;zhongcha=0;
/////////////////////////////前20行/////////////////////////
    for(i = camera_height-1;i>camera_height-21;i--)           
    {
        for(j = camera_width/2;j <= camera_width/2&&j >= 0;j--)           //中间向左找跳变
        {
            if(img[camera_width*(i-1)+(j-1)] == 0xFF&&img[camera_width*(i-1)+(j-1)-1] == 0x00)  
            {
                leftline_x[i] = j;
                break;
            }
            else 
            {
                leftline_x[i] = 0;
            }
        }
        for(j = camera_width/2;j >= camera_width/2&&j < camera_width;j++)        //中间向右找跳变
        {
            if(img[camera_width*(i-1)+(j-1)] == 0xFF&&img[camera_width*(i-1)+(j-1)+1] == 0x00)
            {
                rightline_x[i] = j;
                break;
            }
            else 
            {
                rightline_x[i] = camera_width-1;
            }
        }
        if(i!=camera_height-1)
        {
            if(leftline_x[i] == 0&&rightline_x[i] == camera_width-1)      //双边丢线
            {
                leftline_x[i] = leftline_x[i+1];
                rightline_x[i] = rightline_x[i+1];
                midline_x[i] = (rightline_x[i]+leftline_x[i])/2;
            }  
            
            if(leftline_x[i] == 0&&rightline_x[i] != camera_width-1)        //左边丢线
            {   
                midline_x[i] = midline_x[i+1] - rightline_x[i+1] + rightline_x[i];
            }
          
            if(leftline_x[i] != 0&&rightline_x[i] == camera_width-1)        //右边丢线
            {
            midline_x[i] = midline_x[i+1] - leftline_x[i+1] + leftline_x[i];
            }
            
            if(leftline_x[i] != 0&&rightline_x[i] != camera_width-1)
            {
                midline_x[i] = (rightline_x[i]+leftline_x[i])/2;              
            } 
        }
        midline_x[camera_height-1]=(rightline_x[camera_height-1]+leftline_x[camera_height-1])/2;
        img[camera_width*(i-1)+(midline_x[i]-1)] = 0x00;
        
        Piancha = camera_width/2-midline_x[i];
    }
////////////////////////////20行之后////////////////////////////////      
    for(i = camera_height-21;i >= 0;i--)           
    {
        for(j = midline_x[i+1];j >= 0;j--)           //上一行中间向左找跳变
        {
            if(img[camera_width*(i-1)+(j-1)] == 0xFF&&img[camera_width*(i-1)+(j-1)-1] == 0x00)  
            {
                leftline_x[i] = j;
                break;
            }
            else 
            {
                leftline_x[i] = 0;
            }
        }
        for(j = midline_x[i+1];j < camera_width;j++)        //上一行中间向右找跳变
        {
            if(img[camera_width*(i-1)+(j-1)] == 0xFF&&img[camera_width*(i-1)+(j-1)+1] == 0x00)
            {
                rightline_x[i] = j;
                break;
            }
            else 
            {
                rightline_x[i] = camera_width-1;
            }
        }
        
        if(leftline_x[i] == 0&&rightline_x[i] == camera_width-1)      //双边丢线
        {
            //temp = createPoint(FIND_CENTER, i);
            //midline_x[i-1] = temp;
            leftline_x[i] = leftline_x[i+1];
            rightline_x[i] = rightline_x[i+1];
            midline_x[i] = (rightline_x[i]+leftline_x[i])/2;
            k++;
        }  
        
       if(leftline_x[i] == 0&&rightline_x[i] != camera_width-1)        //左边丢线
        {   
            midline_x[i] = midline_x[i+1] - rightline_x[i+1] + rightline_x[i];
        }
        
        if(leftline_x[i] != 0&&rightline_x[i] == camera_width-1)        //右边丢线
        {
            midline_x[i] = midline_x[i+1] - leftline_x[i+1] + leftline_x[i];
        }
        if(leftline_x[i] != 0&&rightline_x[i] != camera_width-1)
        {
            midline_x[i] = (rightline_x[i]+leftline_x[i])/2;              
        }
        
        Camera_Element_Decision();       //赛道元素判定        
        
        zhongcha= midline_x[i]-midline_x[i+1];
        if(abs(zhongcha)>5)  midline_x[i]=midline_x[i+1];   //限定条件（中点之差不超过5）
        
        img[camera_width*(i-1)+(midline_x[i]-1)] = 0x00;
        Piancha = camera_width/2-midline_x[i];     //计算偏差
        if(i>=30)
        {
             piancha+=Piancha; 
             cishu++;
        }
    }
    zhong=piancha/cishu;
}



void Camera_Element_Decision()         //赛道元素判定
{
//    shizi_flag=0;
//    if(k>5&&i<40)               //十字判定
//    {
//       shizi_flag=1;
//       shizi_deal();
//    }
}

void Duty_gain1()         //获取占空比
{ 
    float P=0.2,D;
//    if(zhong>0)P=0.3,D=0.0095;                   //0.1   0.0095
//    if(zhong<0)P=0.3,D=0.2;
//    Duty = SD5_CENTER-P*zhong+D*(zhong-before_zhong);
    Duty = SD5_CENTER-P*zhong;
}
//int a,b,c,d,e,f;
void shizi_deal()         //十字处理
{
    ;  
}

/* 利用最小二乘法生成需要补全的点 */
int16 createPoint(int type, int line)
{
	uint16 *linePointer;
	int8 tmp = 0;
	double sumX = 0;
	double sumY = 0;
	double averageX = 0;
	double averageY = 0;
	double sumUp = 0;
	double sumDown = 0;
	double parameterA;
	double parameterB;
	
	if(type == FIND_LEFT)
		linePointer = &leftline_x[line];
	else if(type == FIND_RIGHT)
		linePointer = &rightline_x[line];
	else
		linePointer = &midline_x[line];
	
	// 取邻近的 POINT_COUNT 个点进行拟合
	while(++tmp <= POINT_COUNT)
	{
		sumX += (line+tmp);
		sumY += linePointer[tmp];
	}
	--tmp;
	averageX = sumX/tmp;
	averageY = sumY/tmp;
	do
	{
		sumUp += (linePointer[tmp]-averageY) * (line+tmp-averageX);
		sumDown += (line+tmp-averageX) * (line+tmp-averageX);
	} while(--tmp > 0);
	
	if(sumDown == 0)
		parameterB = 0;
	else
		parameterB = sumUp/sumDown;
	parameterA = averageY-parameterB*averageX;
	return (int16)(parameterA+parameterB*line+0.5);
}



void huaxian(int x1,int y1,int x2,int y2)//将两个点之间连成一条线段
{
    int hy,i;
    for(i=x1;i<=x2;i++)
    {
    hy=(i-x1)*(y2-y1)/(x2-x1)+y1;
    img[camera_width*(i-1)+(hy-1)] = 0x00;
    }
}
