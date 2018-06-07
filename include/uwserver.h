//---------------------------------------------------------
/**
 * @file   uwserver.h
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  웹소켓서버 클래스
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
 * @brief 웹소켓서버 클래스
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
		QWebSocketServer* m_websocketServer;   /**< 웹소켓 서버 */
		int m_port;                            /**< 포트번호 */
		QString m_servicename;		             /**< 웹서비스 명 */
		int m_max_count;                       /**< 최대 접속 가능 세션수 */
		int m_connect_cnt;                     /**< 현재 접속 수 */
		//QList<QWebSocket*> m_clientList;       /**< 접속 client 리스트 */
		

signals :
    void destroySignal();
public slots :
    void destroySlot();	
		void newConnectionSlot();
		void readTextMsgSlot(QString msg);
		void disconnectedSlot();
};

#endif // UWSERVER_H