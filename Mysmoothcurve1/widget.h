#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QPointF>
#include <QPainterPath>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Widget *ui;

    QVector<QPointF> datas;     //曲线上的点
    QPainterPath pathNormal;    //正常曲线
    QPainterPath pathSmooth1;   //平滑曲线1
    QPainterPath pathSmooth2;   //平滑曲线2
};

#endif // WIDGET_H
