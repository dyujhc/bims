//---------------------------------------------------------
/**
 * @file   global.h
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  전역으로 사용되는 환경변수 사전정의
 * @version 1.0
 */
//---------------------------------------------------------
#ifndef UBS_GLOBAL_H
#define UBS_GLOBAL_H

#include <QSettings>
#include <QCoreApplication>

class UGlobal : public QCoreApplication 
{
protected :
		QSettings* m_setting;
    QString    m_homedir;
    QString    m_confdir;
    QString    m_conffile;

public:
    UGlobal(int & argc, char ** argv);
    ~UGlobal();
    
    int     getSettingValueToInt(QString keyname, int def);
    QString getSettingValueToString(QString keyname, QString def);
    
};

//Q_DECL_DEPRECATED 
#endif // UBS_GLOBAL_H

