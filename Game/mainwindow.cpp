#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QElapsedTimer"
#include "QTime"
#include <QDebug>

const int PADDING = 10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //ui->centralwidget->setFixedSize(width_ + ui->startButton->width() + PADDING, height_ + PADDING);

    //ui->startButton->move(width_ + PADDING , PADDING);
  //  map = new QScrollArea(this);
   // ui->MapScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);


    ui->MapScrollArea->setGeometry(0,0,510,500);

    QString file = (":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    QPixmap pixmapItem_map(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    ui->mapView->setBackgroundBrush(pixmapItem_map);
    auto map_scene = new QGraphicsScene(this);
    ui->mapView->setScene(map_scene);
    map_scene->setSceneRect(0,0,1095,592);

    ui->mapView->show();
  /*  auto city_map = new QGraphicsView(this);
    city_map->setBackgroundBrush(pixmapItem1);
    ui->mapView->setViewport(city_map);
    ui->MapScrollArea->setViewport(city_map);
    ui->scrollAreaWidgetContents->setWindowFilePath(file);
    //ui->scrollAreaWidgetContents->show();*/
/*
    QPixmap mapItem(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    QPixmap mapItems = mapItem.scaled(QSize(500,500),  Qt::KeepAspectRatio);
    ui->mapView->show();*/

/*
    portrait = new QGraphicsScene(this);
    ui->PortraitView->setScene(portrait);

    portrait->setSceneRect(0,0,119,119);
    QPixmap pixmapItem(":/graphics/1prom2.png");
    pixmapItem= pixmapItem.scaled(ui->PortraitView->size(), Qt::IgnoreAspectRatio);

*/

    /*QPalette palette;


    QPixmap pixmapItems = pixmapItem.scaled(QSize(130,130),  Qt::KeepAspectRatio);
    ui->PortraitView->setBackgroundBrush(pixmapItem);*/

    //QLabel *label = new QLabel(this);


    ui->cash_value->setText(QString("120"));
    ui->drunk_value->setText(QString("1"));
    ui->speed_value->setText(QString("50"));






    //ui->cash_value->text();






    timer = new QTimer(this);
    auto e_timer = new QElapsedTimer();
    e_timer->start();
    //connect   (timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    timer->start(tick_);


    QString display_value = "00:00";
    //ui->partyTimeLcd->setPalette(Qt::red);
    ui->travelTimeLcd->setPalette(Qt::red);
    //ui->totalTimeLcd->setPalette(Qt::red);
    //ui->partyTimeLcd->setStyleSheet("QLabel { background-color : rgba(0,0,255));
    //ui->partyTimeLcd->display(display_value);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, [&]() {
    QString time1 = QTime::currentTime().toString();
    ui->travelTimeLcd->display(time1);
    timer->start();
    });

    std::string elapsed_str = std::to_string(e_timer->elapsed());
    QString elapsed = QString::fromStdString(elapsed_str);
    ui->travelTimeLcd->display(elapsed);

    //connect(timer, &QTimer:: )
    //connect (e_timer, &QElapsedTimer::)

    //std::string timer_str = std::to_string(timer->remainingTimeAsDuration());
    //qDebug() << timer->remainingTimeAsDuration();
    //ui->totalTimeLcd->display(display_value);
    //this->setCentralWidget(ui->MapScrollArea);

    //map->setSceneRect(0,0,150,150);









    portrait = new QGraphicsScene(this);
    ui->PortraitView->setScene(portrait);

    portrait->setSceneRect(0,0,119,119);
    QPixmap pixmapItem(":/graphics/1prom2.png");
    pixmapItem= pixmapItem.scaled(ui->PortraitView->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    //palette.setBrush(QPalette::Background, pixmapItem);
    //ui->PortraitView->setPalette(palette);

    /*
    QPixmap pixmapItems = pixmapItem.scaled(QSize(120,120),  Qt::KeepAspectRatio);
    ui->PortraitView->scale(150,150);
    QBrush harja;*/

    //ui->PortraitView->setAutoFillBackground(true);
    //ui->PortraitView->
    ui->PortraitView->setBackgroundBrush(pixmapItem);
    //QGraphicsPixmapItem *pPix = portrait->addPixmap(pixmapItems);

    //ui->PortraitView->fitInView(pPix);
    //ui->graphicsView->fitInView(pPix);


    //ui->PortraitView->fitInView(0,0,150,150);
    //QGraphicsView::fitInView(const QGraphicsItem * item, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio);
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
