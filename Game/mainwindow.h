#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "interfaces/iactor.hh"
#include "interfaces/istop.hh"
#include "actoritem.hh"
#include "staticitem.hh"
#include "actors/player.hh"
#include "graphics/simpleactoritem.hh"

#include <QGraphicsView>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QElapsedTimer>
//#include <iostream>
#include <memory>
#include <QVector>
#include <map>
#include <QDebug>

namespace Ui {

class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    virtual ~MainWindow();

    void setSize(int w, int h);
    void setTick(int t);
    void setTimer();

    //Function to add buses and players to the map
    void addActor(int locX, int locY, int type = 0, std::shared_ptr<Interface::IActor> actor = nullptr);
    //Function to add bars, atms and stops to the map
    void addStaticItem(int locX, int locY, std::shared_ptr<Interface::IStop> place = nullptr);
    void updateCoords(int nX, int nY);
    //Function to update item positions on the map
    void updateActors();
    //Sets the background map
    void setPicture(QImage &img);
    void createPlayerPortraits();
    //Loads icons for items and assigns pointers to them
    void loadImages();
    void tickClock();

signals:
    void gameStarted();





private slots:

    //Opens settings dialog
    void on_SettingsButton_clicked();
    //Starts gameclock and the game
    void on_StartButton_clicked();
    //gets information from settings dialog
    void savePlayerInfo(int playerCount, std::vector<std::pair<std::string, std::string>> playerSpecs);

    std::shared_ptr<QImage> getActorImage(std::shared_ptr<Interface::IActor> actor = nullptr);
    std::shared_ptr<QImage> getPlaceImage(std::shared_ptr<Interface::IStop> place = nullptr);
   // void mouseClicked(std::shared_ptr<Interface::IStop> place);
    void on_travelTimeLcd_overflow(int lkm);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *portrait;
    QGraphicsScene *map_scene;
    QScrollArea *map;
    QTimer *timer;
    QVector<ActorItem*> actors_;
    QVector<StaticItem*> places_;
    CourseSide::SimpleActorItem* last_;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms

    int playerCount_;
    std::vector<std::pair<std::string, std::string>> playerSpecs_;

    //actor images
    std::shared_ptr<QImage> nysseImg_;
    std::shared_ptr<QImage> taxiImg_;
    std::shared_ptr<QImage> walkImg_;
    std::shared_ptr<QImage> scooterImg_;
    //place images
    std::shared_ptr<QImage> barImg_;
    std::shared_ptr<QImage> atmImg_;
    std::shared_ptr<QImage> stopImg_;

    QElapsedTimer eTime_;




};

 //namespace
#endif // SIMPLEMAINWINDOW_HH
