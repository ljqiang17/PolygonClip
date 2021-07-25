#ifndef POLYGONCLIP_H
#define POLYGONCLIP_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QToolButton>

namespace Ui {
class polygonClip;
}

class polygonClip : public QWidget
{
    Q_OBJECT

public:
    explicit polygonClip(QWidget *parent = nullptr);
    ~polygonClip();

private:
    QRgb lineColor;
    QRgb clipColor;
    int xl, yl, xr, yr;
    QPushButton *SH;
    QToolButton *DONE;
    QPoint point[100];
    QPoint result[100];
    int pointNum = 0;
    int index;
    int x0, y0;
    QPixmap Pix;
    bool flipflop = true;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void sh();
    void clipEdge(int edge);
    QPoint intersect(int edge, QPoint p1, QPoint p2);
    bool isIn(int edge, QPoint p);


private:
    Ui::polygonClip *ui;
};

#endif // POLYGONCLIP_H
