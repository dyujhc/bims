//---------------------------------------------------------
/**
 * @file   collector.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-27
 * @brief  수집 프로세서 
 * @version 1.0
 */
//---------------------------------------------------------

#include "collector.h"

//---------------------------------------------------------
/**
 * @brief UCollector()
 * @return N/A
 
 */
//---------------------------------------------------------
UCollector::UCollector() {
    qDebug("UCollector::UCollector(%p)..\n", QThread::currentThreadId());    	
}

//---------------------------------------------------------
/**
 * @brief ~UCollector()
 * @return N/A
 */
//---------------------------------------------------------
UCollector::~UCollector() {
	qDebug("UCollector::~UCollector(%p)..\n", QThread::currentThreadId());    
}


//---------------------------------------------------------
/**
 * @brief ~UCollector()
 * @return N/A
 */
//---------------------------------------------------------
void UCollector::init(int argc, char *argv[])	{

    //-----------------------------------------------------
    /** UGlobal 객체를 생성한다.  */
    //-----------------------------------------------------
		g_global = new UGlobal(argc, argv);		
		
		m_servicename = g_global->getSettingValueToString(KEY_WS_SERVICENAME, "default");
		m_port        = g_global->getSettingValueToInt(KEY_WSPORT, 1234);
		m_maxcount    = g_global->getSettingValueToInt(MAX_CONNECTION, 10000);
		m_interval    = 1000;
		
		mdb_id        = g_global->getSettingValueToString(KEY_DB_USERNAME, "default");
		mdb_pass      = g_global->getSettingValueToString(KEY_WS_PASSWORD, "default");
		mdb_dbname    = g_global->getSettingValueToString(KEY_WS_DBNAME  , "default");
		mdb_hostname  = g_global->getSettingValueToString(KEY_WS_HOSTNAME, "default");			
		
		qDebug("Server Setting is service_name '%s', port(%d), max_connection(%d)\n", m_servicename.toUtf8().constData(), m_port, m_maxcount);   
		
		
    //-----------------------------------------------------
    /** 타이머를 생성한다.  */
    //-----------------------------------------------------		
		g_timer = new UTimer(m_interval);		
		
		//-----------------------------------------------------
    /** 웹 소켓 서버를 생성한다.  */
    //-----------------------------------------------------				
		g_wserver = new UWserver(m_servicename, m_port, m_maxcount);		
		
		
    //-----------------------------------------------------
    /** Slot 지정한다.  */
    //-----------------------------------------------------		
		connect(g_timer, SIGNAL(min1()), this, SLOT(slot_min1()));

    		
		//-----------------------------------------------------
    /** 서버 실행  */
    //-----------------------------------------------------				
    g_timer->run();
		g_wserver->run();

    //-----------------------------------------------------
    /** Application 객체를 실행한다.  */
    //-----------------------------------------------------
    //rc = uExecApplication(); // 이벤트 루프 실행!!
    
    if (g_timer){
    	delete g_timer;
    	g_timer = NULL;
    }
      
    if (g_global) {
    	delete g_global;    	
    	g_global = NULL;    	
    }				
		
}


void UCollector::slot_min1(){
		qDebug("UCollector::slot_min1 1min check!!..\n" );
		
}