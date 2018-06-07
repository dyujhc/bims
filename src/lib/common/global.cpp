//---------------------------------------------------------
/**
 * @file   global.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief  전역으로 사용되는 환경변수 관련 함수
 * @version 1.0
 */
//---------------------------------------------------------

#include "global.h"
#include "common.h"


//---------------------------------------------------------
/**
 * @brief 글로벌 환경변수 객체를 초기화 한다.
 * @return N/A
 */
//---------------------------------------------------------
UGlobal::UGlobal(int & argc, char ** argv) : QCoreApplication(argc, argv)
{
		m_setting = NULL;
    m_homedir.clear();
    m_confdir.clear();
    m_conffile.clear();
		
		//-------------------------------------------------
    /** 글로벌객체에 HOME 환경변수를 설정한다. */
    //-------------------------------------------------
    m_homedir = uBaseHomeDir();
    m_confdir = m_homedir + "/" + "conf";
    m_conffile = "";
    
    if(argc == 2) {
        if(uFileExists(QString(argv[1]))) {
            m_conffile = QString(argv[1]);
        }
    }  

    if(m_conffile.size() <= 0) {
        m_conffile = m_confdir + "/" + applicationName() + ".ini";        
    }
    
    if(!uFileExists(m_conffile)) {
    	qDebug("Configuration file not exist!!! '%s'\n", m_conffile.toUtf8().constData());    	
    } else {
    	qDebug("Configuration file is '%s'\n", m_conffile.toUtf8().constData());
    }
	
    //-------------------------------------------------
    /** 글로벌객체에 환경변수객체를 생성한다. */
    //-------------------------------------------------
    m_setting = new QSettings(m_conffile, QSettings::IniFormat);
    Q_ASSERT(m_setting);    
   
}

//------------------------------------------------------------
/**
 * @brief ~UGlobal()
 * @return N/A
 */
//------------------------------------------------------------
UGlobal::~UGlobal()
{
    if (m_setting){
    	delete m_setting;
    	m_setting = NULL;
    }
}

//------------------------------------------------------------
/**
 * @brief getSettingValueToInt()
 * @return N/A
 */
//------------------------------------------------------------
int UGlobal::getSettingValueToInt(QString keyname,
                                  int     def
) {
    int ret;
    
    ret = 0;
    
    if(m_setting) {
        ret =  m_setting->value(keyname, def).toInt();
    }
    
    return ret;    
}

//------------------------------------------------------------
/**
 * @brief getSettingValueToString()
 * @return N/A
 */
//------------------------------------------------------------
QString UGlobal::getSettingValueToString(QString keyname,
                                         QString def
) {
    QString ret;
    
    ret = "";
    
    if(m_setting) {
        ret =  m_setting->value(keyname, def).toString();
    }
    
    return ret;    
}