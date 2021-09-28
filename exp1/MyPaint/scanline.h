#ifndef SCANLINE_H
#define SCANLINE_H

#include <vector>
#include <QPainter>

class Point
{
public:
    int x, y;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

class Edge
{
public:
    int ymax;
    double x, k;
};

class Polygon
{
public:
    Polygon();
    ~Polygon();
    void addPoint(int x, int y);
    void paint(QPainter *p);

private:
    int yMin, yMax;
    // 顶点表
    std::vector<Point> pt;
    // 边表
    std::vector<std::vector<Edge> > et;
    // 活动边表
    std::vector<Edge> aet;

    void addEdge(int x0, int y0, int x1, int y1);
};

#endif // SCANLINE_H
