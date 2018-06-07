//---------------------------------------------------------
/**
 * @file   uwserver.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  웹소켓서버 관련 함수
 * @version 1.0
 */
//---------------------------------------------------------
#include "uwserver.h"


//---------------------------------------------------------
/**
 * @brief UWserver()
 * @return N/A
 
 */
//---------------------------------------------------------
UWserver::UWserver(QString servicename, int port, int max_count) {
    qDebug("UWserver::UWserver(%p)..\n", QThread::currentThreadId());    
		
		m_servicename = servicename;
		m_port = port;
		m_max_count = max_count;
}

//---------------------------------------------------------
/**
 * @brief ~UWserver()
 * @return N/A
 */
//---------------------------------------------------------
UWserver::~UWserver()
{
    qDebug("UWserver::~UWserver(%p)..\n", QThread::currentThreadId());
}

//---------------------------------------------------------
/**
 * @brief 서버 소켓을 구동한다.
 * @return N/A
 */
//---------------------------------------------------------
void UWserver::startServer()
{
		qDebug("UWserver::startServer()..\n");

    m_websocketServer = new QWebSocketServer("TestWebSocketServer",
                                      		   QWebSocketServer::NonSecureMode,
                                      			 NULL
                                      			);
    Q_CHECK_PTR(m_websocketServer);
    
    m_websocketServer->setMaxPendingConnections(m_max_count);

   if(m_websocketServer->listen(QHostAddress::Any, m_port)) {
        qDebug("UWserver: started(%s:%d)\n",
               m_websocketServer->serverAddress().toString().toUtf8().data(),
               m_websocketServer->serverPort());
   } else {
        qFatal("UWserver: not started! ==> exit(-1) now..\n");
        //g_Application->exit(-1);
   }
}


//---------------------------------------------------------
/**
 * @brief 서버 소켓을 정지한다.
 * @return N/A
 */
//---------------------------------------------------------
void UWserver::stopServer()
{
    qDebug("UWserver::stopServer()..\n");

    if(m_websocketServer) {
        m_websocketServer->close();

        delete m_websocketServer;
        m_websocketServer = NULL;
    }
}

//---------------------------------------------------------
/**
 * @brief 웹소켓서버를 실행한다.
 *
 * <pre>
 * </pre>
 *
 * @return N/A
 */
//---------------------------------------------------------
void UWserver::run()
{
    qDebug("UWserver::run(%p)\n", QThread::currentThreadId());
    startServer();
    
    qDebug("UWserver::Connect!\n");

    connect(this, SIGNAL(destroySignal()), this, SLOT(destroySlot()), Qt::DirectConnection);
    connect(m_websocketServer, SIGNAL(newConnection()), this, SLOT(newConnectionSlot()), Qt::DirectConnection);

		qDebug("UWserver::exec\n");
		
    this->exec();
    qDebug("UWserver::exec done\n");
}

//---------------------------------------------------------
/**
 * @brief 스레드 종료 이벤트 함수
 * @return N/A
 */
//---------------------------------------------------------
void UWserver::destroySlot() {
    qDebug("UWserver::destroySlot(%p)\n", QThread::currentThreadId());

    stopServer();
    this->quit();
    this->wait();
    delete this;
}


//---------------------------------------------------------
/**
 * @brief 클라이언트 콜백 이벤트
 * @return N/A
 */
//---------------------------------------------------------
void UWserver::newConnectionSlot() {
    QWebSocket* socket = m_websocketServer->nextPendingConnection();
     
    qDebug("UWserver::newConnectionSlot(%p)\n", QThread::currentThreadId());
    	
    if(socket) {
				connect(socket, 
				        SIGNAL(textMessageReceived(QString)), 
				        this, 
				        SLOT(readTextMsgSlot(QString))
				        );
				        
        connect(socket,
                SIGNAL(disconnected()),
                this,
                SLOT(disconnectedSlot()),
                Qt::DirectConnection
                );
    }
}


//---------------------------------------------------------
/**
 * @brief 클라이언트 텍스트 데이터 수신 콜백 이벤트
 * @return N/A
 */
//---------------------------------------------------------
void UWserver::readTextMsgSlot(QString msg   /**< JSon(텍스트)메시지 */
) {
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());

    qDebug("UWserver::readTextMsgSlot(%p)\n", QThread::currentThreadId());

    if(socket) {
    	  logging(SYSLOG,"[readTextMsg]:%s\n", msg.toUtf8().constData());
    		//qDebug("[readTextMsg]:%s\n", msg.toUtf8().constData());   
    		//socket->close();
    }
}

//---------------------------------------------------------
/**
 * @brief 클라이언트 접속해제 콜백함수
 * @return 0:성공, -1:실패
 */
//---------------------------------------------------------
void UWserver::disconnectedSlot() {
    qDebug("UWServerClient::disconnectedSlot()\n");	
}