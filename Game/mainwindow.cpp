#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

const int PADDING = 10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //ui->centralwidget->setFixedSize(width_ + ui->startButton->width() + PADDING, height_ + PADDING);

    //ui->startButton->move(width_ + PADDING , PADDING);
    //map = new QGraphicsScene(this);
    //ui->MapScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //ui->MapScrollArea->setWidgetResizable(false);

    //ui->MapScrollArea->setGeometry(0,0,510,500);

    QString file = (":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    //QPixmap pixmapItem(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    ui->scrollAreaWidgetContents->setWindowFilePath(file);
    //ui->scrollAreaWidgetContents->show();
    auto city_map = new QGraphicsView(this);
    ui->mapView->setViewport(city_map);

    timer = new QTimer(this);

    //connect   (timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    timer->start(tick_);



    QString display_value = "00:00";
    //ui->partyTimeLcd->setPalette(Qt::red);
    ui->travelTimeLcd->setPalette(Qt::red);
    //ui->totalTimeLcd->setPalette(Qt::red);
    //ui->partyTimeLcd->setStyleSheet("QLabel { background-color : rgba(0,0,255));
    //ui->partyTimeLcd->display(display_value);
    ui->travelTimeLcd->display(timer->remainingTime());
    //ui->totalTimeLcd->display(display_value);
    //this->setCentralWidget(ui->MapScrollArea);

    //map->setSceneRect(0,0,150,150);

    portrait = new QGraphicsScene(this);
    ui->PortraitView->setScene(portrait);
    portrait->setSceneRect(0,0,150,150);

    QPixmap pixmapItem(":/graphics/0prom_small.png");
    QPixmap pixmapItems = pixmapItem.scaled(QSize(130,130),  Qt::KeepAspectRatio);
    ui->PortraitView->setBackgroundBrush(pixmapItem);

    ui->MapScrollArea->show();
    //ui->PortraitView->setFixedSize(150,150);
    ui->PortraitView->show();




}
/*
MainWindow::~MainWindow()
{
    delete ui;
}*/

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
