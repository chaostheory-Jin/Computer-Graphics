#include "polygon.h"

polygon::polygon(QVector<QPoint>& points,QPoint seed, QColor color)
    :points(points)
    ,seed(seed)
    ,color(color)
{

}

void polygon::showPolygonInEdgeTable(QPainter* ptr)
{
    if(points.size()<3)
        return;
    int i, j;
    int x0, x1, y, tx;

    int scanLines;//扫描线数量
    int min;//最低扫描线号
    int max;//最高扫描线号

    QVector<QList<edge>> ET;//边表
    QList<edge> AET;//活化边表
    QVector<double> arr;//扫描线与各边交点表

    QPoint p0;//边的起点
    QPoint p1;//边的终点
    QPoint temp;//保存位置变量
    edge* pNode;//边结点指针

    QVector<QList<edge>>::iterator iterET;//边表矢量迭代器
    QList<edge>::iterator iterEdge;//边链表迭代器

    min = getMinY();
    max = getMaxY();
    scanLines = max - min;

    //建立边表ET
    ET.resize(scanLines);
    //逐边进行处理，将每一条边的信息插入到ET中
    for(i=0; i<points.size(); i++)
    {
        if(i < points.size()-1)
        {
            p0 = points[i];
            p1 = points[i+1];
        }
        else
        {
            p0 = points[i];
            p1 = points[0];
        }

        if(p0.y()>p1.y())//将p0设为边的起点坐标，y坐标较小
        {
            temp = p0;
            p0 = p1;
            p1 = temp;
        }

        if(p0.y() != p1.y())//非水平边
        {
            pNode = new edge;
            pNode->setX(static_cast<double>(p0.x()));
            pNode->setDx(static_cast<double>(p1.x()-p0.x())/(p1.y()-p0.y()));
            pNode->setYmax(p1.y()-1);//下闭上开
            ET[p0.y()-min].append(*pNode);
        }
    }//所有边都已插入到ET中

    for (i=0; i<scanLines; i++)// 开始扫描，各边依次加入到AET中
    {
        y = i + min;//当前扫描线y坐标
        if(!ET[i].isEmpty())//有边加入AET
        {
            for(iterEdge=ET[i].begin(); iterEdge!=ET[i].end(); iterEdge++)
                AET.append(*iterEdge);
        }
        ET[i].clear();//边结点已取出加入AET，无需保留

        //处理活化边表AET
        if(!AET.isEmpty())//首先删除扫描线以下的边
        {
            for(iterEdge=AET.begin(); iterEdge!=AET.end(); iterEdge++)
            {
                if(iterEdge->getYmax()<y){
                    AET.erase(iterEdge);
                    iterEdge=AET.begin();
           }
            }
        }

        if(!AET.isEmpty())//活化边表非空，求出交点，排序，画线
        {
            for(iterEdge=AET.begin(); iterEdge!=AET.end(); iterEdge++)
            {
                arr.append(iterEdge->getX());//取出所有交点
                iterEdge->setX(iterEdge->getX() + iterEdge->getDx());
            }
            sort(arr.begin(), arr.end());//交点排序
            for(j=0; j<arr.size(); j++)
            {
                if(j%2 == 0)
                {
                    tx = static_cast<int>(arr[j]);// 左边交点向右取整
                    if(arr[j]-tx)
                        x0 = tx + 1;
                    else
                        x0 = tx;
                    x1 = static_cast<int>(arr[j + 1]);// 右边交点向左取整
                }
                ptr->save();
                ptr->setPen(color);
                ptr->drawLine(QPoint(x0, y),QPoint(x1, y));
                ptr->restore();
            }
            arr.clear();
        }
    }//所有扫描线处理完毕
    ET.clear();
}

