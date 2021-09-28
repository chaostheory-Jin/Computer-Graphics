#ifndef POLYGON_H
#define POLYGON_H
#include <QPoint>
#include <QVector>
#include <QList>
#include <QColor>
#include <QPainter>
#include <algorithm>
#include <QStack>
#include <QEventLoop>
#include <QTimer>
#include <QThread>
#include <QTime>
#include <QCoreApplication>
using namespace std;
#include "edge.h"

class polygon
{
private:
    QVector<QPoint> points;
    QColor color;
    QPoint seed;
    int getMaxX();
    int getMinX();
    int getMaxY();
    int getMinY();
    void Sleep(int msec);

public:
    polygon(QVector<QPoint>& points,QPoint seed, QColor color);
    void showPolygonInEdgeTable(QPainter* ptr);//有序边表算法
    void showPolygonInSeed(QPainter* ptr);//边标志算法
    bool isInPolygon(QPoint p);
};

#endif // POLYGON_H
