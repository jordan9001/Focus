#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDateTime>
#include <QFile>
#include <QTextStream>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QTimer progsteps;
    double totalmsec;
    double intervalmsec;
    QDateTime markstart;
    QDateTime markend;
    QStringList taglist;

    QPoint dragPosition;

private slots:
    void startcount(QStringList,QDateTime,QDateTime);
    void updateprog();
    void takebreak();
    void processbreak(double);
    void seshend();

signals:
    void complete(QDateTime, QDateTime, QStringList);
    void breaksignal(QTimer*, QDateTime);
};

#endif // WIDGET_H
