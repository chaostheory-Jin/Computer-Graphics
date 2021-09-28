#include "scanline.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <QPainter>
#include <QtDebug>

Polygon::Polygon()
{
    yMin = 2e9;
    yMax = -2e9;
    pt.clear();
    et.clear();
    aet.clear();
}

Polygon::~Polygon()
{
    yMin = 2e9;
    yMax = -2e9;
    pt.clear();
    et.clear();
    aet.clear();
}

void Polygon::addPoint(int x, int y)
{
    yMin = qMin(yMin, y);
    yMax = qMax(yMax, y);
    pt.push_back(Point(x, y));
}

void Polygon::addEdge(int x0, int y0, int x1, int y1)
{
    Edge tmp;
    if(y0 < y1)
    {
        tmp.ymax = y1-1;
        tmp.x = x0;
        tmp.k = (x1-x0)*1.0/(y1-y0);
        et[y0-yMin].push_back(tmp);
    }
    else if(y0 >= y1)
    {
        tmp.ymax = y0-1;
        tmp.x = x1;
        tmp.k = (x1-x0)*1.0/(y1-y0);
        et[y1-yMin].push_back(tmp);
    }
}

bool operator<(Edge A, Edge B)
{
    if(abs(A.x - B.x) <= 1e-6)
        return A.k < B.k;
    else
        return A.x < B.x;
}

void Polygon::paint(QPainter *p)
{
    int i, j, l;
    et.resize(yMax - yMin + 1);
    for(i = 0;i < pt.size() - 1;i++)
    {
        this->addEdge(pt[i].x, pt[i].y, pt[i+1].x, pt[i+1].y);
    }
    this->addEdge(pt[i].x, pt[i].y, pt[0].x, pt[0].y);
    for(i = 0;i < yMax - yMin + 1;i++)
    {
        for(j = 0;j < et[i].size();j++)
        {
            aet.push_back(et[i][j]);
        }
        sort(aet.begin(), aet.end());
        for(j = 0;j+1 < aet.size();j+=2)
        {
            int ll = (aet[j].x - (int)aet[j].x >= 0.5?(int)aet[j].x+1:(int)aet[j].x);
            int rr = (aet[j+1].x - (int)aet[j+1].x >= 0.5?(int)aet[j+1].x+1:(int)aet[j+1].x);
            for(l = ll;l <= rr;l++)
            {
                p->fillRect(l, i+yMin, 1, 1, Qt::blue);
            }
        }
        std::vector<Edge>::iterator it;
        for(it = aet.begin();it != aet.end();)
        {
            if(it->ymax <= i+yMin)
            {
                aet.erase(it);
            }
            else
            {
                it++;
            }

        }
        for(it = aet.begin();it != aet.end();it++)
        {
            it->x = it->x + it->k;
        }
    }
    for(i = 0;i < pt.size();i++)
    {
        p->fillRect(pt[i].x, pt[i].y, 1, 1, Qt::blue);
    }
}
