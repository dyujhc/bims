//---------------------------------------------------------
/**
 * @file   ubs_uprocess.h
 * @Author yko (yko@ubns.kr)
 * @date   2015-03-29
 * @brief 프로세스 관리 클래스
 * @version 1.0
 */
//---------------------------------------------------------
#ifndef UPROCESS_H
#define UPROCESS_H

#include <QCoreApplication>
#include <QThread>
#include <QDebug>

#include "common.h"

//---------------------------------------------------------
/**
 * @class UProcess
 * @brief 프로세스 관리 클래스
 *
 * <pre>
 * UProcess 클래스는 채널관리, 데이터 변환/전달등을 관리하는 클래스이다.
 *  1)
 * </pre>
 */
//---------------------------------------------------------
class UProcess : public QObject
{
    Q_OBJECT
public:
    explicit UProcess(QObject *parent);
    ~UProcess();
    void setDestroy(void);

protected :

signals:

public slots:

};

#endif // UPROCESS_H

