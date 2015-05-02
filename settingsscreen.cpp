#include "settingsscreen.h"
#include "ui_settingsscreen.h"



SettingsScreen::SettingsScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsScreen)
{

    ui->setupUi(this);
    this->setParent(0);
    this->showFullScreen();
    connect(ui->DoneSet,SIGNAL(clicked()),this,SLOT(submit()));
    connect(ui->TagsSet,SIGNAL(editingFinished()),this,SLOT(textclean()));
    connect(ui->MinSet,SIGNAL(valueChanged(int)),this,SLOT(changetime(int)));
    //connect(ui->TimeSet,SIGNAL(dateTimeChanged(QDateTime)),this,SLOT(changemin(QDateTime)));
    connect(this,SIGNAL(update()),this,SLOT(showupdate()));

    timestart = timestart.currentDateTime();
    ui->TimeSet->setDateTime(timestart);
    ui->TimeSet->setDateTimeRange(timestart,timestart.addDays(3));
}

SettingsScreen::~SettingsScreen()
{
    delete ui;
}

void SettingsScreen::submit(){
    //get tags
    QString inputtags = ui->TagsSet->text();
    inputtags = inputtags.remove(" ");
    tags = inputtags.split("#", QString::SkipEmptyParts);

    //make output
    QString outsave;
    for (int i=0; i<tags.length(); i++){
        outsave.append("#");
        outsave.append(tags.at(i));
    }
    outsave.append(" -start- ");
    outsave.append(timestart.toString("dd.MMM.yy-hh:ss"));
    outsave.append(" -until- ");
    outsave.append(timeend.toString("dd.MMM.yy-hh:ss"));


    //open file and write
    QFile savefile("/Users/jordan/Documents/CompUse.txt");
    if(savefile.open(QIODevice::Append)){
        QTextStream stream(&savefile);
        stream << outsave << endl;
    }
    else{

    }
    savefile.close();

    this->setParent(0);
    this->showNormal();

    emit submitted(tags,timestart,timeend);
    return;
}

void SettingsScreen::textclean()
{
    //cleantext to have proper format before stuff?
    return;
}

void SettingsScreen::changetime(int newmin)
{
    //add minutes to end time and display in TimeSet
    timestart = timestart.currentDateTime();
    timeend = timestart.addSecs(60 * newmin);
    emit update();
    return;
}

/*void SettingsScreen::changemin(QDateTime newtime)
{
    //find differance between TimeSet and timestart and display in MinSet
    timestart = timestart.currentDateTime();
    timeend = newtime;
    emit update();
    return;
}*/

void SettingsScreen::showupdate()
{
    ui->TimeSet->setDateTime(timeend);
    ui->MinSet->setValue(timestart.secsTo(timeend) / 60);
    return;
}