void polygon::showPolygonInSeed(QPainter* ptr)
{

    if(!isInPolygon(seed) || points.size()<3)
        return;
    //获取多边形最小包围盒
    int minx, maxx, miny, maxy;
    minx = getMinX()-1;
    maxx = getMaxX()+1;
    miny = getMinY()-1;
    maxy = getMaxY()+1;
    if(seed.x()<=minx || seed.x()>=maxx || seed.y()<=miny || seed.y()>=maxy)
        return;
    //设置一个标志矩阵
    int m = maxy - miny;
    int n = maxx - minx;
    bool MF[m][n];
    int i,j;
    for(i=0; i<m; i++)
        for(j=0; j<n; j++)
            MF[i][j] = false;
    //绘制边界，并将边界像素标志置为true
    QPoint p0, p1;
    int temp;
    int vertics = points.size();
    int x, y;
    double tx, ty, dx, dy;
    int k;
    int x0, x1, y0, y1;
    ptr->save();
    ptr->setPen(color);
    ptr->setPen(Qt::green);
    for(k=0; k<vertics; k++)//逐边绘制
    {
        //获取一条边p0p1
        if(k == vertics-1)
        {
            p0 = points[k];
            p1 = points[0];
        }
        else
        {
            p0 = points[k];
            p1 = points[k+1];
        }

        x0 = p0.x();
        y0 = p0.y();
        x1 = p1.x();
        y1 = p1.y();

        if(y0 == y1)//水平边
        {
            y = y0;
            if(x0>x1)
            {
                temp = x0;
                x0 = x1;
                x1 = temp;
            }
            for(x=x0; x<x1; x++)
            {
                ptr->drawPoint(x, y);
                MF[y-miny][x-minx] = true;
            }
        }
        else if(x0 == x1)//垂直边
        {
            x = x0;
            if(y0>y1)
            {
                temp = y0;
                y0 = y1;
                y1 = temp;
            }
            for(y=y0; y<y1; y++)
            {
                ptr->drawPoint(x, y);
                MF[y-miny][x-minx] = true;
            }

        }
        else//非水平和垂直边
        {
            dy = (double)(y1-y0)/(double)(x1-x0);
            dx = 1/dy;

            if(dy>-1 && dy<1)
            {
                if(x0>x1)
                {
                    temp = x0;
                    x0 = x1;
                    x1 = temp;
                    temp = y0;
                    y0 = y1;
                    y1 = temp;
                }
                ty = y0;
                for(x=x0; x<=x1; x++)
                {
                    y = (int)(ty+0.5);
                    ptr->drawPoint(x, y);
                    MF[y-miny][x-minx] = true;
                    ty += dy;
                }
            }
            else
            {
                if(y0>y1)
                {
                    temp = x0;
                    x0 = x1;
                    x1 = temp;
                    temp = y0;
                    y0 = y1;
                    y1 = temp;
                }
                tx = x0;
                for(y=y0; y<=y1; y++)
                {
                    x = (int)(tx+0.5);
                    ptr->drawPoint(x, y);
                    MF[y-miny][x-minx] = true;
                    tx += dx;
                }
            }
        }
    }

    //种子点压栈，压栈像素标志置为true
    QStack<QPoint> stack;
    stack.push(seed);
    MF[seed.y()-miny][seed.x()-minx] = true;
    //当栈不为空时，退栈，绘制像素点
    //对当前退栈元素的左上右下点进行检查，若标志为false，压栈，并将压栈像素标志置为true
    QPoint ps;

    while(!stack.isEmpty())
    {

        ps = stack.pop();
        ptr->drawPoint(ps);
        //Sleep(100);
        p0.setX(ps.x()-1);//左
        p0.setY(ps.y());
        if(!MF[p0.y()-miny][p0.x()-minx])
        {
            stack.push(p0);
            MF[p0.y()-miny][p0.x()-minx] = true;
        }

        p0.setX(ps.x()+1);//右
        p0.setY(ps.y());
        if(!MF[p0.y()-miny][p0.x()-minx])
        {
            stack.push(p0);
            MF[p0.y()-miny][p0.x()-minx] = true;
        }

        p0.setX(ps.x());//下
        p0.setY(ps.y()-1);
        if(!MF[p0.y()-miny][p0.x()-minx])
        {
            stack.push(p0);
            MF[p0.y()-miny][p0.x()-minx] = true;
        }

        p0.setX(ps.x());//上
        p0.setY(ps.y()+1);
        if(!MF[p0.y()-miny][p0.x()-minx])
        {
            stack.push(p0);
            MF[p0.y()-miny][p0.x()-minx] = true;
        }

    }

    ptr->restore();
}


int polygon::getMaxX()
{
    int max = 0;
    QVector<QPoint>::iterator iter;
    for (iter=points.begin(); iter!=points.end(); iter++)
        if (iter->x() > max)
            max = iter->x();
    return max;
}

int polygon::getMinX()
{
    int min = getMaxX();
    QVector<QPoint>::iterator iter;
    for (iter=points.begin(); iter!=points.end(); iter++)
        if (iter->x() < min)
            min = iter->x();
    return min;
}

int polygon::getMaxY()
{
    int max = 0;
    QVector<QPoint>::iterator iter;
    for (iter=points.begin(); iter!=points.end(); iter++)
        if (iter->y() > max)
            max = iter->y();
    return max;
}

int polygon::getMinY()
{
    int min = getMaxY();
    QVector<QPoint>::iterator iterPos;
    for (iterPos=points.begin(); iterPos!=points.end(); iterPos++)
        if (iterPos->y() < min)
            min = iterPos->y();
    return min;
}

bool polygon::isInPolygon(QPoint p)
{
    int i, j;
    bool c = false;

    for (i=0, j=points.size()-1; i<points.size(); j=i++)
    {
        if(((points[i].y()>seed.y()) != (points[j].y()>seed.y())) &&
            (seed.x()<(points[j].x()-points[i].x()) *
             (seed.y()-points[i].y()) / (points[j].y()-points[i].y()) + points[i].x()))
        c = !c;
    }
    return c;
}

void polygon::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
