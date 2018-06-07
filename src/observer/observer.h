//---------------------------------------------------------
/**
 * @file   observer.h
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-05-01
 * @brief  수집 프로세서 
 * @version 1.0
 */
//---------------------------------------------------------

#include "common.h"
#include "uwclient.h"


class UObserver : public QThread
{
	Q_OBJECT
public:
    UObserver();
    ~UObserver();
    
    void init(int argc, char *argv[]);  
    
    UWclient* g_wclient = NULL;
protected:
		int       m_port;
		QString   m_servicename;
		int       m_maxcount;   
		int       m_interval;
		QString   m_serverip;

		QString   mdb_id;
		QString   mdb_pass;
		QString   mdb_dbname;
		QString   mdb_hostname;		

signals :	  
    
public slots :	
		void slot_min1();
		
};

void cleanup_on_sig(int catched_signal);