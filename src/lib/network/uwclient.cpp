//---------------------------------------------------------
/**
 * @file   uwclient.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  웹소켓서버 관련 함수
 * @version 1.0
 */
//---------------------------------------------------------
#include "uwclient.h"

QT_USE_NAMESPACE

#include <QtCore/QDebug>

QT_USE_NAMESPACE

UWclient::UWclient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &UWclient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &UWclient::closed);
    m_webSocket.open(QUrl(url));
}

void UWclient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &UWclient::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void UWclient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    m_webSocket.close();
}

#if 0
//---------------------------------------------------------
/**
 * @brief UWclient()
 * @return N/A
 */
//---------------------------------------------------------
#if 0
UWclient::UWclient() {
    qDebug("UWclient::UWclient(%p)..\n", QThread::currentThreadId());    
		
		m_connectTM = QDateTime::currentDateTime();
		m_clientID  = "";		
}

//---------------------------------------------------------
/**
 * @brief ~UWserver()
 * @return N/A
 */
//---------------------------------------------------------
UWclient::~UWclient()
{
    qDebug("UWclient::~UWclient(%p)..\n", QThread::currentThreadId());
}
#endif


#if 0
//---------------------------------------------------------
/**
 * @brief setConnectTime()
 * @return N/A
 */
//---------------------------------------------------------
QDateTime UWclient::getConnectTime(void)
{
		return m_connectTM; 
}
#endif

UWclient::UWclient(const QUrl &url, bool debug, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &UWclient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &UWclient::closed);
    m_webSocket.open(QUrl(url));
}

void UWclient::onConnected()
{
    if (m_debug)
        qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &UWclient::onTextMessageReceived);
    m_webSocket.sendTextMessage(QStringLiteral("Hello, world!"));
}

void UWclient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    m_webSocket.close();
}
#endif