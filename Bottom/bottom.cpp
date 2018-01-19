#include "bottom.h"
#include "ui_bottom.h"
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <QTimer>
#include "joint.h"

using std::vector;
using std::sort;

#define LHDEBUG 0
#define BOTTOM_UPDATE_INTEVAL 50000000

Bottom::Bottom(QWidget *parent) :
    QWidget(parent),
    uiBottom(new Ui::Bottom)
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    uiBottom->setupUi(this);
    joint = NULL;
    timerBottom = NULL;
    isCANInitialSucceed = false;
}

Bottom::~Bottom()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    delete uiBottom;
}

void Bottom::waitingForWidgetReady()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    this->on_btnUpdateID_clicked();
}

void Bottom::dealIDChanged(int newID)
{
//    on_btnUpdateID_clicked();
}

void Bottom::updateEnableDriver()
{
    uint16_t data16 = 0;
    jointGet(SYS_ENABLE_DRIVER, 2, (Joint *)joint, (void *)&data16, 50, NULL);
    if(data16) {
        uiBottom->enableDriverPushButton_2->setStyleSheet("background-color:green");
        uiBottom->enableDriverPushButton->setText("Enabled");
    }else {
        uiBottom->enableDriverPushButton_2->setStyleSheet("");
        uiBottom->enableDriverPushButton->setText("Disabled");
    }
}

void Bottom::updateWorkModePushButton()
{
    uint16_t workMode = 0;
//    QString workModePushButtonStr = "background-color:green";
    uiBottom->workModePushButton->setStyleSheet("background-color:green");
    jointGetMode(joint, &workMode, 50, NULL);
    switch (workMode) {
    case 0:
        uiBottom->workModePushButton->setText("OPEN");
        break;
    case 1:
        uiBottom->workModePushButton->setText("CURRENT");
        break;
    case 2:
        uiBottom->workModePushButton->setText("SPEED");
        break;
    case 3:
        uiBottom->workModePushButton->setText("POSITION");
        break;
    default:
        break;
    }

}

void Bottom::updateConnected()
{
    QString connectedPushButtonStr = "background-color:green";
    uiBottom->connectedPushButton->setStyleSheet(connectedPushButtonStr);
}

void Bottom::updateIfError()
{
    uint16_t data16 = 0;
//    QString ifErrorPushButtonStr = "background-color:green";
    jointGet(SYS_ERROR, 2, (Joint *)joint, (void *)&data16, 50, NULL);
    if(data16 != 0) {
        uiBottom->ifErrorPushButton->setStyleSheet("");
    }else {
        uiBottom->ifErrorPushButton->setStyleSheet("background-color:green");
    }
}

void Bottom::on_btnUpdateID_clicked()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!isCANInitialSucceed) {
        isCANInitialSucceed = true;
        qDebug("===============");
        int re = startMaster(0);
        qDebug() << re << "startMaster(0)";
    }
    uiBottom->cmbID->clear();
    vector<uint32_t> vectID;
    JOINT_HANDLE tempj = NULL;
    uint16_t ID = 0;
    for(int i=1;i<MAX_JOINTS+1;i++) {
        tempj = jointUp(i, masterLoadSendFunction(0));
        if(tempj) {
            int re = jointGetId(tempj, &ID, 100, NULL);
            vectID.push_back(ID);
            qDebug() << "发现这个ID:" << ID << re;
        }
    }
    if(vectID.empty()) {
//        qDebug() << vectID.empty();
        QMessageBox::warning(this,"WARNING","Module not detected", QMessageBox::Ok);
        return ;
    }
    sort(vectID.begin(), vectID.end());
#if 0
    qDebug() << "vectID.back()" << vectID.back();
#endif
    joint = jointSelect(vectID.back());
    for(vector<uint32_t>::iterator iter = vectID.begin();
        iter != vectID.end();
        ++iter) {
        uiBottom->cmbID->addItem(QString::number(*iter, 10));
    }
}

void Bottom::on_enableDriverPushButton_clicked()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        return ;
    }
    uint16_t data16 = 0;
    jointGet(SYS_ENABLE_DRIVER, 2, (Joint *)joint, (void *)&data16, 50, NULL);
    bool isEbable = !data16;
    uint16_t value = (int)isEbable;
    qDebug() << data16 << isEbable;
    jointSet(SYS_ENABLE_DRIVER, 2, (Joint *)joint, (void *)&value, 50, NULL);
    updateEnableDriver();
}

void Bottom::on_btnFlash_clicked()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        return ;
    }
    jointSetSave2Flash(joint, 50, NULL);
    QMessageBox::information(this, tr("information"), tr("    Succeed     "), QMessageBox::Ok);
}

void Bottom::on_btnLoad_clicked()
{
    QMessageBox::information(this, tr("information"), tr("该功能还没实现！"), QMessageBox::Ok);
}

void Bottom::on_btnSave_clicked()
{
    QMessageBox::information(this, tr("information"), tr("该功能还没实现！"), QMessageBox::Ok);
}

void Bottom::on_cmbID_currentIndexChanged(int index)
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        return ;
    }
    int jointID = uiBottom->cmbID->currentText().toInt();
#if 1
    qDebug() << "jointID  = " << jointID;
#endif
    emit cmbIDChanged(jointID);
    if(!timerBottom) {
        timerBottom = new QTimer(this);
        connect(timerBottom, SIGNAL(timeout()), this, SLOT(slotTimerBottomDone()));
        timerBottom->start(BOTTOM_UPDATE_INTEVAL);
    }
    slotTimerBottomDone();
    uint16_t data16 = 0;
    jointGetType(joint, &data16, 50, NULL);
    //#define MODEL_TYPE_M14        0x010
    //#define MODEL_TYPE_M17        0x020
    //#define MODEL_TYPE_M17V2      0x021
    //#define MODEL_TYPE_M20        0x030
    //#define MODEL_TYPE_M20V2      0x031
    //#define MODEL_TYPE_M20E       0x031
    //#define MODEL_TYPE_LIFT       0x040
    QString str;
    switch(data16) {
    case MODEL_TYPE_M14:
        str = "M14";
        break;
    case MODEL_TYPE_M17:
        str = "M17";
        break;
    case MODEL_TYPE_M17V2:
        str = "M17V2";
        break;
    case MODEL_TYPE_M20:
        str = "M20";
        break;
    case MODEL_TYPE_M20V2:
        str = "M20V2";
        break;
    case MODEL_TYPE_LIFT:
        str = "LIFT";
        break;
    default :
        break;
    }
    uiBottom->typeLabel->setText(str);
    jointGet(SYS_REDU_RATIO, 2, (Joint *)joint, (void *)&data16, 50, NULL);
    uiBottom->ratioLabel->setText(QString::number(data16, 10));
    jointGet(SYS_FW_VERSION, 2, (Joint *)joint, (void *)&data16, 50, NULL);
    uiBottom->firmLabel->setText(QString::number(data16, 10));
}

void Bottom::slotTimerBottomDone()
{
    if(!joint) {
        return ;
    }
    updateEnableDriver();
    updateWorkModePushButton();
    updateConnected();
    updateIfError();
}


