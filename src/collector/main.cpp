//---------------------------------------------------------
/**
 * @file   main.cpp
 * @Author frogmon (dyujhc@gmail.com)
 * @date   2018-03-27
 * @brief  ���� ���μ��� 
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
    /** �ñ׳� ó���� ����Ѵ�.. */
    //-----------------------------------------------------
    //signal(SIGINT, cleanup_on_sig);
    //signal(SIGTERM, cleanup_on_sig);    
        
    g_collector = new UCollector();
    g_collector->init(argc, argv);
    
    return rc;
}



//---------------------------------------------------------
/**
 * @brief �ñ׳�ó�� �Լ�(���μ��� ����)
 * @return N/A
 */
//---------------------------------------------------------
void cleanup_on_sig(int catched_signal   /**< Posix �ñ׳� */
) {
    //-----------------------------------------------------
    /** SIGINT, SIGTERM�� �߻��ϴ� ��� Application�� �����Ѵ�.(�̶� CleanUp ��ü�� �����)  */
    //-----------------------------------------------------
    if (catched_signal == SIGINT || catched_signal == SIGTERM) {
        qDebug("%p:Catched 'SIGINT'!!!\n", QThread::currentThreadId());
        g_collector->exit(0);
    }
}
