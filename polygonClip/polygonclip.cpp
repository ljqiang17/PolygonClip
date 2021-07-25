#include "polygonclip.h"
#include "ui_polygonclip.h"
#include <QPainter>

polygonClip::polygonClip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::polygonClip)
{
    ui->setupUi(this);

    //裁剪区域的边界
    xl = 150;
    yl = 150;
    xr = 450;
    yr = 450;

    //设置主窗口界面
    setWindowTitle("Sutherland-Hodgman");
    setAutoFillBackground(true);
    setFixedSize(600, 600);
    setFocusPolicy(Qt::StrongFocus);
    Pix = QPixmap(560, 560);
    Pix.fill(Qt::transparent);

    //自定义颜色，红色表示原多边形的颜色，绿色代表裁剪后的颜色
    lineColor = qRgb(255, 0, 0);
    clipColor = qRgb(0, 255, 0);

    //设置SH按钮
    SH = new QPushButton(this);
    SH->setText("Sutherland-Hodgman ");
    SH->adjustSize();
    SH->move(10, 0);
    connect(SH, &QPushButton::pressed, this, &polygonClip::sh); //将SH按钮与sh函数（Sutherland-Hodgman算法）连接

    //设置DONE按钮，用于完成多边形的绘制
    DONE = new QToolButton(this);
    DONE->setText("DONE");
    DONE->adjustSize();
    DONE->setCheckable(true);
    DONE->move(50 + SH->width(), 0);

}

void polygonClip::paintEvent(QPaintEvent *event) {//重写paintevent函数，用于绘制裁剪区域
    //设置画笔
    QPainter myPainter(this);
    QPen myPen(Qt::black);
    myPen.setWidth(2);
    myPainter.setPen(myPen);

    //绘制裁剪区域
    myPainter.drawRect(150, 150, 300, 300);
    myPainter.drawPixmap(0, 0, Pix);
}

void polygonClip::mousePressEvent(QMouseEvent *event) { //重写mousepressevent函数，用于自定义绘制多边形
    //设置画笔
    QPainter myPainter(&Pix);
    QPen myPen(lineColor);
    myPen.setWidth(3);
    myPainter.setPen(myPen);
    myPainter.setRenderHint(QPainter::Antialiasing, true);

    if(event->button() == Qt::LeftButton) {
        point[pointNum].setX(event->x());
        point[pointNum].setY(event->y());
        if(DONE->isChecked()) { //当按下DONE按钮时，此时的鼠标点击事件为完成多边形的最后一条边的绘制，即在最后一个顶点和第一个顶点之间绘制一条直线
            //myPainter.drawLine(x0, y0, point[0].x(), point[0].y());
            myPainter.drawLine(point[pointNum-1].x(), point[pointNum-1].y(), point[0].x(), point[0].y());
        } else { //没有按下DONE按钮
            if(pointNum != 0) {
                myPainter.drawLine(x0, y0, event->x(), event->y());
            }

            x0 = event->x();
            y0 = event->y();
            pointNum++;

        }
//        if(pointNum != 0) {
//            myPainter.drawLine(x0, y0, event->x(), event->y());
//        }

//        x0 = event->x();
//        y0 = event->y();
//        pointNum++;
    }
    update();
}



void polygonClip::sh() { //Sutherland-Hodgma算法
    //设置画笔
    QPainter myPainter(&Pix);
    QPen myPen(clipColor);
    myPen.setWidth(3);
    myPainter.setPen(myPen);

    //分别对裁剪区域的四条边进行裁剪
    clipEdge(1);
    clipEdge(2);
    clipEdge(3);
    clipEdge(4);
    //对裁剪后得到的顶点，重新绘制多边形，得到裁剪后的多边形
    for(int i = 0; i < pointNum; i++) {
        myPainter.drawLine(point[i], point[(i + 1) % pointNum]);
    }
    update();
}

void polygonClip::clipEdge(int edge) { //按边进行裁剪
    index = 0;
    bool isIn_p1, isIn_p2;
    for(int i = 0; i < pointNum; i++) {
        isIn_p1 = isIn(edge, point[i]);
        isIn_p2 = isIn(edge, point[(i+1) % pointNum]);
        if(isIn_p1 && isIn_p2) {
            result[index++] = point[(i+1) % pointNum];
        } else if(isIn_p1) {
            result[index++] = intersect(edge, point[i], point[(i+1) % pointNum]);
        } else if(isIn_p2) {
            result[index++] = intersect(edge, point[i], point[(i+1) % pointNum]);
            result[index++] = point[(i+1) % pointNum];
        }

    }
    //更新顶点数组（顶点队列）
    pointNum = index;
    for(int i = 0; i < pointNum; i++)
        point[i] = result[i];
}

QPoint polygonClip::intersect(int edge, QPoint p1, QPoint p2) { //线段和边进行求交点
    QPoint p;
    if(edge == 1) {
        p.setX(xl);
        p.setY((int) (p1.y() - (float)(p1.y() - p2.y()) * (p1.x() - xl) / (p1.x() - p2.x())));
    } else if(edge == 3) {
        p.setX(xr);
        p.setY((int)(p1.y() - (float)(p1.y() - p2.y()) * (p1.x() - xr) / (p1.x() - p2.x())));
    } else if(edge == 2) {
        p.setY(yl);
        p.setX((int)(p1.x() - (float)(p1.x() - p2.x()) * (p1.y() - yl) / (p1.y() - p2.y())));
    } else if(edge == 4) {
        p.setY(yr);
        p.setX((int)(p1.x() - (float)(p1.x() - p2.x()) * (p1.y() - yr) / (p1.y() - p2.y())));
    }
    return p;

}

bool polygonClip::isIn(int edge, QPoint p) { //判断边是否在裁剪区域内
    if((edge == 1 && p.x() < xl) || (edge == 3 && p.x() > xr) || (edge == 2 && p.y() < yl) || (edge == 4 && p.y() > yr))
        return false;
    return true;
}



polygonClip::~polygonClip()
{
    delete ui;
}
