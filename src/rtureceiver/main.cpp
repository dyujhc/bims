//---------------------------------------------------------
/**
 * @file   main.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-05-10
 * @brief  GPIO 컨트롤 프로그램
 * @version 1.0
 */
//---------------------------------------------------------

#include "rtucontrol.h"

//---------------------------------------------------------
/**
 * @brief main()
 * @return N/A
 */
//---------------------------------------------------------
#if 1
int main(int argc, char *argv[])
{
    int rc = 0;   
            
    QCoreApplication a(argc, argv);    
    
    URtuControl gRtu;
    
    if (gRtu.init() < 0) 
    	return -1;
    	
    gRtu.start();
   
    //gRtu.sendData();
    
    return rc;
} 
#else

int main(int argc, char *argv[])
{
		int rc = 0; 
		
		QCoreApplication a(argc, argv);
		
		if (wiringPiSetup() == -1)
	  	return rc ;
   
	  int data;
	  
    while(1) {
				rc=serialOpen("/dev/ttyAMA0", 9600);
				if(rc < 0) {
			  		qDebug("Unable to open serial port device!!");
			  		return -1;
			  }
	    	data = 0x45; //serialGetchar(rc);
	    	qDebug("RPi = %c", (char)data);
	    	serialPutchar(rc, data);
	    	//serialPuts(rc, "W");
	    	delay(200);
	    	fflush(stdout);
	    	close(rc);
    }
    
    return rc;
}
#endif