#ifndef COMPLETEDETAILS_H
#define COMPLETEDETAILS_H

#include <QWidget>
#include <QDateTime>

namespace Ui {
class CompleteDetails;
}

class CompleteDetails : public QWidget
{
    Q_OBJECT

public:
    explicit CompleteDetails(QWidget *parent = 0);
    ~CompleteDetails();

private:
    Ui::CompleteDetails *ui;

private slots:
    void report(QDateTime,QDateTime,QStringList);
    void finished();

signals:
    void reset();
};

#endif // COMPLETEDETAILS_H
