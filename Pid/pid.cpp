#include "pid.h"
#include "ui_pid.h"
#include <QDebug>

#define LHDEBUG 0

Pid::Pid(QWidget *parent) :
    QWidget(parent),
    uiPid(new Ui::Pid)
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    uiPid->setupUi(this);
    joint = NULL;
}

Pid::~Pid()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    delete uiPid;
}

void Pid::pidInit(int ID)
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    this->joint = jointGetJoint(ID);
    if(!joint) {
        return ;
    }
    on_adjustGroupComboBox_currentIndexChanged(uiPid->adjustGroupComboBox->currentIndex());
    showMaxLimit();
}

void Pid::showSEVPID()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        return ;
    }
    uint16_t data16 = 0;
    // 位置环P
    jointGetPositionP(joint, &data16, 100, NULL);
    uiPid->POS_PSpinBox->setValue(data16);
    // 位置环I
    jointGetS_POSITION_I(joint, &data16, 100, NULL);
    uiPid->POS_ISpinBox->setValue(data16);
    // 位置环D
    jointGetS_POSITION_D(joint, &data16, 100, NULL);
    uiPid->POS_DSpinBox->setValue(data16);
    // 位置死区
    jointGetPositionDs(joint, &data16, 100, NULL);
    uiPid->POS_DSSpinBox->setValue(data16);
    // 速度环P
    jointGetSpeedP(joint, &data16, 100, NULL);
    uiPid->SPD_PSpinBox->setValue(data16);
    // 速度环I
    jointGetSpeedI(joint, &data16, 100,NULL);
    uiPid->SPD_ISpinBox->setValue(data16);
    // 速度环D
    jointGetS_SPEED_D(joint, &data16, 100, NULL);
    uiPid->SPD_DSpinBox->setValue(data16);
    // 速度死区
    jointGetS_SPEED_DS(joint, &data16, 100, NULL);
    uiPid->SPD_DSSpinBox->setValue(data16);
    // 电流环P
    jointGetCurrP(joint, &data16, 100, NULL);
    uiPid->CUR_PSpinBox->setValue(data16);
    // 电流环I
    jointGetCurrI(joint, &data16, 100, NULL);
    uiPid->CUR_ISpinBox->setValue(data16);
    // 电流环D
    jointGetS_CURRENT_D(joint, &data16, 100, NULL);
    uiPid->CUR_DSpinBox->setValue(data16);
}

void Pid::showMPID()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        return ;
    }
    uint16_t data16 = 0;
    jointGetM_POSITION_P(joint, &data16, 100, NULL);
    uiPid->POS_PSpinBox->setValue(data16);
    // 位置环I
    jointGetM_POSITION_I(joint, &data16, 100, NULL);
    uiPid->POS_ISpinBox->setValue(data16);
    // 位置环D
    jointGetM_POSITION_D(joint, &data16, 100, NULL);
    uiPid->POS_DSpinBox->setValue(data16);
    // 位置死区
    jointGetM_POSITION_DS(joint, &data16, 100, NULL);
    uiPid->POS_DSSpinBox->setValue(data16);
    // 速度环P
    jointGetM_SPEED_P(joint, &data16, 100, NULL);
    uiPid->SPD_PSpinBox->setValue(data16);
    // 速度环I
    jointGetM_SPEED_I(joint, &data16, 100,NULL);
    uiPid->SPD_ISpinBox->setValue(data16);
    // 速度环D
    jointGetM_SPEED_D(joint, &data16, 100, NULL);
    uiPid->SPD_DSpinBox->setValue(data16);
    // 速度死区
    jointGetM_SPEED_DS(joint, &data16, 100, NULL);
    uiPid->SPD_DSSpinBox->setValue(data16);
    // 电流环P
    jointGetM_CURRENT_P(joint, &data16, 100, NULL);
    uiPid->CUR_PSpinBox->setValue(data16);
    // 电流环I
    jointGetM_CURRENT_I(joint, &data16, 100, NULL);
    uiPid->CUR_ISpinBox->setValue(data16);
    // 电流环D
    jointGetM_CURRENT_D(joint, &data16, 100, NULL);
    uiPid->CUR_DSpinBox->setValue(data16);
}

