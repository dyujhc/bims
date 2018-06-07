
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "echoclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    EchoClient client(QUrl(QStringLiteral("ws://127.0.0.1:7788")), debug);
    QObject::connect(&client, &EchoClient::closed, &a, &QCoreApplication::quit);

    return a.exec();
}