//---------------------------------------------------------
/**
 * @file   dbms.h
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-04-06
 * @brief  데이터베이스 관련 클래스
 * @version 1.0
 */
//---------------------------------------------------------
#ifndef UBS_DATABASE_H
#define UBS_DATABASE_H

#include "common.h"

#include <QSqlDatabase>

class UDbms: public QThread
{
    Q_OBJECT
protected :
		QSqlDatabase m_db;		
		QString      m_id;
		QString      m_pass;
		QString      m_dbname;
		QString      m_hostname;		

public:
    UDbms(QString id, QString pass, QString dbname, QString hostname);
    ~UDbms();    
    
    bool connect();
signals :
    
public slots :
    
};


#endif // UBS_DATABASE_H

