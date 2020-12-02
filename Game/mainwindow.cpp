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






    //TIMER



    /* e_timer for elapsed timer if needed
    auto e_timer = new QElapsedTimer();
    e_timer->start();
    std::string elapsed_str = std::to_string(e_timer->elapsed());
    QString elapsed = QString::fromStdString(elapsed_str);
    ui->travelTimeLcd->display(elapsed); */


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
}

void MainWindow::addActor(int locX, int locY, int type, QString iconPath, Interface::IActor* actor)
{
    ActorItem* nActor = new ActorItem(locX, locY, type, iconPath, actor);
    //CourseSide::SimpleActorItem* nActor = new CourseSide::SimpleActorItem(locX, locY, type);
    actors_.push_back(nActor);
    map_scene->addItem(nActor);
    last_ = nActor;
}

void MainWindow::updateCoords(int nX, int nY)
{
    last_->setCoord(nX, nY);
}

void MainWindow::updateActors()
{
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
        QPixmap pixmap_portrait(":/graphics/0prom_small.png");
        QGraphicsView* portraitView = new QGraphicsView;
        portrait->setForegroundBrush(pixmap_portrait);
        portraitView->setSceneRect(0,0,150,150);
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


void MainWindow::on_PortraitView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

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
    playerCount_ = playerCount;
    playerSpecs_ = playerSpecs;
}
