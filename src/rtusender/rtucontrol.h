#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H

#include <QtCore/QCoreApplication>
#include <QImage>
#include <QColor>
#include <QDebug>
#include <QSettings>
#include <QDir>

#include <unistd.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#define  RECV_BODY_SIZE  13
#define  SEND_BODY_SIZE  10

#define BIMS_HOME                       "BIMS_HOME"                     /**< 홈디렉토리                */

//---------------------------------------------------------
/** @brief RTU 상태정보 구조체    */
//---------------------------------------------------------
struct ustatus_t {
    int     mi_temp;         /**< 온도  */
    int     mi_humi;         /**< 습도  */
		int     mi_shock;        /**< 충격(1:충격, 0:정지) */
		int     mi_fan;          /**< 팬(1:동작, 0:정지) */
		int     mi_elect;        /**< 전류 */
};



class URtuControl
{
public:	
    int  init();    
    void start();
    void sendData();
private:
		int rd;
		QSettings* m_setting;    
    QString    m_homedir;
    QString    m_conffile;   	
    
    ustatus_t  m_stat;	
    
		void saveLEDVolt(QString fileName, float value);
		int  getMessage(char c);
		int  check_checksum(int* message, int value);
		int  calculaton_Checksum(char* message);
		void saveToFile(void);
		int  setMessage(char *message);
		QString uBaseHomeDir(void);	
		void clear(void);
};

#endif // GPIOCONTROL_H

