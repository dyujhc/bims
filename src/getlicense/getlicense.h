#ifndef GETLICENSE_H
#define GETLICENSE_H

#include <QtCore>
#include <QtNetwork>

#include <cstdio>

#define BIMS_HOME                       "BIMS_HOME"                     /**< 홈디렉토리                */

class QSslError;

using namespace std;

class DownloadManager: public QObject
{
    Q_OBJECT
    QNetworkAccessManager manager;
    QVector<QNetworkReply *> currentDownloads;

public:
    DownloadManager();
    ~DownloadManager();
    void doDownload(const QUrl &url);
    static QString saveFileName(const QUrl &url);
    bool saveToDisk(const QString &filename, QIODevice *data);
		bool getResult(QIODevice *data);
    static bool isHttpRedirect(QNetworkReply *reply);
    
    QSettings* m_setting;
    QString    m_homedir;
    QString    m_conffile;    
		QString    mUrl;   
    QString    mMacAddr;
    QString    mProject_id;
    QString    mBitID;
    
		
		QString uBaseHomeDir(void);
		QString extractNumberFromString(QString srcStr);
public slots:
    void execute();
    void downloadFinished(QNetworkReply *reply);
    void sslErrors(const QList<QSslError> &errors);
};


#endif // GETLICENSE_H
