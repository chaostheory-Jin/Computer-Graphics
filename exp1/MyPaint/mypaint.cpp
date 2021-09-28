#include "mypaint.h"
#include<QPushButton>
#include<QWidget>
#include<math.h>
MyPaint::MyPaint(QWidget *parent) :
    QMainWindow(parent)
  , m_curvePen(Qt::black)
  , m_dragging(false)
{
    m_curvePen.setWidth(2);

    m_colors[0] = Qt::green;
    m_colors[1] = Qt::red;
    m_colors[2] = Qt::blue;
    m_colors[3] = Qt::green;

    for (int i = 0; i < NUM_POINTS; i++) {
        m_pens[i]    = QPen(m_colors[i]);
        m_brushes[i] = QBrush(m_colors[i]);
    }

    m_points[StartPoint]    = QPointF(200, height() - 20);
    m_points[ControlPoint1] = QPointF(width() - 20, height() - 20);
    m_points[ControlPoint2] = QPointF(200, 60);
    m_points[EndPoint]      = QPointF(width() - 20, 60);

    _lpress = false;//初始鼠标左键未按下
    _drawType = 0;//初始为什么都不画
    _drag = 0;//默认非拖拽模式
    _begin = pos();//拖拽的参考坐标，方便计算位移
    _openflag = 0;//初始不打开图片
    this->setGeometry(250,200,960,720);//设置窗体大小、位置
    setMouseTracking(true);//开启鼠标实时追踪，监听鼠标移动事件，默认只有按下时才监听
    //设置背景颜色
    this->setStyleSheet("background-color:white;");

    //创建工具栏
    QToolBar *tbar = addToolBar(tr("工具栏"));
    tbar->setMovable(false);//工具栏不可移动
    tbar->setIconSize(QSize(20, 20));//设置动作图标的尺寸
    tbar->setStyleSheet("background-color:rgb(155,155,155)");//背景色

    _Rmenu = new QMenu(this);//创建右键菜单
    _Rmenu->addAction(tr("保存  \tCtrl+S"), this, SLOT(SavePic()));//添加菜单动作
    _Rmenu->addAction(tr("退出  \tALT+F4"), this, SLOT(close()));//添加菜单动作
    _Rmenu->setStyleSheet("background-color:rgb(199,237,204)");//设置背景色

    QAction *openAction = new QAction(tr("&打开"), this);//打开动作
    openAction->setIcon(QIcon(":/png/images/open.png"));//图标
    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));//热键
    tbar->addAction(openAction);//添加到工具栏

    QAction *saveAction = new QAction(tr("&保存"), this);//保存动作
    saveAction->setIcon(QIcon(":/png/images/save.png"));//图标
    saveAction->setShortcut(QKeySequence(tr("Ctrl+S")));//热键
    tbar->addAction(saveAction);//添加到工具栏

    QAction *lineAction = new QAction(tr("&DDA"), this);//直线动作
    //lineAction->setIcon(QIcon(":/png/images/dda.png"));//图标
    lineAction->setText("DDA");
    lineAction->setShortcut(QKeySequence(tr("Ctrl+L")));//热键
    tbar->addAction(lineAction);//添加到工具栏

    QAction *lineAction1 = new QAction(tr("&中点"), this);//直线动作
    //lineAction1->setIcon(QIcon(":/png/images/中点.png"));//图标
    //lineAction->setText("中点");
    lineAction1->setShortcut(QKeySequence(tr("Ctrl+L")));//热键
    tbar->addAction(lineAction1);//添加到工具栏

    QAction *lineAction2 = new QAction(tr("&Bresenham"), this);//直线动作
    //lineAction2->setIcon(QIcon(":/png/images/bresenham.png"));//图标
    //lineAction->setText("Bresenham");
    lineAction2->setShortcut(QKeySequence(tr("Ctrl+L")));//热键
    tbar->addAction(lineAction2);//添加到工具栏


    QAction *ellipseAction = new QAction(tr("&圆"), this);//圆动作
    //ellipseAction->setIcon(QIcon(":/png/images/ellipse.png"));//图标
    //lineAction->setText("圆");
    ellipseAction->setShortcut(QKeySequence(tr("Ctrl+E")));//热键
    tbar->addAction(ellipseAction);

    QAction *rectAction = new QAction(tr("&矩形"), this);//矩形动作
    rectAction->setIcon(QIcon(":/png/images/rect.png"));//图标
    rectAction->setShortcut(QKeySequence(tr("Ctrl+R")));//热键
    tbar->addAction(rectAction);

    QAction *typeAction = new QAction(tr("&线宽"), this);//文字动作
    typeAction->setIcon(QIcon(":/png/images/线宽3.png"));//图标
    typeAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(typeAction);

    QAction *type5Action = new QAction(tr("&线宽"), this);//文字动作
    type5Action->setIcon(QIcon(":/png/images/线宽5.png"));//图标
    type5Action->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(type5Action);

    QAction *type7Action = new QAction(tr("&线宽"), this);//文字动作
    type7Action->setIcon(QIcon(":/png/images/线宽7.png"));//图标
    type7Action->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(type7Action);

    QAction *colorAction = new QAction(tr("&颜色"), this);//文字动作
    colorAction->setIcon(QIcon(":/png/images/红色.png"));//图标
    colorAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(colorAction);

    QAction *color1Action = new QAction(tr("&颜色"), this);//文字动作
    color1Action->setIcon(QIcon(":/png/images/绿色.png"));//图标
    color1Action->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(color1Action);

    QAction *color2Action = new QAction(tr("&颜色"), this);//文字动作
    color2Action->setIcon(QIcon(":/png/images/蓝色.png"));//图标
    color2Action->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(color2Action);

    QAction *polygonAction = new QAction(tr("&扫描转换"), this);//扫描转换
    polygonAction->setIcon(QIcon(":/png/images/蓝色.png"));//图标
    polygonAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(polygonAction);

    QAction *seedAction = new QAction(tr("&种子填充"), this);//种子填充
    seedAction->setIcon(QIcon(":/png/images/蓝色.png"));//图标
    seedAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(seedAction);

    QAction *cutAction = new QAction(tr("裁剪"), this);//种子填充
    //cutAction->setIcon(QIcon(":/png/images/蓝色.png"));//图标
    lineAction->setText("裁剪");
    cutAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(cutAction);

    QAction *moveAction = new QAction(tr("平移"), this);//种子填充
    moveAction->setIcon(QIcon(":/png/images/蓝色.png"));//图标
    moveAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(moveAction);

    QAction *setcenterAction = new QAction(tr("设置中心点"), this);//种子填充
    setcenterAction->setIcon(QIcon(":/png/images/蓝色.png"));//图标
    setcenterAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(setcenterAction);

    QAction *scaleAction = new QAction(tr("缩放"), this);//种子填充
    scaleAction->setIcon(QIcon(":/png/images/蓝色.png"));//图标
    scaleAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(scaleAction);

    QAction *rotateAction = new QAction(tr("旋转"), this);//种子填充
    rotateAction->setIcon(QIcon(":/png/images/蓝色.png"));//图标
    rotateAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(rotateAction);

    QAction *bezierAction = new QAction(tr("贝塞尔"), this);//种子填充
    bezierAction->setIcon(QIcon(":/png/images/rect.png"));//图标
    bezierAction->setShortcut(QKeySequence(tr("Ctrl+T")));//热键
    tbar->addAction(bezierAction);

    //连接信号与槽函数
    connect(ellipseAction, SIGNAL(triggered()), this, SLOT(Ellipses()));
    connect(lineAction, SIGNAL(triggered()), this, SLOT(Line()));
    connect(lineAction1, SIGNAL(triggered()), this, SLOT(Line1()));
    connect(lineAction2, SIGNAL(triggered()), this, SLOT(Line2()));
    connect(rectAction, SIGNAL(triggered()), this, SLOT(Rects()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(SavePic()));
    connect(openAction, SIGNAL(triggered()), this, SLOT(OpenPic()));
    connect(typeAction, SIGNAL(triggered()), this, SLOT(LineType()));
    connect(type5Action, SIGNAL(triggered()), this, SLOT(LineType5()));
    connect(type7Action, SIGNAL(triggered()), this, SLOT(LineType7()));
    connect(colorAction, SIGNAL(triggered()), this, SLOT(ColorType()));
    connect(color1Action, SIGNAL(triggered()), this, SLOT(ColorType1()));
    connect(color2Action, SIGNAL(triggered()), this, SLOT(ColorType2()));
    connect(polygonAction, SIGNAL(triggered()), this, SLOT(Polygon()));
    connect(seedAction, SIGNAL(triggered()), this, SLOT(Seed()));
    connect(cutAction, SIGNAL(triggered()), this, SLOT(Cut()));
    connect(moveAction, SIGNAL(triggered()), this, SLOT(Move()));
    connect(setcenterAction, SIGNAL(triggered()), this, SLOT(Setcenter()));
    connect(scaleAction, SIGNAL(triggered()), this, SLOT(Scale()));
    connect(rotateAction, SIGNAL(triggered()), this, SLOT(Rotate()));
    connect(bezierAction, SIGNAL(triggered()), this, SLOT(Bezier()));

}

