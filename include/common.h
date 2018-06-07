//--------------------------------------------------------------------
/**
 * @file common.h
 * @author dyujhc@gmail.com
 * @date 2017/08/25
 * @brief 전역으로 사용되는 구조체 및 사전정의
 *
*/
//--------------------------------------------------------------------
#include <QString>
#include <QDir>
#include <QFileInfo>
#include <QThread>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QList>

#include <signal.h>
#include "utimer.h"
#include "global.h"

#ifndef COMMON
#define COMMON

extern  UTimer*  g_timer;
extern  UGlobal* g_global;

//---------------------------------------------------------
/* 사전정의 문자열 */
//---------------------------------------------------------
#define BIMS_HOME                       "BIMS_HOME"                     /**< 홈디렉토리                */
#define YMSF                            "yyyy/MM/dd hh:mm:ss.z"         /**< 날짜시각 포맷형태 */

#define KEY_TIMER                       "global/TIMER"                  /**< 타이머발생간격(밀리초)       */
#define KEY_WS_SERVICENAME              "wserver/SERVICENAME"           /**< 웹소켓서비스명 */
#define KEY_WS_IP                       "wserver/SERVERIP"              /**< 웹소켓서버 IP */
#define KEY_WSPORT                      "wserver/PORT"                  /**< 웹소켓서버 Listen 포트 */
#define MAX_CONNECTION                  "wserver/MAX_CONNECTION"        /**< 웹소켓서버 최대 세션수 */

#define KEY_DB_USERNAME                 "dbms/USERNAME"                 /**< 유저ID */
#define KEY_WS_PASSWORD                 "dbms/PASSWORD"                 /**< 비밀번호 */
#define KEY_WS_DBNAME                   "dbms/DBNAME"                   /**< 데이터베이스명 */
#define KEY_WS_HOSTNAME                 "dbms/HOSTNAME"                 /**< 호스트주소 */


//---------------------------------------------------------
/** 0xF000 ~ 0xFFFF : 시스템로깅 */
//---------------------------------------------------------
#define NOLOGG (0x0000) /**< 시스템 로깅 없음(화면출력만..) */
#define SYSLOG (0xF000) /**< 시스템 로깅메시지 */
#define OPF001 (0xF001) /**< 로그인 */
#define OPF002 (0xF002) /**< 로그아웃 */
#define OPMAPI (0xFFFD) /**< 맵매칭 로깅 */
#define OPTMAX (0xFFFE) /**< TAX 로깅 */
#define OPHEXA (0xFFFF) /**< HEXA 로깅 */

#define UTC_YMSF_SZ 19

//---------------------------------------------------------
/* 디렉토리관련 유틸리티 전역함수 */
//---------------------------------------------------------
QString uBaseHomeDir(void);

//---------------------------------------------------------
/* 파일관련 유틸리티 전역함수 */
//---------------------------------------------------------
bool    uFileExists(QString filepath);
QString uBaseFileName(QString filepath);

//---------------------------------------------------------
/* 로그관련 유틸리티 전역함수 */
//---------------------------------------------------------
void g_logger(char const* file, int line, char const* func, short opcode, char const* fmt, ...);
#define logging(opcode, fmt, args...) g_logger((char const*)__FILE__, (int)__LINE__, (char const*)__func__, (short)(opcode), (char const*)(fmt), ## args)


#endif // UBS_COMMON


