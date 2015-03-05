#ifndef BREAK_H
#define BREAK_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class Break;
}

class Break : public QWidget
{
    Q_OBJECT

public:
    explicit Break(QWidget *parent = 0);
    ~Break();

private:
    Ui::Break *ui;
    bool breakon;
    QDateTime progstart;

private slots:
    void startbreak(QTimer*, QDateTime);
    void barprogress();
    void setbreaktime(int);
    void endbreak();

signals:
    void breakover(double);
};

#endif // BREAK_H
