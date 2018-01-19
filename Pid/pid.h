#ifndef PID_H
#define PID_H

#include "pid_global.h"
#include <QWidget>
#include "mrapi.h"

namespace Ui {
class Pid;
}

class PIDSHARED_EXPORT Pid : public QWidget
{
    Q_OBJECT

public:


public:
    Pid(QWidget *parent = 0);
    ~Pid();

public slots:
    void pidInit(int ID);

private:
    void showSEVPID();
    void showMPID();
    void showLPID();
    void showMaxLimit();

private slots:
    void on_POS_PSpinBox_editingFinished();
    void on_POS_ISpinBox_editingFinished();
    void on_POS_DSpinBox_editingFinished();
    void on_POS_DSSpinBox_editingFinished();
    void on_SPD_PSpinBox_editingFinished();
    void on_SPD_ISpinBox_editingFinished();
    void on_SPD_DSpinBox_editingFinished();
    void on_SPD_DSSpinBox_editingFinished();
    void on_CUR_PSpinBox_editingFinished();
    void on_CUR_ISpinBox_editingFinished();
    void on_CUR_DSpinBox_editingFinished();
    void on_adjustGroupComboBox_currentIndexChanged(int index);
    void on_maxSpdLineEdit_editingFinished();
    void on_maxAccLineEdit_editingFinished();
    void on_maxCurLineEdit_editingFinished();
    void on_minPosLLineEdit_editingFinished();
    void on_minPosHLineEdit_editingFinished();
    void on_maxPosLLineEdit_editingFinished();
    void on_maxPosHLineEdit_editingFinished();

private:
    Ui::Pid *uiPid;
    JOINT_HANDLE joint;
};


#endif // PID_H