void MyPaint::paintEvent(QPaintEvent *)
{
    if(_openflag == 0)//不是打开图片的，每一次新建一个空白的画布
    {
        _pixmap = QPixmap(size());//新建pixmap
        _pixmap.fill(Qt::white);//背景色填充为白色
    }

    QPixmap pix = _pixmap;//以_pixmap作为画布
    QPainter p(&pix);//将_pixmap作为画布
    int i2=0,i3=0,i4=0,i6=0,i7=0,i8=0,i10=0,i13=0;//各种图形的索引

    for(int c = 0;c<_shape.size();++c)//控制用户当前所绘图形总数
    {
        if(_shape.at(c) == 3)//圆
        {
            if(_lineflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            if(_colorflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            //p.drawEllipse(_ellipse.at(i3++));
            double x=(_ellipse.at(i3).topLeft().x()+_ellipse.at(i3).bottomRight().x())/2,
                    y=(_ellipse.at(i3).topLeft().x()+_ellipse.at(i3).bottomRight().x())/2;
            double x1=_ellipse.at(i3).topLeft().x(),y1=_ellipse.at(i3).topLeft().x();
            int a=abs(x-x1),b=abs(y-y1);
            //p.drawEllipse(x,y,a,b);
            float d1,d2;
            x = 0; y = b;
            d1 = b*b +a*a*(-b+0.25);     //d1置初值
            p.drawPoint(x1+x,y1+y);
            p.drawPoint(x1-x,y1+y);
            p.drawPoint(x1+x,y1-y);
            p.drawPoint(x1-x,y1-y);
            while( b*b*(x+1) < a*a*(y-0.5))    //直到上下分界点
            {
                if (d1<0) {d1 +=b*b*(2*x+3); x++;} //取右点,d1增
                else  {d1 +=(b*b*(2*x+3)+a*a*(-2*y+2));
                    x++;  y--;}    //取右下点，d1增
                p.drawPoint(x1+x,y1+y);
                p.drawPoint(x1-x,y1+y);
                p.drawPoint(x1+x,y1-y);
                p.drawPoint(x1-x,y1-y);

            }//上半部分结束
            d2=(b*(x+0.5))*(b*(x+0.5)) +(a*(y-1))*(a*(y-1)) - (a*b)*(a*b);
            //d2置初值，sqr为平方函数
            while(y >0)          //直到x坐标轴
            {
                if(d2<0) {d2 +=b*b*(2*x+2)+a*a*(-2*y+3);
                    x++;  y--;}     //取右下点
                else  {d2 += a*a*(-2*y+3);  y--;}  //取下点
                p.drawPoint(x1+x,y1+y);
                p.drawPoint(x1-x,y1+y);
                p.drawPoint(x1+x,y1-y);
                p.drawPoint(x1-x,y1-y);
            }
            i3++;
        }
        else if(_shape.at(c) == 2)//矩形
        {
            p.drawRect(_rects.at(i2++));

        }
        else if(_shape.at(c) == 4)//直线中点
        {

            if(_lineflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            if(_colorflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            int a, b, d1, d2, d, x, y;
            int dx, dy, num;
            int p2, p1, q, q1;//p,q属于x  p1,q1属于y  决定x，y加1或0
            int x1,y1,x2,y2;
            x1=_line.at(i4).topLeft().x();
            y1=_line.at(i4).topLeft().y();
            x2=_line.at(i4).bottomRight().x();
            y2=_line.at(i4).bottomRight().y();

            x = x1; y =y1;
            a = y1 - y2;//A=-<>y
            b = x2 -x1;
            dx = abs(x1 - x2);
            dy = abs(y1 - y2);

            if (((x2 - x1 >= 0) && (y2 - y1 < 0)) || ((x2 - x1 <= 0) && (y2 - y1 > 0)))//2,4象限
            {
                if ((x2 - x1 <= 0) && y2 - y1 > 0)//从左边开始向右递增
                {
                    a = -a; b = -b;   x = x2; y = y2;
                }
                if (dx >= dy)
                {
                    num = dx;
                    p2 = 1; p1 = 0; q = 1; q1 = -1;
                    d = 2 * a - b; d2 = 2 * a; d1 = 2 * (a - b);
                }
                else {
                    num = dy;
                    p2 = 1; p1 = -1; q = 0; q1 = -1;
                    d = a - 2 * b; d1 = -(2 * b); d2 = 2 * (a - b);
                }
            }
            else {//1,3象限
                if ((x2 - x1 <= 0) && (y2 - y1 < 0))//从左边开始向右递增
                {
                    a = -a; b = -b; x = x2; y = y2;
                }
                if (dx >= dy)//斜率<1
                {
                    num = dx;
                    p2 = 1; p1 = 1; q = 1; q1 = 0;//
                    d = 2 * a + b; d1 = 2 * a; d2 = 2 * (a + b);//d初始值，d1 d大于0加的值
                }
                else {
                    num = dy;
                    p2 = 0; p1 = 1; q = 1; q1 = 1;
                    d = 2 * b + a; d2 = 2 * b; d1 = 2 * (a + b);
                }
            }
            for (int i = 0; i <= num; i++)
            {
                if (d < 0)
                {
                    x += p2; y += p1; d += d2;
                }
                else {
                    x += q; y += q1; d += d1;
                }
                p.drawPoint(x,y);

            }
            i4++;
        }
        else if(_shape.at(c) == 6)//DDA
        {
            if(_lineflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            if(_colorflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            int x1,y1,x2,y2;
            x1=_line1.at(i6).topLeft().x();
            y1=_line1.at(i6).topLeft().y();
            x2=_line1.at(i6).bottomRight().x();
            y2=_line1.at(i6).bottomRight().y();

            float x, y, dx, dy, k, _k;//浮点变量x，y，x增量，y增量，斜率，斜率倒数
            float xm, ym;
            dx =x2 - x1;
            dy =y2 - y1;
            k = dy / dx;
            _k = dx / dy;
            x = x2; xm = x1;
            y = y2; ym = y1;

            //斜率判断
            if (abs(dx) >= abs(dy))//斜率abs小于1
            {
                if (x1 < x2) { x = x1; xm = x2; y = y1; ym = y2; }
                for (; x <= xm; x++)
                {
                    p.drawPoint(x,(int)(y+0.5));
                    y += k;
                }
            }
            else {//斜率大于1，用y每次增加1
                if (y1<=y2) { x = x1; xm = x2; y = y1; ym = y2; }
                for (; y <= ym;y++)
                {
                    p.drawPoint((int)(x+0.5),y);
                    x += _k;
                }
            }
            i6++;
        }
        else if(_shape.at(c) == 7)//bresenham
        {
            if(_lineflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            if(_colorflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            int x1,y1,x2,y2;
            x1=_line2.at(i7).topLeft().x();
            y1=_line2.at(i7).topLeft().y();
            x2=_line2.at(i7).bottomRight().x();
            y2=_line2.at(i7).bottomRight().y();



            int dx = x2 - x1;
            int dy = y2 - y1;
            int ux = ((dx > 0) << 1) - 1;//x的增量方向，取或-1
            int uy = ((dy > 0) << 1) - 1;//y的增量方向，取或-1
            int x = x1, y = y1, eps;//eps为累加误差

            eps = 0;dx = abs(dx); dy = abs(dy);
            if (dx > dy)
            {
                for (x = x1; x != x2; x += ux)
                {
                    p.drawPoint(x,y);
                    eps += dy;
                    if ((eps << 1) >= dx)
                    {
                        y += uy; eps -= dx;
                    }
                }
            }
            else
            {
                for (y = y1; y != y2; y += uy)
                {
                    p.drawPoint(x,y);
                    eps += dx;
                    if ((eps << 1) >= dy)
                    {
                        x += ux; eps -= dy;
                    }
                }
            }

            //p.drawLine(x0,y0,x1,y1);
            i7++;
        }
        else if(_drawType == 8)
        {
            if(_lineflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            if(_colorflag==1)
            {
                p.setPen(QPen(_color.at(c),_width.at(c),_penstyle));
            }
            if(i8>=1)
            {
                p.drawLine(cx,cy,_point.at(i8).x(),_point.at(i8).y());
            }
            cx=_point.at(i8).x();cy=_point.at(i8).y();
            update();
            polygon poly(_point,seed,Qt::red);
            poly.showPolygonInEdgeTable(&p);
            i8++;
        }
        else if(_drawType == 9)
        {
            polygon poly(_point,seed,Qt::red);
            poly.showPolygonInEdgeTable(&p);
            //seed.setX(300);seed.setY(300);
            if(poly.isInPolygon(seed))
            {
                poly.showPolygonInSeed(&p);
                p.drawPoint(seed);
            }
            update();
        }
        else if(_drawType == 10)
        {
            polygon poly(_point,seed,Qt::red);
            poly.showPolygonInEdgeTable(&p);
            //seed.setX(300);seed.setY(300);
            if(poly.isInPolygon(seed))
            {
                poly.showPolygonInSeed(&p);
                p.drawPoint(seed);
            }

            QPoint p0(_line.at(0).topLeft().x(),_line.at(0).topLeft().y());
            QPoint p1(_line.at(0).bottomRight().x(),_line.at(0).bottomRight().y());
            //p.drawLine(10,10,100,100);
            if(lineClip(p0, p1, _rects.at(0)))
            {
                p.setPen(QPen(Qt::white,Qt::DashDotLine));
                p.drawLine(p0,p1);
            }
            update();
            i10++;
        }
        else if(_drawType == 11)
        {

            QPoint p0=_point.at(0);

            QPoint pg;
            for(int i=0;i<_point.size();i++)
            {
                pg=_point.at(i);
                pg.setX(pg.x()+(pointf.x()-p0.x()));
                pg.setY(pg.y()+(pointf.y()-p0.y()));
                _point.replace(i,pg);
            }
            polygon poly(_point,seed,Qt::red);
            poly.showPolygonInEdgeTable(&p);
            update();
        }
        else if(_drawType == 12)
        {



        }
        else if(_shape.at(c) == 13)
        {
            double sx,sy;
            polygon poly(_point,seed,Qt::red);
            poly.showPolygonInEdgeTable(&p);
            QPoint pz;
            for(int i=0;i<_point.size();i++)
            {
                pz=_point.at(i);
                sx=(propotionline.at(i13).bottomRight().x()-center.x())*1.0/(propotionline.at(i13).topLeft().x()-center.x());
                sy=(propotionline.at(i13).bottomRight().y()-center.y())*1.0/(propotionline.at(i13).topLeft().y()-center.y());
                qDebug()<<sx<<" "<<sy;
                pz.setX(pz.x()*sx+center.x()*(1-sx));
                pz.setY(pz.y()*sy+center.y()*(1-sy));
                _point.replace(i,pz);
            }
            p.drawLine(propotionline.at(i13).topLeft(),propotionline.at(i13).bottomRight());
            i13++;
        }
        else if(_shape.at(c) == 14)
        {

            double angle=360-beginline.angleTo(endline);
            p.translate(center.x(),center.y());
            p.rotate(angle);
            polygon poly(_point,seed,Qt::red);
            poly.showPolygonInEdgeTable(&p);
            qDebug()<<angle;
        }
        else if(_shape.at(c) == 15)
        {
            p.setRenderHint(QPainter::Antialiasing, true);
            p.setPen(m_curvePen);
            /*QPainterPath path;
            path.moveTo(m_points[StartPoint]);
            path.cubicTo(m_points[ControlPoint1], m_points[ControlPoint2], m_points[EndPoint]);
            p.drawPath(path);*/

            float xarray[2001];
            float yarray[2001];
            int n = 4;//number
            float ps[2001][2];
            float ctrlPoints[4][2];
            ctrlPoints[0][0]=m_points[StartPoint].x();
            ctrlPoints[0][1]=m_points[StartPoint].y();
            ctrlPoints[1][0]=m_points[ControlPoint1].x();
            ctrlPoints[1][1]=m_points[ControlPoint1].y();
            ctrlPoints[2][0]=m_points[ControlPoint2].x();
            ctrlPoints[2][1]=m_points[ControlPoint2].y();
            ctrlPoints[3][0]=m_points[EndPoint].x();
            ctrlPoints[3][1]=m_points[EndPoint].y();

            int u = 0;
            for(double t = 0.0000;t<=1;t+=0.0005)
            {
                for (int i = 1; i < n; ++i)
                {
                    for (int j = 0; j < n - i; ++j)
                    {
                        if (i == 1) // i==1时,第一次迭代,由已知控制点计算
                        {
                            xarray[j] = ctrlPoints[j][0] * (1 - t) + ctrlPoints[j+1][0] * t;
                            yarray[j] = ctrlPoints[j][1] * (1 - t) + ctrlPoints[j + 1][1] * t;
                            continue;
                        }
                        // i != 1时,通过上一次迭代的结果计算
                        xarray[j] = xarray[j] * (1 - t) + xarray[j + 1] * t;
                        yarray[j] = yarray[j] * (1 - t) + yarray[j + 1] * t;
                    }

                }
                ps[u][0] = xarray[0];
                ps[u][1] = yarray[0];
                u++;
            }

            QVector<QPoint> bezier;
            QPoint bezierpoint;
            for (int i = 0; i < 2001; i++)
            {
                bezierpoint.setX(ps[i][0]);
                bezierpoint.setY(ps[i][1]);
                bezier.append(bezierpoint);

            }

            p.drawLines(bezier);
            for (int i = 0; i < NUM_POINTS; i++) {
                p.setPen(m_pens[i]);
                //p.setBrush(m_brushes[i]);
                p.drawEllipse(m_points[i], POINT_RADIUS, POINT_RADIUS);
            }
        }
    }
    p.end();
    p.begin(this);//将当前窗体作为画布
    p.drawPixmap(0,0, pix);//将pixmap画到窗体
}

void MyPaint::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)//当鼠标左键按下
    {

        if(_drawType == 3)//椭圆
        {
            _lpress = true;//左键按下标志
            if(!_drag)//非拖拽模式
            {
                QRect rect;//鼠标按下，椭圆开始
                _ellipse.append(rect);//将新椭圆添加到椭圆集合
                QRect& lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setTopLeft(e->pos());//记录鼠标的坐标(新椭圆的左上角坐标)
                _color.append(_colortype);
                _width.append(_lineType);
                _shape.append(3);
            }
            else if(_ellipse.last().contains(e->pos()))//如果在椭圆内按下
            {
                _begin = e->pos();//记录拖拽开始的坐标位置

            }
        }
        else if(_drawType == 2)//矩形
        {
            _lpress = true;//左键按下标志
            if(!_drag)//非拖拽模式
            {
                QRect rect;//鼠标按下，矩形开始
                _rects.append(rect);//将新矩形添加到矩形集合
                QRect& lastRect = _rects.last();//拿到新矩形
                lastRect.setTopLeft(e->pos());//记录鼠标的坐标(新矩形的左上角坐标)
                _shape.append(2);
            }
            else if(_rects.last().contains(e->pos()))//拖拽模式、如果在矩形内按下
            {
                _begin = e->pos();//记录拖拽开始的坐标位置,方便计算位移

            }

        }
        else if(_drawType == 4)//dda直线
        {
            _lpress = true;//左键按下标志
            QRect rect;//鼠标按下，直线一端开始
            _line.append(rect);//将新直线添加到直线集合
            QRect& lastLine = _line.last();//拿到新直线
            lastLine.setTopLeft(e->pos());//记录鼠标的坐标(新直线开始一端坐标)

            _color.append(_colortype);
            _width.append(_lineType);
            _shape.append(4);
        }
        else if(_drawType == 6)//中点直线
        {
            _lpress = true;//左键按下标志
            QRect rect;//鼠标按下，直线一端开始
            _line1.append(rect);//将新直线添加到直线集合
            QRect& lastLine = _line1.last();//拿到新直线
            lastLine.setTopLeft(e->pos());//记录鼠标的坐标(新直线开始一端坐标)
            _color.append(_colortype);
            _width.append(_lineType);
            _shape.append(6);
        }
        else if(_drawType == 7)//bresenham直线
        {
            _lpress = true;//左键按下标志
            QRect rect;//鼠标按下，直线一端开始
            _line2.append(rect);//将新直线添加到直线集合
            QRect& lastLine = _line2.last();//拿到新直线
            lastLine.setTopLeft(e->pos());//记录鼠标的坐标(新直线开始一端坐标)
            _color.append(_colortype);
            _width.append(_lineType);
            _shape.append(7);
        }
        else if(_drawType == 8)//多边形
        {
            _lpress = true;//左键按下标志
            if(!_drag)
            {

                QPoint point;
                _point.append(point);
                QPoint& lastPoint=_point.last();
                lastPoint.setX(e->pos().x());
                lastPoint.setY(e->pos().y());
                _color.append(_colortype);
                _width.append(_lineType);
                _shape.append(8);
            }
            else if(QPolygon(_point).contains(e->pos()))//拖拽模式、如果在矩形内按下
            {
                _begin = e->pos();//记录拖拽开始的坐标位置,方便计算位移

            }
        }
        else if(_drawType == 9)
        {
            _lpress = true;//左键按下标志
            seed.setX(e->pos().x());
            seed.setY(e->pos().y());
            qDebug()<<seed.x()<<" "<<seed.y();
        }
        else if(_drawType == 10)
        {
            _lpress = true;//左键按下标志

        }
        else if(_drawType == 11)
        {
            _lpress = true;//左键按下标志

            pointf.setX(e->pos().x());
            pointf.setY(e->pos().y());
            qDebug()<<pointf.x()<<" "<<pointf.y();

        }
        else if(_drawType == 12)
        {
            _lpress = true;//左键按下标志

            center.setX(e->pos().x());
            center.setY(e->pos().y());
            qDebug()<<center.x()<<" "<<center.y();

        }
        else if(_drawType == 13)
        {
            _lpress = true;//左键按下标志
            QRect rect;//鼠标按下，直线一端开始
            propotionline.append(rect);//将新直线添加到直线集合
            QRect& lastLine = propotionline.last();//拿到新直线
            lastLine.setTopLeft(e->pos());//记录鼠标的坐标(新直线开始一端坐标)
            _shape.append(13);
            qDebug()<<lastLine.topLeft().x()<<" "<<lastLine.topLeft().y();

        }
        else if(_drawType == 14)
        {
            _lpress = true;//左键按下标志
            QPoint beginpoint(e->pos());
            beginline.setP1(center);
            beginline.setP2(beginpoint);
            _shape.append(14);
        }
        else if(_drawType == 15)
        {
            _lpress = true;
            for(int i = 0; i < NUM_POINTS; i++) {
                if(distance(m_points[i], e->pos()) <= POINT_RADIUS) {
                    m_selectedPoint = i;
                    m_dragging = true;
                    break;
                }
            }
            _shape.append(15);
        }
    }
}

void MyPaint::mouseMoveEvent(QMouseEvent *e)
{
    if(_drag &&  ((_drawType == 3  && _ellipse.last().contains(e->pos())) || (_drawType == 2  && _rects.last().contains(e->pos())) ))
    {
        setCursor(Qt::SizeAllCursor);//拖拽模式下，并且在拖拽图形中，将光标形状改为十字
    }
    else
    {
        setCursor(Qt::ArrowCursor);//恢复原始光标形状
        _drag = 0;
    }

    if(_lpress)
    {
        if(_drawType == 3)//圆
        {
            if(_drag == 0)//非拖拽
            {
                QRect& lastEllipse = _ellipse.last();//拿到新椭圆
                lastEllipse.setBottomRight(e->pos());//更新椭圆的右下角坐标)

            }
            else//拖拽
            {
                QRect& lastEllipse = _ellipse.last();//拿到最后添加的矩形
                if(lastEllipse.contains(e->pos()))//在椭圆内部
                {
                    int dx = e->pos().x()-_begin.x();//横向移动x
                    int dy = e->pos().y()-_begin.y();//纵向移动y
                    lastEllipse = lastEllipse.adjusted(dx,dy,dx,dy);
                    _begin = e->pos();//刷新拖拽点起始坐标
                }

            }
            update();//触发窗体重绘
        }
        else if(_drawType == 2)
        {
            if(_drag == 0)//非拖拽
            {
                QRect& lastRect = _rects.last();//拿到新矩形
                lastRect.setBottomRight(e->pos());//更新矩形的右下角坐标
            }
            else//拖拽模式
            {
                QRect& lastRect = _rects.last();//拿到最后添加的矩形
                if(lastRect.contains(e->pos()))//在矩形的内部
                {
                    int dx = e->pos().x()-_begin.x();//横向移动x
                    int dy = e->pos().y()-_begin.y();//纵向移动y
                    lastRect = lastRect.adjusted(dx,dy,dx,dy);//更新矩形的位置
                    _begin = e->pos();//刷新拖拽点起始坐标
                }

            }
            update();//触发窗体重绘

        }
        else if(_drawType == 4)
        {
            QRect& lastLine = _line.last();//拿到新直线
            lastLine.setBottomRight(e->pos());//更新直线另一端)
            update();//触发窗体重绘
        }
        else if(_drawType == 6)
        {
            QRect& lastLine = _line1.last();//拿到新直线
            lastLine.setBottomRight(e->pos());//更新直线另一端)
            update();//触发窗体重绘
        }
        else if(_drawType == 7)
        {
            QRect& lastLine = _line2.last();//拿到新直线
            lastLine.setBottomRight(e->pos());//更新直线另一端)
            update();//触发窗体重绘
        }
        else if(_drawType == 8)
        {
            if(!_drag)
            {
                QPoint& lastPoint = _point.last();
                lastPoint=e->pos();
            }
            else
            {

            }
            update();
        }
        else if(_drawType == 9)
        {

            //update();
        }
        else if(_drawType == 10)
        {

            //update();
        }
        else if(_drawType == 11)
        {

            //update();
        }
        else if(_drawType == 12)
        {

            //update();
        }
        else if(_drawType == 13)
        {
            QRect& lastLine = propotionline.last();//拿到新直线
            lastLine.setBottomRight(e->pos());//更新直线另一端)
            //qDebug()<<propotionline.bottomRight().x()<<" "<<propotionline.bottomRight().y();
            update();

        }
        else if(_drawType == 14)
        {
            QPoint endpoint(e->pos());
            endline.setP1(center);
            endline.setP2(endpoint);
            update();
        }
        else if(_drawType == 15)
        {
            if(m_dragging) {
                m_points[m_selectedPoint] = e->pos();
            }
            update();
        }
    }
}

void MyPaint::mouseReleaseEvent(QMouseEvent *e)
{
    if(_lpress)
    {
        if(_drawType == 3)
        {
            QRect& lastEllipse = _ellipse.last();//拿到新椭圆
            if(!_drag)
            {
                lastEllipse.setBottomRight(e->pos());//不是拖拽时，更新椭圆的右下角坐标)
                //刚画完椭圆，将光标设置到新椭圆的中心位置，并进入拖拽模式
                this->cursor().setPos(this->cursor().pos().x()-lastEllipse.width()/2,this->cursor().pos().y()-lastEllipse.height()/2);
                _drag = 1;

            }
            _lpress = false;
        }
        else if(_drawType == 2)
        {
            QRect& lastRect = _rects.last();//拿到新矩形
            if(!_drag)
            {
                lastRect.setBottomRight(e->pos());//不是拖拽时，更新矩形的右下角坐标)
                //刚画完矩形，将光标设置到新矩形的中心位置，并进入拖拽模式
                this->cursor().setPos(this->cursor().pos().x()-lastRect.width()/2,this->cursor().pos().y()-lastRect.height()/2);
                _drag = 1;

            }
            _lpress = false;

        }
        else if(_drawType == 4)
        {
            QRect& lastLine = _line.last();//拿到新矩形
            lastLine.setBottomRight(e->pos());//更新矩形的右下角坐标)
            _lpress = false;

        }
        else if(_drawType == 6)
        {
            QRect& lastLine = _line1.last();//拿到新矩形
            lastLine.setBottomRight(e->pos());//更新矩形的右下角坐标)
            _lpress = false;

        }
        else if(_drawType == 7)
        {
            QRect& lastLine = _line2.last();//拿到新矩形
            lastLine.setBottomRight(e->pos());//更新矩形的右下角坐标)
            _lpress = false;
        }
        else if(_drawType == 8)
        {
            QPoint& lastPoint = _point.last();
            if(!_drag)
            {
                lastPoint=e->pos();
                _drag = 1;
            }
            _lpress = false;
        }
        else if(_drawType == 9)
        {
            _lpress = false;
        }
        else if(_drawType == 10)
        {
            _lpress = false;
        }
        else if(_drawType == 11)
        {
            _lpress = false;
        }
        else if(_drawType == 12)
        {
            _lpress = false;
        }
        else if(_drawType == 13)
        {


            QRect& lastLine = propotionline.last();//拿到新直线
            lastLine.setBottomRight(e->pos());//更新直线另一端)
            qDebug()<<lastLine.bottomRight().x()<<" "<<lastLine.bottomRight().y();
            _lpress = false;
        }
        else if(_drawType == 14)
        {
            QPoint endpoint(e->pos());
            endline.setP1(center);
            endline.setP2(endpoint);
            _lpress = false;
        }
        else if(_drawType == 15)
        {
            m_dragging = false;
        }
    }
}

bool MyPaint::lineClip(QPoint& p0, QPoint& p1, QRect rt)
{
    bool accept, done;
    char c0, c1, code;
    int x0, y0, x1, y1, x, y;
    double m;
    accept = false;//线段可见标志
    done = false;//裁剪完成标志
    x0 = p0.x();
    y0 = p0.y();
    x1 = p1.x();
    y1 = p1.y();
    c0 = getCSCode(x0, y0, rt);//返回线段起点的编码
    c1 = getCSCode(x1, y1, rt);//返回线段终点的编码
    while (!done)
    {
        if (!c0 && !c1){//线段完全可见
            p0 = QPoint(x0,y0);
            p1 = QPoint(x1,y1);

            //可见，处理完成
            accept = true;
            done = true;
        }
        else if (c0&c1){//线段完全不可见
            p0 = QPoint(0,0);
            p1 = QPoint(0,0);

            //不可见，处理完成
            accept = false;
            done = true;
        }
        else{//处理非完全可见又非显然不可见的情况

            //P0不可见不意味着P1可见；但P0可见则P1此时一定不可见
            if (c0){//p0不可见
                code = c0;
            }
            else{////p0可见，则p1一定不可见
                code = c1;
            }
            //x已知，求x增量
            if (code & 0x01){//线段与窗口的左边有交
                x = rt.left();
                m = (double)(y1 - y0) / (double)(x1 - x0);
                y = y0 + (int)((x - x0)*m);
            }
            //y已知，求y增量
            else if (code & 0x08){//线段与窗口的下边有交
                y = rt.bottom();
                m = (double)(x1 - x0) / (double)(y1 - y0);
                x = x0 + (int)((y - y0)*m);
            }
            else if (code & 0x02){//线段与窗口的右边有交
                x = rt.right();
                m = (double)(y1 - y0) / (double)(x1 - x0);
                y = y0 + (int)((x - x0)*m);
            }
            else if (code & 0x04){//线段与窗口的上边有交
                y = rt.top();
                m = (double)(x1 - x0) / (double)(y1 - y0);
                x = x0 + (int)((y - y0)*m);
            }
            //求交后用交点替代源点
            if (code == c0){
                x0 = x;		y0 = y;
                c0 = getCSCode(x0, y0, rt);
            }
            else{
                x1 = x;		y1 = y;
                c1 = getCSCode(x1, y1, rt);
            }
        }
    }
    return accept;
}

char MyPaint::getCSCode(int x, int y, QRect rt)
{
    char code=0;
    if(x<rt.left())//编码为***1,最后一位置1
        code=code|0x01;
    else//编码为***0，最后一位置0
        code=code&0xfe;
    if(x>rt.right())//编码为**1*
        code=code|0x02;
    else//编码为**0*
        code=code&0xfd;
    if(y<rt.top())//编码为*1**
        code=code|0x04;
    else//编码为*0**
        code=code&0xfb;
    if(y>rt.bottom())//编码为1***
        code=code|0x08;
    else//编码为0***
        code=code&0xf7;
    return code;
}

void MyPaint::Ellipses()
{
    _drawType = 3;//椭圆
}

void MyPaint::Line()
{
    _drawType = 4;//dda直线
}

void MyPaint::Line1()
{
    _drawType =6;//中点
}

void MyPaint::Line2()
{
    _drawType =7;//bresenham
}

void MyPaint::Rects()
{
    _drawType = 2;
}

void MyPaint::Polygon()
{
    _drawType =8;//扫描转换
}

void MyPaint::Seed()
{
    _drawType =9;//种子填充
}

void MyPaint::Cut()
{
    _drawType=10;
}

void MyPaint::Move()
{
    _drawType=11;
}

void MyPaint::Setcenter()
{
    _drawType=12;
}


void MyPaint::Scale()
{
    _drawType=13;
}

void MyPaint::Rotate()
{
    _drawType=14;
}

void MyPaint::Bezier()
{
    _drawType=15;
}

void MyPaint::SavePic()
{
    //弹出文件保存对话框
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存"), "new.jpg", "Image (*.jpg *.png *.bmp)");

    if (fileName.length() > 0)
    {
        QPixmap pixmap(size());//新建窗体大小的pixmap
        QPainter painter(&pixmap);//将pixmap作为画布
        painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);//设置绘画区域、画布颜色
        this->render(&painter);//将窗体渲染到painter，再由painter画到画布
        pixmap.copy(QRect(0,30,size().width(),size().height()-30)).save(fileName);//不包含工具栏
    }
}

void MyPaint::OpenPic()
{
    //弹出文件打开对话框
    QString picPath = QFileDialog::getOpenFileName(this,tr("打开"),"","Image Files(*.jpg *.png)");
    if(!picPath.isEmpty())//用户选择了文件
    {
        QPixmap pix;
        pix.load(picPath);//加载图片
        QPainter p(&_pixmap);
        p.drawPixmap(0,30,pix);//添加工具栏的空间
        _openflag = 1;//设置文件打开标志
        update();//触发窗体重绘，将图片画到窗体
    }
}

void MyPaint::LineType()
{
    _lineflag=1;
    _lineType=3;
}

void MyPaint::LineType5()
{
    _lineflag=1;
    _lineType=5;
}

void MyPaint::LineType7()
{
    _lineflag=1;
    _lineType=7;
}


void MyPaint::ColorType()
{
    _colorflag=1;
    _colortype=Qt::red;
}

void MyPaint::ColorType1()
{
    _colorflag=1;
    _colortype=Qt::green;
}

void MyPaint::ColorType2()
{
    _colorflag=1;
    _colortype=Qt::blue;
}

void MyPaint::contextMenuEvent(QContextMenuEvent *)  //右键菜单事件
{
    _Rmenu->exec(cursor().pos());//在光标位置弹出菜单
}

void MyPaint::keyPressEvent(QKeyEvent *e) //按键事件
{
    //Ctrl+Z撤销
    if (e->key() == Qt::Key_Z && e->modifiers() == Qt::ControlModifier)
    {
        if(_shape.size()>0)
        {
            switch(_shape.last())
            {

            case 1: _ellipse.pop_back();
                break;
            case 2: _line.pop_back();
                break;
            }
            _shape.pop_back();
            _drag = 0;//设置为非拖拽模式
            update();
        }
    }
    else if (e->key() == Qt::Key_S && e->modifiers() == Qt::ControlModifier)//保存
    {
        SavePic();//Ctrl+S保存
    }
}
