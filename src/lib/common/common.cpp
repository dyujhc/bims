//--------------------------------------------------------------------
/**
 * @file   common.cpp
 * @author dyujhc@gmail.com
 * @date   2018/08/22
 * @brief  전역으로 사용되는 함수
*/
//--------------------------------------------------------------------

#include "common.h"

UTimer* g_timer;
UGlobal* g_global;

//---------------------------------------------------------
/**
 * @brief  어플케이션을 'path' + '../' 기준으로 홈디렉토리를 반환한다.
 * @return 파일명
 */
//---------------------------------------------------------
QString uBaseHomeDir(void) {
    if(qgetenv(BIMS_HOME).isNull()) {
        QDir dir(QCoreApplication::applicationDirPath());
        dir.cdUp();
        qputenv(BIMS_HOME, dir.path().toUtf8());
    }
    return qgetenv(BIMS_HOME);
}


//---------------------------------------------------------
/**
 * @brief 파일이 존재하는 지 확인한다.
 * @return bool (true:존재, false:존재하지 않음)
 */
//---------------------------------------------------------
bool uFileExists(QString filepath) {
    QFileInfo fi(filepath);
    return fi.exists();
}


//---------------------------------------------------------
/**
 * @brief 로그를 저장 한다.
 * @return N/A
 */
//---------------------------------------------------------
void g_logger(char const* file,					/**< __FILE__ 매크로 */
              int         line,					/**< __LINE__ 매크로 */
              char const* func,					/**< __func__ 매크로 */
              short       opcode,				/**< Opcode */
              char const* fmt,					/**< 포맷형식 */
              ...												/**< 가변인자 */
) {
    char*     buffer;
    char      new_str[2048];
    QString msg;
    va_list   ap;
    int       len;
    
    //-----------------------------------------------------
    /** 가변인자를 포맷에 맞춰 문자열을 생성한다. */ 
    //-----------------------------------------------------
    va_start(ap, fmt); // use variable arg list
    len = qvsnprintf(new_str, sizeof(new_str), fmt, ap);
    va_end(ap);
    msg.append("[");
    
    if (g_timer) {
    	msg.append(g_timer->getStrNowUtcYmsf());
    }
    
    msg.append("]");

    //-----------------------------------------------------
    /** 시스템시각, 파일명, 라인, 함수명을 추가로 붙여 데이터를 생성한다. */
    //-----------------------------------------------------
    msg.append("[");
    msg.append(uBaseFileName(file));
    msg.append(":");
    msg.append(QString::number(line));
    msg.append(":");
    msg.append(func);
    msg.append("]");

    msg.append(":");
    msg.append(new_str);    
    
    printf("%s", msg.toUtf8().constData());
        
}    

//---------------------------------------------------------
/**
 * @brief Path와 확장자가 제거된 파일명을 반환한다.
 * @return 파일명
 */
//---------------------------------------------------------
QString uBaseFileName(QString filepath) {
    QFileInfo fi(filepath);
    QString base = fi.baseName();
    return base;
}
