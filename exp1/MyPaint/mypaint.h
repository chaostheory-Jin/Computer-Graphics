#ifndef MYPAINT_H
#define MYPAINT_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QColor>
#include <qpen.h>
#include <QFileDialog>
#include <QDebug>
#include "polygon.h"
#include <cmath>
class MyPaint : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyPaint(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
    void mousePressEvent(QMouseEvent *);//重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);//重写鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);//重写鼠标移动事件
    void contextMenuEvent(QContextMenuEvent *);//重写菜单事件
    void keyPressEvent(QKeyEvent *e); //重写按键事件


public:
    bool lineClip(QPoint& p0, QPoint& p1, QRect rt);
    char getCSCode(int x, int y, QRect rt);
private:
    int _lpress;//左键按下标志
    int _drag;//拖拽标志
    int _drawType;//描绘类型
    QColor _colortype=Qt::black;//线型颜色
    int _colorflag;//颜色启用
    int _lineType=1;//线宽控制
    int _lineflag;//线宽启用
    Qt::PenStyle _penstyle=Qt::CustomDashLine;
    QMenu *_Rmenu;//右键菜单
    int _openflag;//打开图片
    QPixmap _pixmap;//画布图片
    int cx=0,cy=0;
    QPoint seed;

public:
    QVector<QColor> _color;
    QVector<int> _width;
    QVector<QPoint> _point;
    QVector<QPoint> _pointf;//辅助点
    QVector<QRect> _ellipse;//椭圆集合
    QVector<QRect> _rects;//矩形集合
    QVector<QRect>  _line;//dda直线集合
    QVector<QRect>  _line1;//中点直线集合
    QVector<QRect>  _line2;//bresenham直线集合
    QVector<int>  _shape;//图形类型集合，用于撤回功能
    QPoint _begin;//鼠标按下坐标、用于最后一个图形移动
    QPoint pointf;
    QPoint center;
    QVector<QRect> propotionline;
    QLineF beginline;
    QLineF endline;

signals:

public slots:
    void SavePic();//保存图片
    void Ellipses();//画椭圆
    void Line();//画直线
    void Line1();
    void Line2();
    void Rects();//矩形
    void Polygon();//多边形
    void Seed();//扫描线
    void OpenPic();//打开图片
    void LineType();
    void LineType5();
    void LineType7();
    void ColorType();
    void ColorType1();
    void ColorType2();
    void Cut();
    void Move();
    void Setcenter();
    void Scale();
    void Rotate();
    void Bezier();

private:
    enum PointIndices {
        StartPoint = 0,
        ControlPoint1 = 1,
        ControlPoint2 = 2,
        EndPoint = 3
    };

   //Functions
private:
    qreal distance(QPointF a, QPointF b) {
        QPointF diff = a - b;
        return sqrt(diff.x()*diff.x() + diff.y()*diff.y());
    }

private:
    const int NUM_POINTS = 4;
    const qreal POINT_RADIUS = 4.0;

    QPointF         m_points[4];
    QPen            m_pens[4];
    QBrush          m_brushes[4];
    Qt::GlobalColor m_colors[4];

    QPen        m_curvePen;

    bool        m_dragging;
    int         m_selectedPoint;
};

#endif // MYPAINT_H
