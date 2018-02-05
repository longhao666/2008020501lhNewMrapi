#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "setandhealth.h"
#include "pid.h"
#include "bottom.h"
#include "move.h"
#include "oscilloscope.h"
#include <QTime>

#define LHDEBUG 0
void delay(int s) ;


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    joint1(NULL)
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    ui->setupUi(this);
    int i = 0;
    for(i=0;i<5;i++) {
        if(i == 0) {
            break;
        }
    }
    qDebug() << "i = " << i;
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

    oscilloScope = new OscilloScope;
    ui->oscilloScopeVerticalLayout->addWidget(oscilloScope);

    connect(bottom, &Bottom::cmbIDChanged, pid, &Pid::pidInit);
    connect(bottom, &Bottom::cmbIDChanged, move, &Move::moveInit);
    connect(bottom, &Bottom::cmbIDChanged, setAndHealth, &SetAndHealth::SetAndHealthIint);
    connect(bottom, &Bottom::cmbIDChanged, oscilloScope, &OscilloScope::OscilloScopeInitialize);
    connect(this, &Widget::widgetAllReady, bottom, &Bottom::waitingForWidgetReady);
    connect(this, SIGNAL(destroyed(QObject*)), move, SLOT(ClickStopButton()));
    connect(setAndHealth, &SetAndHealth::ZeroPositionSeted, move, &Move::ClickStopButton);
    connect(bottom, &Bottom::cmbIDJoint, this, &Widget::jointQuit);

    emit widgetAllReady();
}

void Widget::jointQuit(JOINT_HANDLE joint)
{
    bottom->joint = NULL;
    move->joint = NULL;
    pid->joint = NULL;
    setAndHealth = NULL;
    oscilloScope->joint = NULL;
    delay(3);
    qDebug("===============");
    int re = stopMaster(0);
    qDebug() << re << "stopMaster(0)";
    qDebug() << joint;
#if 0
    int i = 50;
    re = jointDown((void *)&i);
#else
    re = jointDown(joint);
#endif
    qDebug() << "re" << re << "jointDown(joint)";

}


void delay(int s) {
    QTime t;
    t.start();
    while(t.elapsed() < 1000 * s)
        QCoreApplication::processEvents();
}
