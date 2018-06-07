//---------------------------------------------------------
/**
 * @file   rtucontrol.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-05-10
 * @brief  GPIO 컨트롤 프로그램
 * @version 1.0
 */
//---------------------------------------------------------


#include "rtucontrol.h"

//---------------------------------------------------------
/**
 * @brief 초기화
 * @return 0 : ture -1 : false
 */
//---------------------------------------------------------
int URtuControl::init() {
		int rc = -1;
		
		
		if (wiringPiSetup() == -1)
	  		return rc ;
	  	
	  rd=serialOpen("/dev/ttyAMA0", 9600);
	  if (rd < 0) {
	  	 qDebug("Unable to open serial port device!!");
	  	 return rc ;
	  }
	  
//		m_setting = NULL;
    m_homedir.clear();    
    m_conffile.clear();    
           
		//-------------------------------------------------
    /** 글로벌객체에 HOME 환경변수를 설정한다. */
    //-------------------------------------------------
    m_homedir = uBaseHomeDir();
    m_conffile = "";    
    m_conffile = m_homedir + "/" + "status.dat";   
    		  
   	rc = 1;
   	
   	return rc;
}

//---------------------------------------------------------
/**
 * @brief 시작
 * @return N/A
 */
//---------------------------------------------------------
void URtuControl::start() {
		
		qDebug("RTU Controler Start!!");
	  clear();
	  sendinit();
	  int data;
	  
    while(1) {
	    	data = serialGetchar(rd);
	    	if(getMessage((char)data)==0) {
	    			saveToFile();
	    			proc_shock();
	    			qDebug("receive Data!!");
	    			//sleep(4);
	    	}
    }
    	  
		close(rd);    	  
		
		return;
}


//---------------------------------------------------------
/**
 * @brief 충격시 음성출력
 * @return N/A
 */
//---------------------------------------------------------
void URtuControl::proc_shock(){
		if (m_stat.mi_shock == 1) {
				QProcess prc;
				
				prc.start("aplay ./voice/Warn.wav");
				prc.waitForFinished();		
		}
}


//---------------------------------------------------------
/**
 * @brief 시작
 * @return N/A
 */
//---------------------------------------------------------
int URtuControl::getMessage(char c) {
		int rc = -1;
		int data = 0;		
		int i;
		int elect;
		//int chksum = 0;
		int body[RECV_BODY_SIZE];
		
		if (c == 0x16) {	
				
				data = serialGetchar(rd);				
				if (data == 0x53) {
						for(i=0;i<RECV_BODY_SIZE;i++){
								body[i] = serialGetchar(rd);
						}
						
						int temp;
						if (body[1] == 0x10) {
								temp = body[2]*-1;						
						} else {
								temp = body[2];
						}
						m_stat.mi_temp = temp;
						m_stat.mi_humi = body[3];
						m_stat.mi_shock = body[4];
						m_stat.mi_fan = body[5];
						elect = body[6]*256 + body[7]; 
						qDebug("elect (%d:%d=%d)",  body[6], body[7], elect);
						m_stat.mi_elect = elect;	

						rc = 0;					
    		}					
		}
		
		return rc;
}

		
void URtuControl::saveToFile(void)
{
	  //-------------------------------------------------
    /** 글로벌객체에 환경변수객체를 생성한다. */
    //-------------------------------------------------
    m_setting = new QSettings(m_conffile, QSettings::IniFormat);
    	
    QDateTime dateTime = QDateTime::currentDateTime();
	
		m_setting->setValue("STATUS/TEMP", m_stat.mi_temp);		
		m_setting->setValue("STATUS/HUMI", m_stat.mi_humi);		
		m_setting->setValue("STATUS/SHOCK", m_stat.mi_shock);		
		m_setting->setValue("STATUS/FAN", m_stat.mi_fan);		
		m_setting->setValue("STATUS/ELECT", m_stat.mi_elect);	
		m_setting->setValue("STATUS/UPDT", dateTime.toString("yyyyMMddhhmmss"));	
	
		m_setting->sync();
		
		if (m_setting){
    	delete m_setting;
    	m_setting = NULL;
  	}
}

//---------------------------------------------------------
/**
 * @brief check sum을 확인한다.
 * @return 0 : ture -1 : false
 */
//---------------------------------------------------------
int URtuControl::check_checksum(int* message, int value)
{
    /* 임의의 길이를 갖는 메시지를 넘겨받아 Checksum을 계산하여 return한다.*/
    int Checksum;
    int sum = 0, pre_sum = 0;
 
    for (int n = 0; n < RECV_BODY_SIZE; n++)
    {
        sum += message[n];
        if (pre_sum > sum)
            sum++;
        pre_sum = sum;
    }
 
    Checksum = ~sum;
    
    if (Checksum == value) {
    		return 0;
    } else {
    		return -1;
    } 
}
//---------------------------------------------------------
/**
 * @brief check sum값을 생성한다.
 * @return N/A
 */
