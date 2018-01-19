#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "setandhealth.h"
#include "pid.h"
#include "bottom.h"
#include "move.h"
//#include "oscilloscope.h"

#define LHDEBUG 0


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    joint1(NULL)
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    ui->setupUi(this);
    bottom = NULL;
    pid = NULL;
    setAndHealth = NULL;
    move = NULL;
    oscilloScope = NULL;
    widgetInit();
}

Widget::~Widget()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    delete ui;
}

void Widget::widgetInit()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif

    bottom = new Bottom;
    ui->BottomLayout->addWidget(bottom);

    move = new Move;
    ui->MoveLayout->addWidget(move);

    setAndHealth = new SetAndHealth;
    ui->setAndHealthLayout->addWidget(setAndHealth);

    pid = new Pid;
    ui->pidLayout->addWidget(pid);

//    oscilloScope = new OscilloScope;
//    ui->oscilloScopeVerticalLayout->addWidget(oscilloScope);

    connect(bottom, &Bottom::cmbIDChanged, pid, &Pid::pidInit);
//    connect(bottom, &Bottom::cmbIDChanged, move, &Move::moveInit);
//    connect(bottom, &Bottom::cmbIDChanged, setAndHealth, &SetAndHealth::SetAndHealthIint);
//    connect(bottom, &Bottom::cmbIDChanged, oscilloScope, &OscilloScope::OscilloScopeInitialize);
    connect(this, &Widget::widgetAllReady, bottom, &Bottom::waitingForWidgetReady);
//    connect(setAndHealth, &SetAndHealth::ZeroPositionSeted, move, &Move::ClickStopButton);

    emit widgetAllReady();
}
