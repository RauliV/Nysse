#include "settingsdialog.hh"
#include "mainwindow.h"
#include "setboard.hh"
#include "ui_mainwindow.h"
#include "QTime"
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
    timer->setInterval(1000);

    connect(timer, &QTimer::timeout, map_scene, &QGraphicsScene::advance);

    connect(timer, &QTimer::timeout, this, &MainWindow::updateActors);

    ui->travelTimeLcd->setPalette(Qt::red);
    eTime_.start();
    connect(timer, &QTimer::timeout, this, &MainWindow::tickClock);
}


void MainWindow::tickClock()
{
    int tSeconds = eTime_.elapsed()/1000;
    int minutes = tSeconds/60;
    int seconds = tSeconds % 60;
    minutes = minutes % 60;
    std::string minutesStr = "";
    std::string secondsStr = "";


    //muotoillaan näyttö halutunlaiseksi
    if (minutes<10)
    {
        minutesStr = "0"+std::to_string(minutes);
    }
    else
    {
        minutesStr = std::to_string(minutes);
    }

    if (seconds<10)
    {
        secondsStr = "0"+std::to_string(seconds);
    }
    else
    {
        secondsStr = std::to_string(seconds);
    }

    QString elaplsedTime = QString::fromStdString(minutesStr +":" +secondsStr);
    ui->travelTimeLcd->display(elaplsedTime);
    emit tick();
}

void MainWindow::mouseClicked(std::shared_ptr<Interface::IStop> place)
{
    qDebug() << place->getName();
    ui->DestinationValueLabel->setText(place->getName());
}

void MainWindow::newTurn(std::shared_ptr<Player> &player)
{
    playerInTurn_ = player;
    timer->stop();
    ui->WithdrawPushButton_2->setEnabled(true);
    ui->NysseCheckBox->setEnabled(true);
    ui->WalkCheckBox->setEnabled(true);
    ui->TaxiCheckBox->setEnabled(true);
    ui->ScooterCheckBox->setEnabled(true);
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
    LocationItem* nPlace = new LocationItem( nullptr, locX, locY, 2, img, place);
    QObject::connect(nPlace,&LocationItem::itemClicked, this, &MainWindow::mouseClicked);
    places_.push_back(nPlace);
    map_scene->addItem(nPlace);
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
    this->setFixedWidth((820 + 150*playerCount_)-150);
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
    setBoard(playerSpecs_);
    createPlayerPortraits();
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

void MainWindow::on_travelTimeLcd_overflow(int lkm)
{
    lkm ++;
    ui->travelTimeLcd->display(lkm);
    timer->intervalAsDuration();
}

void MainWindow::on_MovePushButton_clicked()
{
    qDebug() << "Liikutaan " + ui->DestinationValueLabel->text();
    timer->start(tick_);
    ui->MovePushButton->setDisabled(true);
    ui->WithdrawPushButton_2->setDisabled(true);
}

void MainWindow::on_WalkCheckBox_toggled(bool checked)
{
    if(checked)
    {
        ui->NysseCheckBox->setCheckState(Qt::Unchecked);
        ui->TaxiCheckBox->setCheckState(Qt::Unchecked);
        ui->ScooterCheckBox->setCheckState(Qt::Unchecked);
        if(ui->DestinationValueLabel->text().size()>0)
        {
            ui->MovePushButton->setEnabled(true);
            if(std::dynamic_pointer_cast<Bar>(destination_) != 0)
            {
                ui->EnterBarPushButton->setEnabled(true);
            }
        }
    }

}

void MainWindow::on_NysseCheckBox_toggled(bool checked)
{
    if(checked)
    {
        ui->WalkCheckBox->setCheckState(Qt::Unchecked);
        ui->TaxiCheckBox->setCheckState(Qt::Unchecked);
        ui->ScooterCheckBox->setCheckState(Qt::Unchecked);
        if(ui->DestinationValueLabel->text().size()>0)
        {
            ui->MovePushButton->setEnabled(true);
            if(std::dynamic_pointer_cast<Bar>(destination_) != 0)
            {
                ui->EnterBarPushButton->setEnabled(true);
            }
        }
    }
}

void MainWindow::on_TaxiCheckBox_toggled(bool checked)
{
    if(checked)
    {
        ui->NysseCheckBox->setCheckState(Qt::Unchecked);
        ui->WalkCheckBox->setCheckState(Qt::Unchecked);
        ui->ScooterCheckBox->setCheckState(Qt::Unchecked);
        if(ui->DestinationValueLabel->text().size()>0)
        {
            ui->MovePushButton->setEnabled(true);
            if(std::dynamic_pointer_cast<Bar>(destination_) != 0)
            {
                ui->EnterBarPushButton->setEnabled(true);
            }
        }
    }
}

void MainWindow::on_ScooterCheckBox_toggled(bool checked)
{
    if(checked)
    {
        ui->NysseCheckBox->setCheckState(Qt::Unchecked);
        ui->TaxiCheckBox->setCheckState(Qt::Unchecked);
        ui->WalkCheckBox->setCheckState(Qt::Unchecked);
        if(ui->DestinationValueLabel->text().size()>0)
        {
            ui->MovePushButton->setEnabled(true);
            if(std::dynamic_pointer_cast<Bar>(destination_) != 0)
            {
                ui->EnterBarPushButton->setEnabled(true);
            }
        }
    }
}

void MainWindow::on_EnterBarPushButton_clicked()
{
    timer->start(tick_);
    emit enterBar(playerInTurn_, destination_);

}

void MainWindow::on_WithdrawPushButton_2_clicked()
{
    playerInTurn_->withdrawCash(20);
}
