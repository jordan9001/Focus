#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(&progsteps,SIGNAL(timeout()),this,SLOT(updateprog()));
    connect(ui->BreakButton,SIGNAL(clicked()),this,SLOT(takebreak()));
    connect(ui->DoneButton,SIGNAL(clicked()),this,SLOT(seshend()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::startcount(QStringList tags,QDateTime starttime,QDateTime endtime)
{
    this->show();
    ui->Progress->setStyleSheet("QProgressBar::chunk { background-color: rgb(147, 045, 203); }");
    markstart = starttime;
    markend = endtime;
    taglist = tags;
    //set tags
    QString tagscomp;
    for(int i=0; i<tags.length(); i++){
        tagscomp.append("#");
        tagscomp.append(tags.at(i));
        tagscomp.append("  ");
    }
    ui->TagsArea->setText(tagscomp);

    //calculate min/max for timer
    totalmsec = markstart.secsTo(markend) * 1000;
    intervalmsec = 1000;

    ui->Progress->setMinimum(0);
    ui->Progress->setMaximum(totalmsec);

    progsteps.setSingleShot(false);
    progsteps.start(intervalmsec);

    return;
}

void Widget::updateprog()
{
    double timeused = markstart.secsTo(QDateTime::currentDateTime()) * 1000;
    ui->Progress->setValue(timeused);

    ui->TimeDone->display(timeused / 1000);
    ui->TimeLeft->display((totalmsec - timeused) / 1000);

    if(timeused < totalmsec){

    }
    else{
        QApplication::beep();
        ui->Progress->setRange(0,0);
        int modrest = timeused / 1000;
        switch (modrest % 2) {
            case 0:
                ui->Progress->setStyleSheet("QProgressBar::chunk { background-color: rgb(147, 000, 000); }");
                break;
            case 1:
                ui->Progress->setStyleSheet("QProgressBar::chunk { background-color: rgb(147, 045, 000); }");
                break;

        }
    }


    return;
}

void Widget::takebreak()
{
    this->hide();
    emit breaksignal(&progsteps, markend);

    return;
}

void Widget::processbreak(double breaktime)
{
    this->show();
    QDateTime curtime = QDateTime::currentDateTime();
    //write break data
    QString outtext = "---Break ";
    outtext += QString::number(breaktime /1000);
    outtext += " seconds- @ ";
    outtext.append(curtime.toString("dd.MMM.yy-hh:ss"));

    //open file and write
    QFile savefile("/Users/jordan/Documents/CompUse.txt");
    if(savefile.open(QIODevice::Append)){
        QTextStream stream(&savefile);
        stream << outtext << endl;
    }
    else{

    }
    savefile.close();

    return;
}
void Widget::seshend()
{
    //write end line
    QDateTime curtime = QDateTime::currentDateTime();
    progsteps.stop();
    QString outtext = "---End- @ ";
    outtext.append(curtime.toString("dd.MMM.yy-hh:ss"));

    QFile savefile("/Users/jordan/Documents/CompUse.txt");
    if(savefile.open(QIODevice::Append)){
        QTextStream stream(&savefile);
        stream << outtext << endl;
        stream << "---" << endl;
    }
    else{

    }
    savefile.close();
    this->hide();
    emit complete(markstart, curtime, taglist);
    return;
}
