//---------------------------------------------------------
/**
 * @file   collector.h
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-27
 * @brief  수집 프로세서 
 * @version 1.0
 */
//---------------------------------------------------------

#include "common.h"
#include "uwserver.h"


class UCollector : public QThread
{
	Q_OBJECT
public:
    UCollector();
    ~UCollector();
    
    void init(int argc, char *argv[]);  
    
    UWserver* g_wserver = NULL;
protected:
		int       m_port;
		QString   m_servicename;
		int       m_maxcount;   
		int       m_interval;

		QString   mdb_id;
		QString   mdb_pass;
		QString   mdb_dbname;
		QString   mdb_hostname;		

signals :	  
    
public slots :	
		void slot_min1();
		
};

void cleanup_on_sig(int catched_signal);