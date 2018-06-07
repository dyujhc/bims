//---------------------------------------------------------
/**
 * @file   utimer.h
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  �����ϼ��� Ŭ����
 * @version 1.0
 */
//---------------------------------------------------------
#ifndef UTIMER_H
#define UTIMER_H

#include <QDateTime>
#include <QThread>
#include <QTimer>

//---------------------------------------------------------
/**
 * @class UTimer
 *
 * <pre>
 * </pre>
 *
 * @brief Ÿ�̸� Ŭ����
 */
//---------------------------------------------------------

//---------------------------------------------------------
/** @brief Ÿ�̸Ӱ��� ����ü    */
//---------------------------------------------------------
struct utimer_t {
    time_t  mi_NowUtcYms;    /**< unix �ð�  */
    time_t  mi_NowUtcYmsf;   /**< (yyyymmddhhmmss)  */
		int     m_hh;            /**< �ð� 24 */
		int     m_mi;            /**< �� */
		int     m_se;            /**< �� */
		QString ms_NowUtcYms;    /**< (yyyymmddhhmmss)  */
		QString ms_NowUtcYmsf;   /**< (yyyy/mm/dd hh:mm:ss) */
		
};

class UTimer : public QThread
{
	Q_OBJECT
public:
    UTimer(int interval);
    ~UTimer();
    
    //void init(int interval);  
    void run();
    
    QString  getStrNowUtcYmsf();
protected:
		QTimer*  utimer;		
		utimer_t m_timer;
		int      m_interver;

		void uUpdateTimer(void);

signals :
	  void sec1();
    void min1();
    void min5();
    void min10();
    
public slots :		
		void timesUP();
		
};


#endif // UTIMER_H