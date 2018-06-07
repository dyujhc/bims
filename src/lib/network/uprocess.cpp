//---------------------------------------------------------
/**
 * @file   uprocess.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief 프로세스 관리 함수
 * @version 1.0
 */
//---------------------------------------------------------

#include "uprocess.h"
//---------------------------------------------------------
/**
 * @brief UProcess()
 * @return N/A
 */
//---------------------------------------------------------
UProcess::UProcess(QObject *parent       /**< Parent */                   
) : QObject(parent)
{
    qDebug("UProcess::UProcess(%p)..\n", QThread::currentThreadId()); 
}


//---------------------------------------------------------
/**
 * @brief ~UProcess()
 * @return N/A
 */
//---------------------------------------------------------
UProcess::~UProcess()
{
    setDestroy();
    qDebug("UProcess::~UProcess(%p)..\n", QThread::currentThreadId());
}

//---------------------------------------------------------
/**
 * @brief 프로세스 종료를 설정한다.
 * @return N/A
 */
//---------------------------------------------------------
void UProcess::setDestroy(void)
{
    //mb_destroyed = true;
}
