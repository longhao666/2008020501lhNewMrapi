#ifndef BOTTOM_H
#define BOTTOM_H

#include "bottom_global.h"
#include "mrapi.h"
#include <QWidget>


class QTimer;

namespace Ui {
class Bottom;
}

class BOTTOMSHARED_EXPORT Bottom : public QWidget
{
    Q_OBJECT
public:

public:
    Bottom(QWidget *parent = 0);
    ~Bottom();

public slots:
    void waitingForWidgetReady();
    void dealIDChanged(int newID);

signals:
    void cmbIDChanged(int ID);


private:
    void updateEnableDriver();
    void updateWorkModePushButton();
    void updateConnected();
    void updateIfError();

private slots:
    void on_btnUpdateID_clicked();
    void on_enableDriverPushButton_clicked();
    void on_btnFlash_clicked();
    void on_btnLoad_clicked();
    void on_btnSave_clicked();
    void on_cmbID_currentIndexChanged(int index);
    void slotTimerBottomDone();


private:
    Ui::Bottom *uiBottom;
    JOINT_HANDLE joint;
    bool isCANInitialSucceed;
    QTimer *timerBottom;
};

#endif // BOTTOM_H
