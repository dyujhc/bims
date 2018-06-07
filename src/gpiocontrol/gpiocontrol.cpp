//---------------------------------------------------------
/**
 * @file   gpiocontrol.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-05-10
 * @brief  GPIO 컨트롤 프로그램
 * @version 1.0
 */
//---------------------------------------------------------


#include "gpiocontrol.h"

//---------------------------------------------------------
/**
 * @brief init()
 * @return 0 : ture -1 : false
 */
//---------------------------------------------------------
int UGpiocontrol::init() {
		int rc = -1;
	
		if (wiringPiSetup() == -1)
	  	return rc ;
		  
		pinMode(GPIO_R1, OUTPUT);   
		pinMode(GPIO_G1, OUTPUT);   
		pinMode(GPIO_B1, OUTPUT);   
		pinMode(GPIO_R2, OUTPUT);   
		pinMode(GPIO_G2, OUTPUT);   
		pinMode(GPIO_B2, OUTPUT);   
		pinMode(GPIO_R3, OUTPUT);   
		pinMode(GPIO_G3, OUTPUT);   
		pinMode(GPIO_B3, OUTPUT);   
		//pinMode(GPIO_A0, OUTPUT);   
		//pinMode(GPIO_A1, INPUT);   
		pinMode(GPIO_A2, OUTPUT);   
		pinMode(GPIO_A3, OUTPUT);   
		pinMode(GPIO_OE, OUTPUT);   
		pinMode(GPIO_LT, OUTPUT);   
		pinMode(GPIO_CK, OUTPUT);   
		        
		//pinMode(GPIO_ADDR0, INPUT);
		pinMode(GPIO_ADDR1, INPUT);
		pinMode(GPIO_ADDR2, INPUT);
		pinMode(GPIO_DATA0, INPUT);
		pinMode(GPIO_DATA1, INPUT);
		pinMode(GPIO_DATA2, INPUT);
		pinMode(GPIO_DATA3, INPUT);
		pinMode(GPIO_DATA4, INPUT);
		pinMode(GPIO_DATA5, INPUT);
		pinMode(GPIO_DATA6, INPUT);
		pinMode(GPIO_DATA7, INPUT);
		rc = 0;
		
		return rc;
}


//---------------------------------------------------------
/**
 * @brief init()
 * @return 0 : ture -1 : false
 */
//---------------------------------------------------------
void UGpiocontrol::clearMetrix() {
		int i, j;
		
		for(i=0;i<SIZE_X;i++){
				for(j=0;j<SIZE_Y;j++){
						bmp_metrix[i][j].R = false;
						bmp_metrix[i][j].G = false;
						bmp_metrix[i][j].B = false;
				}
		}
		
}

//---------------------------------------------------------
/**
 * @brief getMetrix() 
 * @return 0 : ture -1 : false
 */
//---------------------------------------------------------
int UGpiocontrol::getMetrix(
	QString fileName
) {
		int rc = -1;
		int i,j;
		int volt_cnt = 0;

		QImage image;
		if (!image.load(fileName))
			return rc;
			
		clearMetrix();
		for (i=0; i<image.width(); i++)
		{
				for (j=0; j<image.height(); j++) {
						QColor clrCurrent(image.pixel(i, j));
						
						
						if (clrCurrent.red() > COLOR_R_TH) {
								bmp_metrix[i][j].R = true;
								//bmp_metrix[i][j].G = true;
								//bmp_metrix[i][j].B = true;
								volt_cnt++;
						}							
						if (clrCurrent.green() > COLOR_G_TH) {
								//bmp_metrix[i][j].R = true;
								bmp_metrix[i][j].G = true;
								//bmp_metrix[i][j].B = true;
								volt_cnt++;
						}
						if (clrCurrent.blue() > COLOR_B_TH) {
								//bmp_metrix[i][j].R = true;
								//bmp_metrix[i][j].G = true;	
								bmp_metrix[i][j].B = true;
								volt_cnt++;
						}						
				}
		}	
		//saveLEDVolt("status.dat", volt_cnt*0.005);
		rc = 0;
		return rc;
}

//---------------------------------------------------------
/**
 * @brief dec2binN() 
 * @return 0 : ture -1 : false
 */
//---------------------------------------------------------
bool UGpiocontrol::dec2binN(int value, int loc
) {
		int result[loc];			
		int i;		
		for (i=0;i<loc;i++){
				result[i] = value % 2;	
				value = value/2;
		}		
		return result[loc-1];	
}
	

void UGpiocontrol::getColor(int R,int G,int B, int x, int y
){

		int tot;
		double avg;
	
		tot = R + G + B;
		
		avg = double(tot) / 768.0;
		//printf("%d, %d, %d, %d %f\n", R,G,B, tot, avg);
		if (avg > 0.6) {
			
			bmp_metrix[x][y].R = true;
			bmp_metrix[x][y].G = true;
			bmp_metrix[x][y].B = true;
		} else if (avg > 0.4) {
				if(R>G){
						bmp_metrix[x][y].R = true;
						if(G>B) {
								bmp_metrix[x][y].G = true;
						} else {
								bmp_metrix[x][y].B = true;
						}
				} else {
						bmp_metrix[x][y].G = true;
						if(R>B) {
								bmp_metrix[x][y].R = true;
						} else {
								bmp_metrix[x][y].B = true;
						}
				}
		} else if (avg > 0.3) {
				if(R>G){
						if(R>B) {
								bmp_metrix[x][y].R = true;
						} else {
							if(G>B){
									bmp_metrix[x][y].G = true;
							} else {
									bmp_metrix[x][y].B = true;
							}								
						}
				} else {
						if(G>B) {
								bmp_metrix[x][y].G = true;
						} else {
								bmp_metrix[x][y].B = true;
						}
				}	
		} else {
				bmp_metrix[x][y].R = false;
				bmp_metrix[x][y].G = false;
				bmp_metrix[x][y].B = false;		
				}

}		

void UGpiocontrol::saveLEDVolt(QString fileName, float value
) {
	m_setting = new QSettings(fileName, QSettings::IniFormat);
  Q_ASSERT(m_setting);
  
  m_setting->setValue("STATUS/LED_VOLTE", QString::number(value));
  
  if (m_setting) {
  	delete m_setting;    	
  	m_setting = NULL;    	
  }		  
}
