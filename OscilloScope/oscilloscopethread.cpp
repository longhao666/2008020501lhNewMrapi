#include <QDebug>
#include <QDateTime>
#include <vector>
#include "oscilloscopethread.h"
#include "oscilloscope.h"

using std::vector;



OscilloScopeThread::OscilloScopeThread(void *t, QObject *parent) :
    QObject(parent)
{
    view = t;
    //
    paintArea = new PaintArea();
    for (vector<ShowItem>::iterator iItem = paintArea->showItems.begin(); iItem != paintArea->showItems.end(); ++iItem) {
        iItem._Ptr->sq.MaxLength = 700; // grid一格100有7格
    }
    for (unsigned int i = 0; i < paintArea->showItems.size(); i++) {
        paintArea->showItems[i].sq.FillZero();
    }
    //
    this->timerOfGetData = new QTimer(this);
    timerOfGetData->setTimerType(Qt::PreciseTimer);
    this->connect( timerOfGetData,
                   SIGNAL(timeout()),
                   this,
                   SLOT(getData()) ); // slotTimeOscilloScopeDone
    timerOfGetData->start(GET_VALUE_INTEVAL);
    //
    this->timerOfShowData = new QTimer(this);
    connect( timerOfShowData,
             SIGNAL(timeout()),
             this,
             SLOT(showData()) ); // updatePlot
    timerOfShowData->start(UPDATE_SHOW_INTEVAL);
}

OscilloScopeThread::~OscilloScopeThread()
{

}

void OscilloScopeThread::changeTgPOS()
{
    if (paintArea->showItems[2].IsCheck == true) { // showItems[2] is tgPOS
        paintArea->showItems[2].IsCheck = false;
        paintArea->Mask &= ~MASK_TAGPOS;
    } else {
        paintArea->showItems[2].IsCheck = true;
        paintArea->Mask |= MASK_TAGPOS;
        paintArea->showItems[2].sq.FillZero();
    }
    setMask();
}

void OscilloScopeThread::changeTgSPD()
{
    if (paintArea->showItems[1].IsCheck == true) { // showItems[1] is tgSPD
        paintArea->showItems[1].IsCheck = false;
        paintArea->Mask &= ~MASK_TAGSPD;
    } else {
        paintArea->showItems[1].IsCheck = true;
        paintArea->Mask |= MASK_TAGSPD;
        paintArea->showItems[1].sq.FillZero();
    }
    setMask();
}

void OscilloScopeThread::changeTgCUR()
{
    if (paintArea->showItems[0].IsCheck == true) { // showItems[0] is tgCUR
        paintArea->showItems[0].IsCheck = false;
        paintArea->Mask &= ~MASK_TAGCUR;
    } else {
        paintArea->showItems[0].IsCheck = true;
        paintArea->Mask |= MASK_TAGCUR;
        paintArea->showItems[0].sq.FillZero();
    }
    setMask();
}

void OscilloScopeThread::changeRlPOS()
{
    if (paintArea->showItems[5].IsCheck == true) { // showItems[5] is rlPOS
        paintArea->showItems[5].IsCheck = false;
        paintArea->Mask &= ~MASK_MEAPOS;
    } else {
        paintArea->showItems[5].IsCheck = true;
        paintArea->Mask |= MASK_MEAPOS;
        paintArea->showItems[5].sq.FillZero();
    }
    setMask();
}

void OscilloScopeThread::changeRlSPD()
{
    if (paintArea->showItems[4].IsCheck == true) { // showItems[4] is rlSPD
        paintArea->showItems[4].IsCheck = false;
        paintArea->Mask &= ~MASK_MEASPD;
    } else {
        paintArea->showItems[4].IsCheck = true;
        paintArea->Mask |= MASK_MEASPD;
        paintArea->showItems[4].sq.FillZero();
    }
    setMask();
}

void OscilloScopeThread::changeRlCUR()
{
    if (paintArea->showItems[3].IsCheck == true) { // showItems[3] is rlCUR
        paintArea->showItems[3].IsCheck = false;
        paintArea->Mask &= ~MASK_MEACUR;
    } else {
        paintArea->showItems[3].IsCheck = true;
        paintArea->Mask |= MASK_MEACUR;
        paintArea->showItems[3].sq.FillZero();
    }
    setMask();
}

void OscilloScopeThread::setMask()
{
    // 向下位机请求数据
//    uint8_t data[2] = {0,0};
//    data[1] = (uint8_t)( (paintArea->Mask & 0xff00) >> 8 );
//    data[0] = (uint8_t)( paintArea->Mask & 0xff );

    uint16_t data16 = paintArea->Mask;
//    qDebug() << data16 << "dfdfd44444444444444444";
    uint8_t data_L = 0;
    uint8_t data_H = 0;
    data_L = (uint8_t)(data16 & 0xff);
    data_H = (uint8_t)(data16 >> 8);
//    qDebug() << data_L << data_H << "dfdf,,,,,,,,,,,,,,,,,,";
    OscilloScope * JT = static_cast<OscilloScope *>(view);
//    JT->can1->controller.SendMsg( JT->jointBeingUsed->ID,
//                                  CMDTYPE_WR_NR,
//                                  SCP_MASK,
//                                  data,
//                                  2 );
    jointSetScpMask(JT->joint, data16, 100, NULL);
//    JT->can1->controller.SendMsg( JT->jointBeingUsed->ID,
//                                  CMDTYPE_RD,
//                                  SCP_MASK,
//                                  NULL,
//                                  0x02 );
    jointGetSCP_MASK(JT->joint, &data16, 100, NULL);
//    JT->can1->controller.delayMs(5);
}

