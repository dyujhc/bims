//---------------------------------------------------------
/**
 * @file   uwserver.h
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  �����ϼ��� Ŭ����
 * @version 1.0
 */
//---------------------------------------------------------
#ifndef UWSERVER_H
#define UWSERVER_H

#include "common.h"

//---------------------------------------------------------
/**
 * @class UWserver
 *
 * <pre>
 * </pre>
 *
 * @brief �����ϼ��� Ŭ����
 */
//---------------------------------------------------------

class UWserver : public QThread
{
    Q_OBJECT
public:
    UWserver(QString servicename, int port, int max_count);
    ~UWserver();
    
    void startServer();
    void stopServer();
    void run();
    
protected:
		QWebSocketServer* m_websocketServer;   /**< ������ ���� */
		int m_port;                            /**< ��Ʈ��ȣ */
		QString m_servicename;		             /**< ������ �� */
		int m_max_count;                       /**< �ִ� ���� ���� ���Ǽ� */
		int m_connect_cnt;                     /**< ���� ���� �� */
		//QList<QWebSocket*> m_clientList;       /**< ���� client ����Ʈ */
		

signals :
    void destroySignal();
public slots :
    void destroySlot();	
		void newConnectionSlot();
		void readTextMsgSlot(QString msg);
		void disconnectedSlot();
};

#endif // UWSERVER_H