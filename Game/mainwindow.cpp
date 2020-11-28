#include "settingsdialog.hh"
#include "mainwindow.h"
#include "game_engine.h"
#include "ui_mainwindow.h"
#include "QElapsedTimer"
#include "QTime"

#include <QDebug>
#include <QLayout>
#include <QWidget>
const int PADDING = 10;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),

    ui(new Ui::MainWindow)
{

    ui->setupUi(this);



    //STAT LABELS

    ui->cash_value->setText(QString("120"));
    ui->drunk_value->setText(QString("1"));
    ui->speed_value->setText(QString("50"));



    //TIMER

    timer = new QTimer(this);
    timer->start(tick_);
    connect(timer, &QTimer::timeout, map_scene, &QGraphicsScene::advance);
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

MainWindow::~MainWindow()
{
    delete ui;
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
    CourseSide::SimpleActorItem* nActor = new CourseSide::SimpleActorItem(locX, locY, type);
    actors_.push_back(nActor);
    map_scene->addItem(nActor);
    last_ = nActor;
}

void MainWindow::updateCoords(int nX, int nY)
{
    last_->setCoord(nX, nY);
}

void MainWindow::setPicture(QImage &img)
{

    QGraphicsScene* mapScene = new QGraphicsScene;
    mapScene->setSceneRect(0,0,500,500);
    mapScene->setBackgroundBrush(img);
    ui->mapView->setScene(mapScene);

}


void MainWindow::on_PortraitView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}


void MainWindow::on_SettingsButton_clicked()
{
    settingsDialog sDialog;
    sDialog.setModal(true);
    QObject::connect(&sDialog, &settingsDialog::settingsSet, this, &MainWindow::savePlayerInfo);
    sDialog.exec();
}


void MainWindow::on_StartButton_clicked()
{
   std::string nimi1 = "Jaakko";
   std::string vari1 = "musta";
   std::string nimi2 = "Teppo";
   std::string vari2 = "vaaleanpunainen";

   std::pair<std::string, std::string> pari1 = {nimi1,vari1};
   std::pair<std::string, std::string> pari2 = {nimi2,vari2};

   std::vector<std::pair<std::string, std::string>> vec = {pari1,pari2};
   createPlayers(2,vec);

    //Tämä pitäisi saada toimimaan
    //createPlayers(playerCount_, playerSpecs_);
}

void MainWindow::savePlayerInfo(int playerCount, std::vector<std::pair<std::string, std::string> > playerSpecs)
{
    playerCount_ = playerCount;
    playerSpecs_ = playerSpecs;
}
