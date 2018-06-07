//---------------------------------------------------------
/**
 * @file   main.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-05-10
 * @brief  GPIO 컨트롤 프로그램
 * @version 1.0
 */
//---------------------------------------------------------

#include "gpiocontrol.h"

//---------------------------------------------------------
/**
 * @brief main()
 * @return N/A
 */
//---------------------------------------------------------
int main(int argc, char *argv[])
{
    int rc = 0;   
    //int metrix_clock = 0;
            
    QCoreApplication a(argc, argv);    
    
    QStringList args = QCoreApplication::instance()->arguments();
    
    UGpiocontrol gpio;
    
    int bright = -1;
    if (args.count() == 2) {
    	bright = args[1].toInt();
    	qDebug("Bright is (%d)", bright);
    	qDebug("[ %d | %d | %d ]\n", gpio.dec2binN(bright, 3), gpio.dec2binN(bright, 2), gpio.dec2binN(bright, 1));    
    }
    
    if (gpio.init() < 0) 
    	return -1;
    	
    gpio.clearMetrix();
    qDebug("process Start!!");
    
    int stat = 0;
    int X;
    gpio.getMetrix("metrix.bmp");
    //for (;;) {
        digitalWrite(GPIO_OE, HIGH);  // gpio data start
        digitalWrite(GPIO_LT, HIGH);  // gpio initial
        digitalWrite(GPIO_LT, LOW);
            for (stat=0;stat<16;stat++) {
                    for (X=0;X<SIZE_X;X++) {
                          
                            /* GPIO TEST */
                            /*
                            digitalWrite(GPIO_R1, LOW);
                            digitalWrite(GPIO_G1, LOW);
                            digitalWrite(GPIO_B1, HIGH);

                            digitalWrite(GPIO_R2, LOW);
                            digitalWrite(GPIO_G2, LOW);
                            digitalWrite(GPIO_B2, HIGH);

                            digitalWrite(GPIO_R3, LOW);
                            digitalWrite(GPIO_G3, LOW);
                            digitalWrite(GPIO_B3, HIGH);
                        		*/

                            digitalWrite(GPIO_R1, gpio.bmp_metrix[X][stat].R);
                            digitalWrite(GPIO_G1, gpio.bmp_metrix[X][stat].G);
                            digitalWrite(GPIO_B1, gpio.bmp_metrix[X][stat].B);
                            digitalWrite(GPIO_R2, gpio.bmp_metrix[X][stat+16].R);
                            digitalWrite(GPIO_G2, gpio.bmp_metrix[X][stat+16].G);
                            digitalWrite(GPIO_B2, gpio.bmp_metrix[X][stat+16].B);
                            digitalWrite(GPIO_R3, gpio.bmp_metrix[X][stat+32].R);
                            digitalWrite(GPIO_G3, gpio.bmp_metrix[X][stat+32].G);
                            digitalWrite(GPIO_B3, gpio.bmp_metrix[X][stat+32].B);


                            digitalWrite(GPIO_CK, HIGH);
                            digitalWrite(GPIO_CK, LOW);

                    }
            }
            digitalWrite(GPIO_A3, HIGH); // led data change
            digitalWrite(GPIO_A3, LOW);
            
            
            if(bright > 0){
		            digitalWrite(GPIO_R1, gpio.dec2binN(bright, 3));
		            digitalWrite(GPIO_G1, gpio.dec2binN(bright, 2));
		            digitalWrite(GPIO_B1, gpio.dec2binN(bright, 1));
		            digitalWrite(GPIO_R2, LOW);
		            digitalWrite(GPIO_G2, LOW);
		            digitalWrite(GPIO_B2, LOW);
		            digitalWrite(GPIO_R3, LOW);
		            digitalWrite(GPIO_G3, LOW);
		            digitalWrite(GPIO_B3, LOW);   
		              
                digitalWrite(GPIO_A2, HIGH);
                digitalWrite(GPIO_A2, LOW);		                   	
            }
            
    		  	
    //}
    
    return rc;
} 
