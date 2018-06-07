//---------------------------------------------------------
/**
 * @file   gpiocontrol.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-05-17
 * @brief  license 수집 프로그램
 * @version 1.0
 */
//---------------------------------------------------------
#include "getlicense.h"

DownloadManager::DownloadManager()
{		
		connect(&manager, SIGNAL(finished(QNetworkReply*)),
            SLOT(downloadFinished(QNetworkReply*)));
    
		m_setting = NULL;
    m_homedir.clear();    
    m_conffile.clear();    
           
		//-------------------------------------------------
    /** 글로벌객체에 HOME 환경변수를 설정한다. */
    //-------------------------------------------------
    m_homedir = uBaseHomeDir();
    m_conffile = "";    
    m_conffile = m_homedir + "/" + "BIT_SETUP.INI";   
    
    //-------------------------------------------------
    /** 글로벌객체에 환경변수객체를 생성한다. */
    //-------------------------------------------------
    m_setting = new QSettings(m_conffile, QSettings::IniFormat);
}

DownloadManager::~DownloadManager()
{	
    if (m_setting){
    	delete m_setting;
    	m_setting = NULL;
    }	
}

void DownloadManager::doDownload(const QUrl &url)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);

#if 0// QT_CONFIG(ssl)
    connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
            SLOT(sslErrors(QList<QSslError>)));
#endif

    currentDownloads.append(reply);
}

QString DownloadManager::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if (basename.isEmpty())
        basename = "download";

    if (QFile::exists(basename)) {
        // already exists, don't overwrite
        int i = 0;
        basename += '.';
        while (QFile::exists(basename + QString::number(i)))
            ++i;

        basename += QString::number(i);
    }

    return basename;
}

bool DownloadManager::getResult(QIODevice *data)
{
		QString str;
		str = data->readAll();
		//qDebug(str.toUtf8().constData());	
		
		int headerCd;
		QString headerMsg;
		int leftCnt;		
		 
		QXmlStreamReader xml(str);
		while(!xml.atEnd() &&  !xml.hasError()) {
		    /* Read next element.*/
		    QXmlStreamReader::TokenType token = xml.readNext();
		    /* If token is just StartDocument, we'll go to next.*/
		    if(token == QXmlStreamReader::StartDocument) {
		        continue;
		    }
		    /* If token is StartElement, we'll see if we can read it.*/
		    if(token == QXmlStreamReader::StartElement) {		    	
		    		//qDebug("xml.name = %s\n", xml.name().toUtf8().constData());		    		
		        if(xml.name() == "headerCd") {
		        	xml.readNext();
		        	headerCd = xml.text().toInt();
		        } else if (xml.name() == "headerMsg") {
		        	xml.readNext();	
		        	headerMsg = xml.text().toString();		        	
		        } else if (xml.name() == "itemCount") {
		        	xml.readNext();
		        	leftCnt = xml.text().toInt();		        	
		        }		        
		    }		    
		}
		
		if (headerCd < 0) {
				qDebug("\n***************************************\n");
				qDebug("license load error :%s\n", headerMsg.toUtf8().constData());
				qDebug("please cheack the Network or license \n");
				qDebug("***************************************\n");
				
				m_setting->setValue("License/code", "0");
		} else {
			  qDebug("\n***************************************\n");
			  qDebug("YOUR LICENSE IS SUCCESSFULLY DOWNLOADED!! THANK YOU!!\n");
			  qDebug("PROJECT ID = %s\n", mProject_id.toUtf8().constData());
			  qDebug("BIT ID     = %s\n", mBitID.toUtf8().constData());			  
//				qDebug("result is %s\n", headerMsg.toUtf8().constData());				
			  qDebug("the Project license left = %d\n", leftCnt);			  
			  qDebug("***************************************\n");
				
				m_setting->setIniCodec("UTF-8");
			  m_setting->setValue("License/code", mMacAddr.right(2));
			  m_setting->setValue("BIT/BIS_ID", mBitID);
			  
		} 
		
		m_setting->sync();	  
		
    return true;		
}

bool DownloadManager::saveToDisk(const QString &filename, QIODevice *data)
{    
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(filename),
                qPrintable(file.errorString()));
        return false;
    }
		
    file.write(data->readAll());
    file.close();
    		
    return true;
}

bool DownloadManager::isHttpRedirect(QNetworkReply *reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return statusCode == 301 || statusCode == 302 || statusCode == 303
           || statusCode == 305 || statusCode == 307 || statusCode == 308;
}

void DownloadManager::execute()
{
    QStringList args = QCoreApplication::instance()->arguments();
    args.takeFirst();           // skip the first argument, which is the program's name
    if (args.count() < 2) {
				qDebug("\n***************************************\n");
        printf("getlicense example \n\n"
               "Usage: getlicense [project_id] [bit_id]\n"
               "\n");
        qDebug("***************************************\n");
        QCoreApplication::instance()->quit();
        return;
    }    
    mProject_id = args[0];
    mBitID = args[1];  //BIT0000140 
    mUrl.sprintf("http://frogmon.synology.me/bit_license/getlicense.php?project_id=%s&mac_addr=%s&bit_id=%s",
                  args[0].toUtf8().constData(), 
                  mMacAddr.toUtf8().constData(), 
                  mBitID.toUtf8().constData());
    
    QUrl url = QUrl::fromEncoded(mUrl.toLocal8Bit());        
    //qDebug(mUrl.toUtf8().constData());
    doDownload(url);
}

void DownloadManager::sslErrors(const QList<QSslError> &sslErrors)
{
#if 0 //QT_CONFIG(ssl)
    for (const QSslError &error : sslErrors)
        fprintf(stderr, "SSL error: %s\n", qPrintable(error.errorString()));
#else
    Q_UNUSED(sslErrors);
#endif
}

void DownloadManager::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        fprintf(stderr, "Download of %s failed: %s\n",
                url.toEncoded().constData(),
                qPrintable(reply->errorString()));
    } else {
        if (isHttpRedirect(reply)) {
            fputs("Request was redirected.\n", stderr);
        } else {        		
            QString filename = saveFileName(url);
            //if (saveToDisk(filename, reply)) {
            if (getResult(reply)) {
                //printf("Download of %s succeeded (saved to %s)\n",
                //       url.toEncoded().constData(), qPrintable(filename));
            }            
        }
    }

    currentDownloads.removeAll(reply);
    reply->deleteLater();

    if (currentDownloads.isEmpty()) {
        // all downloads finished
        QCoreApplication::instance()->quit();
    }
}

QString DownloadManager::uBaseHomeDir(void) {
    if(qgetenv(BIMS_HOME).isNull()) {
        QDir dir(QCoreApplication::applicationDirPath());
        qputenv(BIMS_HOME, dir.path().toUtf8());
    }
    return qgetenv(BIMS_HOME);
}

QString DownloadManager::extractNumberFromString(QString srcStr)   
{                                                        
    QString finalString;
                                                          
    QRegExp xRegExp("(-?\\d+(?:[\\.,]\\d+(?:e\\d+)?)?)");
    xRegExp.indexIn(srcStr);
    QStringList xList = xRegExp.capturedTexts();
          
    foreach(finalString, xList);

    return finalString;
}
