#include "completedetails.h"
#include "ui_completedetails.h"

CompleteDetails::CompleteDetails(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompleteDetails)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(finished()));
}

CompleteDetails::~CompleteDetails()
{
    delete ui;
}

void CompleteDetails::report(QDateTime starttime, QDateTime endtime, QStringList taglist){
    this->show();

    double timeused = starttime.secsTo(endtime) / 60;
    ui->MinCount->display(timeused);

    for(int i=0; i<taglist.length(); i++){
        ui->Tags->append("#");
        ui->Tags->append(taglist.at(i));
        ui->Tags->append("  ");
    }

    return;
}

void CompleteDetails::finished()
{
    this->hide();
    emit reset();
    return;
}