void OscilloScopeThread::getData()
{
    OscilloScope * JT = static_cast<OscilloScope *>(view);

    if (paintArea->showItems.size() != 6) {
        return;
    }
    if (JT->joint == NULL) {
        return;
    }
//    vector<uint16_t> addrValue;
//    for (unsigned int i = 0; i < paintArea->showItems.size(); i++) {
//        uint16_t data_L = 0;
//        uint16_t data_H = 0;
//        jointGetSCP_MASK_Addr_Value(JT->joint, &data_L, paintArea->showItems[i].Item, 10, NULL);
//        jointGetSCP_MASK_Addr_Value(JT->joint, &data_H, paintArea->showItems[i].Item + 1, 10, NULL);
//        addrValue.push_back(data_L);
//        addrValue.push_back(data_H);
//    }
//    qDebug() << QDateTime::currentDateTime().toString("hh:mm:ss:zzz");

    // 示波器绘制曲线使能开启
    if (paintArea->EnableScope) {
        // 示波器显示曲线用的计数量
        static int gatherCount = 0;
        // 间隔计数会从1开始判断
        ++gatherCount;
        // 按照Interval限定的间隔去执行
        if (gatherCount >= paintArea->Interval) {
            // 间隔计数清零
            gatherCount = 0;
            // 分别处理每个显示项
            // 显示项的显示队列不为0才向队列追加一个新值，该32位有符号值由2个16位有符号数组合而成
            for (unsigned int i = 0; i < paintArea->showItems.size(); i++) {
                if (paintArea->showItems[i].sq.MaxLength != 0 && paintArea->showItems[i].IsCheck) {
//                    uint16_t data_L = 0;
//                    uint16_t data_H = 0;
//                    data_L = addrValue[i];
//                    data_H = addrValue[i+1];
                    uint16_t data_L = 0;
                    uint16_t data_H = 0;
                    jointGetSCP_MASK_Addr_Value(JT->joint, &data_L, paintArea->showItems[i].Item, 100, NULL);
                    jointGetSCP_MASK_Addr_Value(JT->joint, &data_H, paintArea->showItems[i].Item + 1, 100, NULL);
//                    data_L = jointGetmastValue(JT->joint, &data_L, paintArea->showItems[i].Item, 100, NULL);
//                    data_H = jointGetmastValue(JT->joint, &data_H, paintArea->showItems[i].Item + 1, 100, NULL);
                    if(data_L == 0 || data_H == 0) {
                        continue;
                    }
                    double temp = data_L + (data_H * 65536);
                    qDebug() << paintArea->showItems[i].Item << paintArea->showItems[i].Item + 1  << "-==================------------";
                    qDebug() << data_L << data_H << temp << "-vff-----------------";

                    switch (paintArea->showItems[i].Item) {
                    case SCP_TAGCUR_L://(showItems[0].Item)://TAG_CURRENT_L:
                    case SCP_MEACUR_L://showItems[3].Item://SYS_CURRENT_L://若曲线是电流
                        break;
                    case SCP_TAGSPD_L://showItems[1].Item://TAG_SPEED_L:
                    case SCP_MEASPD_L: {//showItems[4].Item://SYS_SPEED_L://若曲线是速度
//                        cout << temp << endl;
                        temp *= 60; // rpm
                        temp /= 65536; // rpm

//
                        uint16_t data16 = 0;
                        jointGetSYS_REDU_RATIO(JT->joint, &data16, 50, NULL);
//                        qDebug("fdfd%d",data16);
                        temp /= data16;
                        break;
                    }
                    case SCP_TAGPOS_L://showItems[2].Item://TAG_POSITION_L:
                    case SCP_MEAPOS_L://showItems[5].Item://SYS_POSITION_L://若曲线是位置
                        temp = temp * 360 / 65536; // degree（会在paintArea里进行转换显示）
//                        temp = data_L; // 位置要去掉圈数，只显示绝对编码器的数值 2017-3-28
                        break;
                    }
                    //向队尾追加值
                    paintArea->showItems[i].sq.Append(temp);
                }
            }
        }
    }
}

void OscilloScopeThread::showData()
{
    OscilloScope * JT = static_cast<OscilloScope *>(view);
    //分别处理每条要测量的曲线
    for ( unsigned int i = 0; i < paintArea->showItems.size(); i++ ) {
        QPolygonF points;
        //若队列非空并且勾选显示
        if (!(paintArea->showItems[i].sq.IsEmpty()) && paintArea->showItems[i].IsCheck) {
            for (int j = 0; j < paintArea->showItems[i].sq.Count(); j++) {//分别处理每一坐标对
                double verticalValue1 = paintArea->showItems[i].sq.GetValue(j);
                points.append(QPointF(j, verticalValue1));
            }
        }
        switch (i) {
            case 0:JT->curveTgCUR->setSamples( points );break;
            case 1:JT->curveTgSPD->setSamples( points );break;
            case 2:JT->curveTgPOS->setSamples( points );break;
            case 3:JT->curveRlCUR->setSamples( points );break;
            case 4:JT->curveRlSPD->setSamples( points );break;
            case 5:JT->curveRlPOS->setSamples( points );break;
        }
    }
//    JT->ui->plot->replot();
//    JT->ui->plotSPD->replot();
//    JT->ui->plotPOS->replot();
}
