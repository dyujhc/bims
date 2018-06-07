//---------------------------------------------------------
/**
 * @file   main.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-05-17
 * @brief  License 수집 프로그램
 * @version 1.0
 */
//---------------------------------------------------------

#include "getlicense.h"
#include <QNetworkInterface>

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

		QString macAddress;
		QString Adddress;		
		QNetworkInterface interface; 
		
		QString hdaddr;
		QString hdname;
		
		QList<QNetworkInterface> macList = interface.allInterfaces();
		for (int i = 0; i < macList.size(); i++)
    {
        hdaddr = macList.at(i).hardwareAddress();       // MAC                
        if(hdaddr != "00:00:00:00:00:00")
        {
        		macAddress = hdaddr;
        		hdname = macList.at(i).name();
        		if (qstrcmp(hdname.toUtf8().constData(), "eth0") == 0) {
		            //qDebug("name(%s) MAC(%s) \n", hdname.toUtf8().constData(), macAddress.toUtf8().constData());        			
		            break;
        		}
        }
    }
        
    DownloadManager manager; 
    manager.mMacAddr = macAddress;   
    QTimer::singleShot(0, &manager, SLOT(execute()));
		
    app.exec();
}

#include "main.moc"