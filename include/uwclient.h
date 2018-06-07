//---------------------------------------------------------
/**
 * @file   uwclient.h
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  웹소켓서버 클래스
 * @version 1.0
 */
//---------------------------------------------------------
#ifndef UWCLIENT_H
#define UWCLIENT_H

#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>

#include "common.h"

//---------------------------------------------------------
/**
 * @class UWclient
 *
 * <pre>
 * </pre>
 *
 * @brief 웹소켓 클래스
 */
//---------------------------------------------------------
#if 0
class UWclient : public QObject
{
	Q_OBJECT
public:
		explicit UWclient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);
    
    //UWclient();
    //~UWclient();
    
    //QWebSocket* socketClient;
    //QDateTime getConnectTime(void);
    
protected:    
    QDateTime  m_connectTM;
    QString    m_clientID;
    
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);  
};
#endif

class UWclient : public QObject
{
    Q_OBJECT
public:
    explicit UWclient(const QUrl &url, bool debug = false, QObject *parent = Q_NULLPTR);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};



#endif // UWCLIENT_H