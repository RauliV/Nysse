#include "settingsdialog.hh"
#include "mainwindow.h"
#include "setboard.hh"
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
    ui->StartButton->setDisabled(true);
    loadImages();
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

void MainWindow::setTimer()
{
    timer = new QTimer(this);
    timer->start(tick_);
    connect(timer, &QTimer::timeout, map_scene, &QGraphicsScene::advance);
    ui->travelTimeLcd->setPalette(Qt::red);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, [&]() {
    QString time1 = QTime::currentTime().toString();
    ui->travelTimeLcd->display(time1);
    });
    connect(timer, &QTimer::timeout, this, &MainWindow::updateActors);
    //connect(timer, %QTimer::timeout, ,);

}

void MainWindow::addActor(int locX, int locY, int type, std::shared_ptr<Interface::IActor> actor)
{
    std::shared_ptr<QImage> img = getActorImage(actor);
    ActorItem* nActor = new ActorItem(locX, locY, type, img, actor);
    actors_.push_back(nActor);
    map_scene->addItem(nActor);
    last_ = nActor;
}

void MainWindow::addStaticItem(int locX, int locY, std::shared_ptr<Interface::IStop> place)
{


    std::shared_ptr<QImage> img = getPlaceImage(place);
    StaticItem* nPlace = new StaticItem(locX, locY, 2, img, place);
    //connect(nPlace,&StaticItem::itemClicked, this, &MainWindow::mouseClicked);
    places_.push_back(nPlace);
    map_scene->addItem(nPlace);
    last_ = nPlace;
}

void MainWindow::updateCoords(int nX, int nY)
{
    last_->setCoord(nX, nY);
}

void MainWindow::updateActors()
{
    onTheTick(getPlayers().front());   //Tämä ehkä pitäisi saada järkevämpään paikkaan.

    for( int i = 0; i < actors_.size();i++)
    {
        actors_.at(i)->updateCoords();
    }
}

void MainWindow::setPicture(QImage &img)
{

    QGraphicsScene* mapScene = new QGraphicsScene;
    mapScene->setSceneRect(0,0,500,500);
    mapScene->setBackgroundBrush(img);
    ui->mapView->setScene(mapScene);
    map_scene = mapScene;

}

void MainWindow::createPlayerPortraits()
{
    //Adding space to mainwindow for portraits based on player count
    this->setFixedWidth(670 + 150*playerCount_);
    ui->horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);

    std::list<std::shared_ptr<Player>> playerList = getPlayers();
    std::list<std::shared_ptr<Player>>::iterator it;
    //going through all players to create individual portraits
    for(it = playerList.begin(); it != playerList.end(); it++)
    {
        //Widget that will contain all player info
        std::shared_ptr<Player> player = *it;
        QWidget* playerLayoutWidget = new QWidget;
        playerLayoutWidget->setMaximumSize(300, 300);
        playerLayoutWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

        //labels
        QLabel* nameLabel = new QLabel;
        QLabel* cashLabel = new QLabel;
        QLabel* bankLabel = new QLabel;
        QLabel* drunknessLabel = new QLabel;

        //Labels for player info
        nameLabel->setText(QString::fromStdString(player->getName()));
        cashLabel->setText("Cash: " + QString::number(player->getCash()));
        bankLabel->setText("Bank: " + QString::number(player->getBank()));
        drunknessLabel->setText("Drunkness: " + QString::number(player->getDrunkness()));

        //Portrait for player image
        portrait = new QGraphicsScene(this);
        portrait->setSceneRect(0,0,150,150);
        std::string color = player->getColour();
        if(color == "Red")
        {
            portrait->setBackgroundBrush(Qt::red);
        }
        else if(color == "Blue")
        {
            portrait->setBackgroundBrush(Qt::blue);
        }
        else if(color == "Green")
        {
            portrait->setBackgroundBrush(Qt::green);
        }
        else if(color == "Yellow")
        {
            portrait->setBackgroundBrush(Qt::yellow);
        }

        //portrait->setBackgroundBrush()

        //KOITIN PIENEMMÄLLÄ KUVALLA JA FRAMELLA, MAHTUUKO PAREMMIN

        QPixmap pixmap_portrait(":/graphics/0prom_small2.png");
        QGraphicsView* portraitView = new QGraphicsView;
        portrait->setForegroundBrush(pixmap_portrait);
        portraitView->setSceneRect(0,0,120,120);
        pixmap_portrait = pixmap_portrait.scaled(portraitView->size(), Qt::IgnoreAspectRatio);
        portraitView->setScene(portrait);


        //Vertical layout for labels and portrait
        QVBoxLayout* vLayout = new QVBoxLayout;
        vLayout->addWidget(nameLabel);
        vLayout->addWidget(cashLabel);
        vLayout->addWidget(bankLabel);
        vLayout->addWidget(drunknessLabel);
        vLayout->addWidget(portraitView);
        playerLayoutWidget->setLayout(vLayout);
        ui->horizontalLayout->addWidget(playerLayoutWidget);
    }
}

