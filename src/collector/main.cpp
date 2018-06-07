//---------------------------------------------------------
/**
 * @file   main.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-27
 * @brief  수집 프로세서 
 * @version 1.0
 */
//---------------------------------------------------------

#include "collector.h"

UCollector* g_collector = NULL;

int chkTm() {
	//printf(%s, ymsf.toUtf8().constData());
	printf("1sec");
	return 0;
}

//---------------------------------------------------------
/**
 * @brief main()
 * @return N/A
 */
//---------------------------------------------------------
int main(int argc, char *argv[])
{
    int rc = 0;
    
    QCoreApplication a(argc, argv);

		//-----------------------------------------------------
    /** 시그널 처리를 등록한다.. */
    //-----------------------------------------------------
    //signal(SIGINT, cleanup_on_sig);
    //signal(SIGTERM, cleanup_on_sig);    
        
    g_collector = new UCollector();
    g_collector->init(argc, argv);
    
    return rc;
}



//---------------------------------------------------------
/**
 * @brief 시그널처리 함수(프로세스 종료)
 * @return N/A
 */
//---------------------------------------------------------
void cleanup_on_sig(int catched_signal   /**< Posix 시그널 */
) {
    //-----------------------------------------------------
    /** SIGINT, SIGTERM이 발생하는 경우 Application을 종료한다.(이때 CleanUp 객체가 실행됨)  */
    //-----------------------------------------------------
    if (catched_signal == SIGINT || catched_signal == SIGTERM) {
        qDebug("%p:Catched 'SIGINT'!!!\n", QThread::currentThreadId());
        g_collector->exit(0);
    }
}
