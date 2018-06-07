//---------------------------------------------------------
/**
 * @file   utimer.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  타이머 관련 함수
 * @version 1.0
 */
//---------------------------------------------------------
#include "utimer.h"

//utimer_t gTimer;
//---------------------------------------------------------
/**
 * @brief UWserver()
 * @return N/A
 
 */
//---------------------------------------------------------
UTimer::UTimer(int interval) {
    qDebug("UTimer::UTimer(%p)..\n", QThread::currentThreadId());        	    
		utimer = new QTimer(this);
		if (interval <= 0 || interval > 10000){
			m_interver = 1000;
		} else {
			m_interver = interval; 	
		}		
		connect(utimer, SIGNAL(timeout()), this, SLOT(timesUP()));    
}

//---------------------------------------------------------
/**
 * @brief ~UTimer()
 * @return N/A
 */
//---------------------------------------------------------
UTimer::~UTimer() {
	qDebug("UTimer::~UTimer(%p)..\n", QThread::currentThreadId());    
		if (utimer) {
			delete utimer;
			utimer = NULL;
		}
}

#if 0
void UTimer::init(int interval
)	{
		utimer = new QTimer(this);   
		m_interver = interval; 
		connect(utimer, SIGNAL(timeout()), this, SLOT(timesUP()));
}
#endif

void UTimer::run()	{		
		utimer->start(m_interver);
}


void UTimer::timesUP(){
		uUpdateTimer();		
		
		emit sec1();
		if (m_timer.m_se == 0) {
			emit min1();
			qDebug("UTimer::timesUP 1min(%s)..\n", m_timer.ms_NowUtcYmsf.toUtf8().constData());
			if (m_timer.m_mi % 5 == 0) {
				emit min5();	
				qDebug("UTimer::timesUP 5min(%s)..\n", m_timer.ms_NowUtcYmsf.toUtf8().constData());
			} 
			if (m_timer.m_mi % 10 == 0) {
				emit min10();	
				qDebug("UTimer::timesUP 10min(%s)..\n", m_timer.ms_NowUtcYmsf.toUtf8().constData());
			}			
		}
		
}

//---------------------------------------------------------
/**
 * @brief Path와 확장자가 제거된 파일명을 반환한다.
 * @return 파일명
 */
//---------------------------------------------------------
void UTimer::uUpdateTimer(void
) {
		QDateTime dtm;        
		dtm = QDateTime::currentDateTime();    
		m_timer.mi_NowUtcYms  = dtm.toTime_t();
		m_timer.mi_NowUtcYmsf = dtm.toString("yyyyMMddHHmmss").toInt();		
    m_timer.ms_NowUtcYms  = dtm.toString("yyyyMMddHHmmss");
    m_timer.ms_NowUtcYmsf = dtm.toString("yyyy/MM/dd HH:mm:ss");		
    m_timer.m_hh          = dtm.toString("HH").toInt();
    m_timer.m_mi          = dtm.toString("mm").toInt();
    m_timer.m_se          = dtm.toString("ss").toInt();
}

QString UTimer::getStrNowUtcYmsf(){
	return m_timer.ms_NowUtcYmsf;
}