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

    // MAP

    ui->MapScrollArea->setGeometry(0,0,529,529);
    QPixmap pixmapItem_map(":/offlinedata/offlinedata/kartta_iso_1095x592.png");
    ui->mapView->setBackgroundBrush(pixmapItem_map);
    auto map_scene = new QGraphicsScene(this);
    ui->mapView->setScene(map_scene);
    map_scene->setSceneRect(0,0,1095,592);


    //STAT LABELS

    ui->cash_value->setText(QString("120"));
    ui->drunk_value->setText(QString("1"));
    ui->speed_value->setText(QString("50"));



    //TIMER

    timer = new QTimer(this);
    timer->start(tick_);
    //connect   (timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    ui->travelTimeLcd->setPalette(Qt::red);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, [&]() {
    QString time1 = QTime::currentTime().toString();
    ui->travelTimeLcd->display(time1);
    });


    /* e_timer for elapsed timer if needed
    auto e_timer = new QElapsedTimer();
    e_timer->start();
    std::string elapsed_str = std::to_string(e_timer->elapsed());
    QString elapsed = QString::fromStdString(elapsed_str);
    ui->travelTimeLcd->display(elapsed); */


    //PORTRAIT

    portrait = new QGraphicsScene(this);
    ui->PortraitView->setScene(portrait);

    portrait->setSceneRect(0,0,119,119);
    QPixmap pixmap_portrait(":/graphics/1prom2.png");
    pixmap_portrait = pixmap_portrait.scaled(ui->PortraitView->size(), Qt::IgnoreAspectRatio);

    ui->PortraitView->setBackgroundBrush(pixmap_portrait);
    ui->MapScrollArea->show();
    ui->mapView->show();
    ui->PortraitView->show();
    //(this)->show();


}
/*
MainWindow::~MainWindow() // Mikä on, kun ei suksi kulje?
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

void MainWindow::on_pushButton_clicked()
{
    settingsDialog PDialog;
    PDialog.setModal(true);
    PDialog.exec();
}
