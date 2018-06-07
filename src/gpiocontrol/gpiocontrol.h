#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H

#include <QtCore/QCoreApplication>
#include <QImage>
#include <QColor>
#include <QDebug>
#include <QSettings>

#include <unistd.h>
#include <wiringPi.h>

/* GPIO */

#define GPIO_R1                      7//8
#define GPIO_G1                      8//9
#define GPIO_B1                      9//7

#define GPIO_R2                      3//0
#define GPIO_G2                      0//2
#define GPIO_B2                      2//3

#define GPIO_R3                      14//12
#define GPIO_G3                      12//13
#define GPIO_B3                      13//14


#define GPIO_A0                      15
#define GPIO_A1                      16
#define GPIO_A2                      1
#define GPIO_A3                      4
#define GPIO_OE                      5
#define GPIO_LT                      6
#define GPIO_CK                      10

//#define GPIO_ADDR0                  10
#define GPIO_ADDR1                   11
#define GPIO_ADDR2                   21
#define GPIO_DATA0                   22
#define GPIO_DATA1                   26
#define GPIO_DATA2                   23
#define GPIO_DATA3                   24
#define GPIO_DATA4                   27
#define GPIO_DATA5                   25
#define GPIO_DATA6                   28
#define GPIO_DATA7                   29 

#define SIZE_X                       96								/**< 6열 열수*16*/
#define SIZE_Y                       48 							/**< 3행 단수*16*/

#define COLOR_R_TH                     128
#define COLOR_G_TH                     128
#define COLOR_B_TH                     128

struct mBMP_pix {
    bool R;
    bool G;
    bool B;    
};



class UGpiocontrol
{
public:	
		mBMP_pix bmp_metrix[SIZE_X][SIZE_Y];
   
    int  init();    
    void clearMetrix();
    int  getMetrix(QString fileName);
    bool dec2binN(int value, int loc);    
    void getColor(int R,int G,int B, int x, int y);    
private:
	QSettings* m_setting;
	void saveLEDVolt(QString fileName, float value);

};

#endif // GPIOCONTROL_H
