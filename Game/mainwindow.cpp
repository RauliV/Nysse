#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

const int PADDING = 10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pixmapItem(":/graphics/oprom.png");
    QPixmap pixmapItems = pixmapItem.scaled(QSize(150,150),  Qt::KeepAspectRatio);

    ui->PortraitView->setBackgroundBrush(pixmapItem);
    ui->PortraitView->show();
    /*QGraphicsScene* map = new QGraphicsScene(this);

    QGraphicsView* view = new QGraphicsView(this);
    setup PortalView
    map->addPixmap(pixmapItems);
    view->setScene(map);
    QScrollArea()
    QAbstractScrollArea(Graphicso)
    setCentralWidget(view);
            */

    //gameView->setFixedSize(width_, height_);
    //ui->centralwidget->setFixedSize(width_ + ui->startButton->width() + PADDING, height_ + PADDING);

    //ui->startButton->move(width_ + PADDING , PADDING);

    //map = new QGraphicsScene(this);
    //ui->gameView->setScene(map);
    //map->setSceneRect(0,0,width_,height_);
    //ui->MapScrollArea->scroll   setWidget()
    //resize(minimumSizeHint());
    //ui->gameView->fitInView(0,0, MAPWIDTH, MAPHEIGHT, Qt::KeepAspectRatio);
/*
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    timer->start(tick_);/*
}

/*MainWindow::~MainWindow()
{
    delete ui;
}*/
}
void MainWindow::setSize(int w, int h)
{
    width_ = w;
    height_ = h;
}

void MainWindow::setTick(int t)
{
    tick_ = t;
}

void MainWindow::addActor(int locX, int locY, int type)
{
    /*SimpleActorItem* nActor = new SimpleActorItem(locX, locY, type);
    actors_.push_back(nActor);
    map->addItem(nActor);
    last_ = nActor; */
}

void MainWindow::updateCoords(int nX, int nY)
{
    //last_->setCoord(nX, nY);
}

void MainWindow::setPicture(QImage &img)
{
    //Ui_MainWindow::PortraitView::
    //menuNysse  PortraitView()
    //map->setBackgroundBrush(img);
    //map->
}


void MainWindow::on_startButton_clicked()
{
    qDebug() << "Start clicked";
    //emit gameStarted();
}

void MainWindow::on_PortraitView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}
