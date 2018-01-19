#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mrapi.h"

class Bottom;
class Pid;
class Move;
class SetAndHealth;
class OscilloScope;



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    JOINT_HANDLE joint1;

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void widgetAllReady();

private:
    void widgetInit();

private:
    Ui::Widget *ui;
    Bottom *bottom;
    SetAndHealth *setAndHealth;
    Pid *pid;
    Move *move;
    OscilloScope *oscilloScope;
};

#endif // WIDGET_H
