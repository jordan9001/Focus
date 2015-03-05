#include "break.h"
#include "ui_break.h"
#include <QTimer>


Break::Break(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Break)
{
    ui->setupUi(this);
    breakon = false;

    ui->BreakTime->setValue(15);
    connect(ui->BreakTime,SIGNAL(valueChanged(int)),this,SLOT(setbreaktime(int)));
    connect(ui->BreakButton,SIGNAL(clicked()),this,SLOT(endbreak()));
}

Break::~Break()
{
    delete ui;
}

void Break::startbreak(QTimer* progtimer, QDateTime maxendtime)
{
    breakon = true;
    progstart = QDateTime::currentDateTime();
    this->show();
    //set max break to until end.
    double rangeend = QDateTime::currentDateTime().secsTo(maxendtime) / 60;
    ui->BreakTime->setRange(1, rangeend);
    ui->BreakProg->setMinimum(0);
    ui->BreakProg->setMaximum(ui->BreakTime->value() * 60 * 1000);
    //progressbar with time
    connect(progtimer,SIGNAL(timeout()),this,SLOT(barprogress()));
    return;
}

void Break::barprogress()
{
    double timeelapsed = progstart.secsTo(QDateTime::currentDateTime());
    if( timeelapsed < (ui->BreakTime->value() * 60) ){
        ui->BreakProg->setValue(timeelapsed);
    }
    else{
        endbreak();
    }

    return;
}

void Break::setbreaktime(int maxminutes)
{
    ui->BreakProg->setMaximum(maxminutes * 60 * 1000);
    return;
}

void Break::endbreak()
{
    if(breakon){
        QApplication::beep();
        breakon = false;
        double breakduration = progstart.secsTo(QDateTime::currentDateTime());
        this->hide();
        emit breakover(breakduration);
    }
    else{

    }
    return;
}
