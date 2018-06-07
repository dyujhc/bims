//---------------------------------------------------------
/**
 * @file   dbms.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  �����ͺ��̽� ���� �Լ�
 * @version 1.0
 */
//---------------------------------------------------------

#include "dbms.h"
//---------------------------------------------------------
/**
 * @brief UWserver()
 * @return N/A
 
 */
//---------------------------------------------------------
UDbms::UDbms(QString id, 
	           QString pass, 
	           QString dbname, 
	           QString hostname
) {
    qDebug("UDbms::UDbms(%p)..\n", QThread::currentThreadId());    
		
		m_id       = id;		
		m_pass     = pass;
		m_dbname   = dbname;
		m_hostname = hostname;
}

//---------------------------------------------------------
/**
 * @brief ~UWserver()
 * @return N/A
 */
//---------------------------------------------------------
UDbms::~UDbms()
{
    qDebug("UWserver::~UWserver(%p)..\n", QThread::currentThreadId());
}



//---------------------------------------------------------
/**
 * @brief ���� ������ �����Ѵ�.
 * @return N/A
 */
//---------------------------------------------------------
bool UDbms::connect()
{
		bool rc;
		qDebug("UDbms::connect()..\n");
		
		m_db = QSqlDatabase::addDatabase("QMYSQL");
		m_db.setUserName(m_id);
		m_db.setPassword(m_pass);
		m_db.setDatabaseName(m_dbname);
		m_db.setHostName(m_hostname);
		
		rc = m_db.open();
		
		if(rc){
				qDebug("UDbms::Database Open Sucessful! \n");
		} else {
				qDebug("UDbms::Database Open Failed! \n");
		}
		
		return rc;
}