void Pid::showLPID()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        return ;
    }
    uint16_t data16 = 0;
    jointGetL_POSITION_P(joint, &data16, 100, NULL);
    uiPid->POS_PSpinBox->setValue(data16);
    // 位置环I
    jointGetL_POSITION_I(joint, &data16, 100, NULL);
    uiPid->POS_ISpinBox->setValue(data16);
    // 位置环D
    jointGetL_POSITION_D(joint, &data16, 100, NULL);
    uiPid->POS_DSpinBox->setValue(data16);
    // 位置死区
    jointGetL_POSITION_DS(joint, &data16, 100, NULL);
    uiPid->POS_DSSpinBox->setValue(data16);
    // 速度环P
    jointGetL_SPEED_P(joint, &data16, 100, NULL);
    uiPid->SPD_PSpinBox->setValue(data16);
    // 速度环I
    jointGetL_SPEED_I(joint, &data16, 100,NULL);
    uiPid->SPD_ISpinBox->setValue(data16);
    // 速度环D
    jointGetL_SPEED_D(joint, &data16, 100, NULL);
    uiPid->SPD_DSpinBox->setValue(data16);
    // 速度死区
    jointGetL_SPEED_DS(joint, &data16, 100, NULL);
    uiPid->SPD_DSSpinBox->setValue(data16);
    // 电流环P
    jointGetL_CURRENT_P(joint, &data16, 100, NULL);
    uiPid->CUR_PSpinBox->setValue(data16);
    // 电流环I
    jointGetL_CURRENT_I(joint, &data16, 100, NULL);
    uiPid->CUR_ISpinBox->setValue(data16);
    // 电流环D
    jointGetL_CURRENT_D(joint, &data16, 100, NULL);
    uiPid->CUR_DSpinBox->setValue(data16);
}

void Pid::showMaxLimit()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    uint16_t data16 = 0;
    // 最大加速度
    jointGetMaxAcceleration(joint, &data16, 100, NULL);
    uiPid->maxAccLineEdit->setText(QString::number(data16, 10));
    // 最大速度
    jointGetMaxSpeed(joint, &data16, 100, NULL);
    uiPid->maxSpdLineEdit->setText(QString::number(data16/100, 10));

    jointGetLIT_MAX_CURRENT(joint, &data16, 100, NULL);
    uiPid->maxCurLineEdit->setText(QString::number(data16, 10));

    jointGetLIT_MIN_POSITION_L(joint, &data16, 100, NULL);
    uiPid->minPosLLineEdit->setText(QString::number(data16, 10));

    jointGetLIT_MIN_POSITION_H(joint, &data16, 100, NULL);
    uiPid->minPosHLineEdit->setText(QString::number(data16, 10));

    jointGetLIT_MAX_POSITION_L(joint, &data16, 100, NULL);
    uiPid->maxPosLLineEdit->setText(QString::number(data16, 10));

    jointGetLIT_MAX_POSITION_H(joint, &data16, 100, NULL);
    uiPid->maxPosHLineEdit->setText(QString::number(data16, 10));
}

