#ifndef SETTINGSSCREEN_H
#define SETTINGSSCREEN_H

#include <QWidget>
#include <QDateTime>
#include <QFile>
#include <QTextStream>


namespace Ui {
class SettingsScreen;
}

class SettingsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsScreen(QWidget *parent = 0);
    ~SettingsScreen();

    QStringList tags;
    QDateTime timestart;
    QDateTime timeend;

private:
    Ui::SettingsScreen *ui;

private slots:
    void submit();
    void changetime(int);
    //void changemin(QDateTime newtime);
    void showupdate();
    void textclean();

signals:
    void update();
    void submitted(QStringList,QDateTime,QDateTime);
};

#endif // SETTINGSSCREEN_H
