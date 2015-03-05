#include "settingsscreen.h"
#include <QApplication>

#include "widget.h"
#include "completedetails.h"
#include "break.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SettingsScreen w;
    w.show();
    Widget q;
    q.hide();
    CompleteDetails d;
    d.hide();
    Break b;
    b.hide();

    QObject::connect(&w,SIGNAL(submitted(QStringList,QDateTime,QDateTime)),&q,SLOT(startcount(QStringList,QDateTime,QDateTime)));
    QObject::connect(&q,SIGNAL(complete(QDateTime,QDateTime,QStringList)),&d,SLOT(report(QDateTime,QDateTime,QStringList)));
    QObject::connect(&q,SIGNAL(breaksignal(QTimer*,QDateTime)),&b,SLOT(startbreak(QTimer*,QDateTime)));
    QObject::connect(&b,SIGNAL(breakover(double)),&q,SLOT(processbreak(double)));
    QObject::connect(&d,SIGNAL(reset()),&w,SLOT(show()));

    return a.exec();
}
