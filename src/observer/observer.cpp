//---------------------------------------------------------
/**
 * @file   observer.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-05-01
 * @brief  ���� ���μ��� 
 * @version 1.0
 */
//---------------------------------------------------------

#include "observer.h"

//---------------------------------------------------------
/**
 * @brief UCollector()
 * @return N/A
 
 */
//---------------------------------------------------------
UObserver::UObserver() {
    qDebug("UObserver::UObserver(%p)..\n", QThread::currentThreadId());    	
}

//---------------------------------------------------------
/**
 * @brief ~UCollector()
 * @return N/A
 */
//---------------------------------------------------------
UObserver::~UObserver() {
	qDebug("UObserver::~UObserver(%p)..\n", QThread::currentThreadId());    
}


//---------------------------------------------------------
/**
 * @brief ~UCollector()
 * @return N/A
 */
//---------------------------------------------------------
void UObserver::init(int argc, char *argv[])	{

		QCoreApplication a(argc, argv);
		
    //-----------------------------------------------------
    /** UGlobal ��ü�� �����Ѵ�.  */
    //-----------------------------------------------------
		g_global = new UGlobal(argc, argv);		
		
		m_servicename = g_global->getSettingValueToString(KEY_WS_SERVICENAME, "default");
		m_port        = g_global->getSettingValueToInt(KEY_WSPORT, 1234);
		m_maxcount    = g_global->getSettingValueToInt(MAX_CONNECTION, 10000);
		m_interval    = g_global->getSettingValueToInt(KEY_TIMER, 10000);
		m_serverip    = g_global->getSettingValueToString(KEY_WS_SERVICENAME, "default");
		
		mdb_id        = g_global->getSettingValueToString(KEY_DB_USERNAME, "default");
		mdb_pass      = g_global->getSettingValueToString(KEY_WS_PASSWORD, "default");
		mdb_dbname    = g_global->getSettingValueToString(KEY_WS_DBNAME  , "default");
		mdb_hostname  = g_global->getSettingValueToString(KEY_WS_HOSTNAME, "default");			
		
		qDebug("Server Setting is service_name '%s', port(%d), max_connection(%d)\n", m_servicename.toUtf8().constData(), m_port, m_maxcount);
		
    //-----------------------------------------------------
    /** Ÿ�̸Ӹ� �����Ѵ�.  */
    //-----------------------------------------------------		
		g_timer = new UTimer(m_interval);		
		
		//-----------------------------------------------------
    /** �� ���� ������ �����Ѵ�.  */
    //-----------------------------------------------------				
		//g_wserver = new UWserver(m_servicename, m_port, m_maxcount);		
		//g_wclient = new UWclient(QUrl(QStringLiteral("ws://127.0.0.1:7788")), false);
		
		//QObject::connect(&g_wclient, &UWclient::closed, &a, &QCoreApplication::quit);
		
		
    //-----------------------------------------------------
    /** Slot �����Ѵ�.  */
    //-----------------------------------------------------		
		connect(g_timer, SIGNAL(min1()), this, SLOT(slot_min1()));

    		
		//-----------------------------------------------------
    /** ���� ����  */
    //-----------------------------------------------------				
    g_timer->run();
		//g_wserver->run();

    //-----------------------------------------------------
    /** Application ��ü�� �����Ѵ�.  */
    //-----------------------------------------------------
    //rc = uExecApplication(); // �̺�Ʈ ���� ����!!
    
    if (g_timer){
    	delete g_timer;
    	g_timer = NULL;
    }
      
    if (g_global) {
    	delete g_global;    	
    	g_global = NULL;    	
    }				
		
}


void UObserver::slot_min1(){
		qDebug("UObserver::slot_min1 1min check!!..\n" );
		
}