void Pid::on_POS_PSpinBox_editingFinished()
{
    if(!joint) {
        uiPid->POS_PSpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->POS_PSpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetPositionP(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_POSITION_P(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_POSITION_P(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_POS_ISpinBox_editingFinished()
{
    if(!joint) {
        uiPid->POS_ISpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->POS_ISpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetS_POSITION_I(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_POSITION_I(joint,str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_POSITION_I(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_POS_DSpinBox_editingFinished()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        uiPid->POS_DSpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->POS_DSpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetS_POSITION_D(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_POSITION_D(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_POSITION_D(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_POS_DSSpinBox_editingFinished()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        uiPid->POS_DSSpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->POS_DSSpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetPositionDs(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_POSITION_DS(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_POSITION_DS(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_SPD_PSpinBox_editingFinished()
{
    if(!joint) {
        uiPid->SPD_PSpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->SPD_PSpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetSpeedP(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_SPEED_P(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_SPEED_P(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_SPD_ISpinBox_editingFinished()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        uiPid->SPD_ISpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->SPD_ISpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetSpeedI(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_SPEED_I(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_SPEED_I(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_SPD_DSpinBox_editingFinished()
{
    if(!joint) {
        uiPid->SPD_DSpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->SPD_DSpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetS_SPEED_D(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_SPEED_D(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_SPEED_D(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_SPD_DSSpinBox_editingFinished()
{
    if(!joint) {
        uiPid->SPD_DSSpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->SPD_DSSpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetS_SPEED_DS(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_SPEED_DS(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_SPEED_DS(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_CUR_PSpinBox_editingFinished()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        uiPid->CUR_PSpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->CUR_PSpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetCurrP(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_CURRENT_P(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_CURRENT_P(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_CUR_ISpinBox_editingFinished()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        uiPid->CUR_ISpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->CUR_ISpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetCurrI(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_CURRENT_I(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_CURRENT_I(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_CUR_DSpinBox_editingFinished()
{
    if(!joint) {
        uiPid->CUR_DSpinBox->setValue(0);
        return ;
    }
    QString str = uiPid->CUR_DSpinBox->text();
    int index = uiPid->adjustGroupComboBox->currentIndex();
    switch(index) {
    case 0:
        jointSetS_CURRENT_D(joint, str.toShort(), 100, NULL);
        break;
    case 1:
        jointSetM_CURRENT_D(joint, str.toShort(), 100, NULL);
        break;
    case 2:
        jointSetL_CURRENT_D(joint, str.toShort(), 100, NULL);
        break;
    default :
        break;
    }
}

void Pid::on_adjustGroupComboBox_currentIndexChanged(int index)
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    switch(index) {
        case 0:
            showSEVPID();
            break;
        case 1:
            showMPID();
            break;
        case 2:
            showLPID();
            break;
        default :
             break;
    }
}

void Pid::on_maxSpdLineEdit_editingFinished()
{
    if(!joint) {
        uiPid->maxSpdLineEdit->setText("");
        return ;
    }
    QString str = uiPid->maxSpdLineEdit->text();
    jointSetMaxSpeed(joint, str.toShort(), 100, NULL);
}

void Pid::on_maxAccLineEdit_editingFinished()
{
#if LHDEBUG
    qDebug() <<__DATE__<<__TIME__<<__FILE__<<__LINE__<<__func__;
#endif
    if(!joint) {
        uiPid->maxAccLineEdit->setText("");
        return ;
    }
    QString str = uiPid->maxAccLineEdit->text();
    jointSetMaxAcceleration(joint, str.toShort(), 100, NULL);
}

/**
 * @brief Pid::on_maxCurLineEdit_editingFinished
 */
void Pid::on_maxCurLineEdit_editingFinished()
{
    if(!joint) {
        uiPid->maxCurLineEdit->setText("");
        return ;
    }
    QString str = uiPid->maxCurLineEdit->text();
    // 设置最大的电流
    jointSetLIT_MAX_CURRENT(joint, str.toShort(), 100, NULL);
}

void Pid::on_minPosLLineEdit_editingFinished()
{
    if(!joint) {
        uiPid->minPosLLineEdit->setText("");
        return ;
    }
    QString str = uiPid->minPosLLineEdit->text();
    jointSetLIT_MIN_POSITION_L(joint, str.toShort(), 100, NULL);
}

void Pid::on_minPosHLineEdit_editingFinished()
{
    if(!joint) {
        uiPid->minPosHLineEdit->setText("");
        return ;
    }
    QString str = uiPid->minPosHLineEdit->text();
    jointSetLIT_MIN_POSITION_H(joint, str.toShort(), 100, NULL);
}

void Pid::on_maxPosLLineEdit_editingFinished()
{
    if(!joint) {
        uiPid->maxPosLLineEdit->setText("");
        return ;
    }
    QString str = uiPid->maxPosLLineEdit->text();
    jointSetLIT_MAX_POSITION_L(joint, str.toShort(), 100, NULL);
}

void Pid::on_maxPosHLineEdit_editingFinished()
{
    if(!joint) {
        uiPid->maxPosHLineEdit->setText("");
        return ;
    }
    QString str = uiPid->maxPosHLineEdit->text();
    jointSetLIT_MAX_POSITION_H(joint, str.toShort(), 100, NULL);
}
