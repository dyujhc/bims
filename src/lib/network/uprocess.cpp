//---------------------------------------------------------
/**
 * @file   uprocess.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-28
 * @brief ���μ��� ���� �Լ�
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
 * @brief ���μ��� ���Ḧ �����Ѵ�.
 * @return N/A
 */
//---------------------------------------------------------
void UProcess::setDestroy(void)
{
    //mb_destroyed = true;
}