//---------------------------------------------------------
int URtuControl::calculaton_Checksum(char* message)
{
    /* 임의의 길이를 갖는 메시지를 넘겨받아 Checksum을 계산하여 return한다.*/
    int Checksum;
    int sum = 0, pre_sum = 0;
 
    for (int n = 0; n < SEND_BODY_SIZE; n++)
    {
        sum += message[n];
        if (pre_sum > sum)
            sum++;
        pre_sum = sum;
    }
 
    Checksum = ~sum;
 
    return Checksum;
}


//---------------------------------------------------------
/**
 * @brief 메세지 전송
 * @return N/A
 */
//---------------------------------------------------------
void URtuControl::sendData() {
	
		qDebug("RTU Control message Send!!\n");
		
		char* body;
		int i;		
		body = new char(SEND_BODY_SIZE);
		
		if (setMessage(body) < 0) {
				qDebug("There is no Send Data!!\n");
				if (body){
				  	delete body;
				   	body = NULL;
			  }				
				return;	
		}			
					
	 	serialPutchar(rd, 0x16);	 	
	 	for(i=0;i<SEND_BODY_SIZE;i++){
	 			serialPutchar(rd, body[i]);	
	 	}
	 	serialPutchar(rd, calculaton_Checksum(body));
	 	serialPutchar(rd, 0x03);
	
		qDebug("Message Sand!!\n");
		if (body){
		  	delete body;
		   	body = NULL;
	  }				
		
}

//---------------------------------------------------------
/**
 * @brief 메세지 전송
 * @return N/A
 */
//---------------------------------------------------------
void URtuControl::sendinit(void) {
	
		qDebug("RTU Control message Send!!\n");
			
	 	serialPutchar(rd, 0x16);	 	
	 	serialPutchar(rd, 0x57);
	 	serialPutchar(rd, 0x0C);
		serialPutchar(rd, 0x00);
	 	serialPutchar(rd, 0x00);
	 	serialPutchar(rd, 0x00);
	 	serialPutchar(rd, 0x00);
	 	serialPutchar(rd, 0x00);
	 	serialPutchar(rd, 0x00);
	 	serialPutchar(rd, 0x00);
	 	serialPutchar(rd, 0x00);
	 	serialPutchar(rd, 0x00);
	 	serialPutchar(rd, 0x03);
		
}

//---------------------------------------------------------
/**
 * @brief 전송 메세지 생성
 * @return 0: true, -1: false
 */
//---------------------------------------------------------
int URtuControl::setMessage(char *message) {
		int rc = -1;	
		int chk;
	
	  //-------------------------------------------------
    /** 글로벌객체에 환경변수객체를 생성한다. */
    //-------------------------------------------------
    m_setting = new QSettings(m_conffile, QSettings::IniFormat);
    		
		chk = m_setting->value("CONTROL/CHECK", 0).toInt();			
		if (chk == 0) {
			return rc;
		}	
		
		memset(message, 0x00, SEND_BODY_SIZE);
		
		message[0] = 0x57;
		message[1] = 0x0C;
		message[2] = (char)m_setting->value("CONTROL/FAN", 0).toInt();
		message[3] = (char)m_setting->value("CONTROL/MODULEPOWER", 0).toInt();
		message[4] = (char)m_setting->value("CONTROL/MAINPOWER", 0).toInt();
		
		
		m_setting->setValue("CONTROL/CHECK", 0);
		m_setting->setValue("CONTROL/FAN", 0);	
		m_setting->setValue("CONTROL/MODULEPOWER", 0);	
		m_setting->setValue("CONTROL/MAINPOWER", 0);		
		m_setting->sync();
		rc = 0;
		
		if (m_setting){
    	delete m_setting;
    	m_setting = NULL;
  	}
  			
		return rc;
}


QString URtuControl::uBaseHomeDir(void) {
    if(qgetenv(BIMS_HOME).isNull()) {
        QDir dir(QCoreApplication::applicationDirPath());
        qputenv(BIMS_HOME, dir.path().toUtf8());
    }
    return qgetenv(BIMS_HOME);
}

//---------------------------------------------------------
/**
 * @brief 전송 메세지 초기화
 * @return 0: true, -1: false
 */
//---------------------------------------------------------
void URtuControl::clear(void) {
		
	  //-------------------------------------------------
    /** 글로벌객체에 환경변수객체를 생성한다. */
    //-------------------------------------------------
    m_setting = new QSettings(m_conffile, QSettings::IniFormat);    		
		
		m_setting->setValue("CONTROL/CHECK", 0);	
		m_setting->setValue("CONTROL/FAN", 0);
		m_setting->setValue("CONTROL/MODULEPOWER", 0);
		m_setting->setValue("CONTROL/MAINPOWER", 0);
		m_setting->sync();
		
		if (m_setting){
    	delete m_setting;
    	m_setting = NULL;
  	}
  			
		return;
}