void MainWindow::on_SettingsButton_clicked()
{
    settingsDialog sDialog;
    sDialog.setModal(true);
    connect(&sDialog, &settingsDialog::settingsSet, this, &MainWindow::savePlayerInfo);
    sDialog.exec();
}


void MainWindow::on_StartButton_clicked()
{
    setTimer();
    createPlayers(playerSpecs_);
    createPlayerPortraits();
    //addActor(200,200, 90);
   /*std::string nimi1 = "Jaakko";
   std::string vari1 = "musta";
   std::string nimi2 = "Teppo";
   std::string vari2 = "vaaleanpunainen";

   std::pair<std::string, std::string> pari1 = {nimi1,vari1};
   std::pair<std::string, std::string> pari2 = {nimi2,vari2};

   std::vector<std::pair<std::string, std::string>> vec = {pari1,pari2};
   createPlayers(2,vec);*/

    ui->StartButton->setDisabled(true);
    ui->SettingsButton->setDisabled(true);

}

void MainWindow::savePlayerInfo(int playerCount, std::vector<std::pair<std::string, std::string> > playerSpecs)
{
    ui->StartButton->setEnabled(true);
    playerCount_ = playerCount;
    playerSpecs_ = playerSpecs;
}

std::shared_ptr<QImage> MainWindow::getActorImage(std::shared_ptr<Interface::IActor> actor)
{
    //Actors
    if (std::dynamic_pointer_cast<Taxi>(actor) != 0){
        return taxiImg_;
    }
    else if (std::dynamic_pointer_cast<Scooter>(actor) != 0){
        return scooterImg_;
    }
    else if (std::dynamic_pointer_cast<CourseSide::Nysse>(actor) != 0){
        return nysseImg_;
    }
    else if (std::dynamic_pointer_cast<Player>(actor) != 0){
        return walkImg_;
    }
    else if (std::dynamic_pointer_cast<CourseSide::Passenger>(actor) != 0){
        return barImg_;
    }
    else return nullptr;
}

std::shared_ptr<QImage> MainWindow::getPlaceImage(std::shared_ptr<Interface::IStop> place)
{
    //Places
    if (std::dynamic_pointer_cast<Atm>(place) != 0){
        return atmImg_;
    }
    else if (std::dynamic_pointer_cast<Bar>(place) != 0){
        return barImg_;
    }
    else return stopImg_;
}
/*
void MainWindow::mouseClicked(std::shared_ptr<Interface::IStop> place)
{
    qDebug() << place->getName();

}
*/
void MainWindow::loadImages()
{
    nysseImg_ = std::make_shared<QImage> (QImage(":/graphics/nysse_icon.png"));
    taxiImg_= std::make_shared<QImage> (QImage(":/graphics/taxi_icon.png"));
    scooterImg_= std::make_shared<QImage> (QImage(":/graphics/scooter_icon.png"));
    walkImg_= std::make_shared<QImage> (QImage(":/graphics/walk_or_passenger_icon.png"));
    barImg_= std::make_shared<QImage> (QImage(":/graphics/bar_icon_2.png"));
    atmImg_ = std::make_shared<QImage> (QImage(":/graphics/bus_stop_icon.png"));
    stopImg_ = std::make_shared<QImage> (QImage(":/graphics/bus_stop_file_2.png"));
}
