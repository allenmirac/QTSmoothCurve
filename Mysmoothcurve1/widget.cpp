#include "widget.h"
#include "ui_widget.h"
#include "smoothcurve.h"
#include "qpainter.h"
#include "qdatetime.h"
#include "qdebug.h"

#define TIMEMS QTime::currentTime().toString("hh:mm:ss zzz")

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化随机数种子
    srand(QDateTime::currentDateTime().toMSecsSinceEpoch());

    //随机生成曲线上的点
    int x = -300;
    while (x < 300) {
        datas << QPointF(x, rand() % 300 - 100);
        x += qMin(rand() % 30 + 5, 300);
    }

    //正常曲线
    pathNormal.moveTo(datas.at(0));
    for (int i = 0; i < datas.size(); ++i) {
        pathNormal.lineTo(datas.at(i));
    }

    //平滑曲线1
    pathSmooth1 = SmoothCurve::createSmoothCurve1(datas);

    //平滑曲线2
    pathSmooth2 = SmoothCurve::createSmoothCurve2(datas);

    ui->show->setChecked(true);
    ui->rbtnNormal->setChecked(true);
    connect(ui->show, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->rbtnNormal, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->rbtnSmooth1, SIGNAL(clicked(bool)), this, SLOT(update()));
    connect(ui->rbtnSmooth2, SIGNAL(clicked(bool)), this, SLOT(update()));

}


Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);//设置渲染提示 化妆品
    // Antialiasing 抗锯齿
    // Text Antialiasing 文本抗锯齿
    // High Quality Antialiasing 高品质抗锯齿
    painter.translate(width()/2, height()/2);//将坐标系原点平移
    painter.scale(1, -1);// 比例尺，将坐标的x，y缩放，这里将y坐标反向
    //坐标系
    painter.setPen(QColor(180, 120, 120));
    painter.drawLine(-250, 0, 250, 0);
    painter.drawLine(0, 150, 0, -150);

    painter.setPen(QPen(QColor(100, 10, 150), 2));
    if(ui->rbtnSmooth1->isChecked()) {
        painter.drawPath(pathSmooth1);
    }else if(ui->rbtnSmooth2->isChecked()) {
        painter.drawPath(pathSmooth2);
    }else {
        painter.drawPath(pathNormal);
    }

    if(ui->show->isChecked()) {
        painter.setPen(Qt::black);
        painter.setBrush(Qt::blue);
        foreach(QPointF point, datas){
            painter.drawEllipse(point, 2, 2);
        }
    }
}
