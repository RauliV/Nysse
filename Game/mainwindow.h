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
#include <iostream>
#include <memory>
#include <QVector>
#include <map>

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

    void addActor(int locX, int locY, int type = 0, std::shared_ptr<Interface::IActor> actor = nullptr);
    void addStaticItem(int locX, int locY, std::shared_ptr<Interface::IStop> place = nullptr);
    void updateCoords(int nX, int nY);
    void updateActors();
    void setPicture(QImage &img);
    void createPlayerPortraits();
    void loadImages();

signals:
    void gameStarted();


private slots:

    void on_PortraitView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_SettingsButton_clicked();

    void on_StartButton_clicked();

    void savePlayerInfo(int playerCount, std::vector<std::pair<std::string, std::string>> playerSpecs);

    std::shared_ptr<QImage> getImage(std::shared_ptr<Interface::IActor> actor = nullptr, std::shared_ptr<Interface::IStop> place = nullptr);



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



};

 //namespace
#endif // SIMPLEMAINWINDOW_HH
