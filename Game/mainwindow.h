#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "interfaces/iactor.hh"
#include "actoritem.hh"
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

//#include"game_engine.h"
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

    void addActor(int locX, int locY, int type = 0, QString iconPath = "", std::shared_ptr<Interface::IActor> actor = nullptr);
    void updateCoords(int nX, int nY);
    void updateActors();
    void setPicture(QImage &img);
    void createPlayerPortraits();

signals:
    void gameStarted();


private slots:

    void on_PortraitView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_SettingsButton_clicked();

    void on_StartButton_clicked();

    void savePlayerInfo(int playerCount, std::vector<std::pair<std::string, std::string>> playerSpecs);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *portrait;
    QGraphicsScene *map_scene;
    QScrollArea *map;
    QTimer *timer;
    QVector<ActorItem*> actors_;
    CourseSide::SimpleActorItem* last_;

    int width_ = 500; //pxls
    int height_ = 500;
    int tick_ = 500; //ms

    int playerCount_;
    std::vector<std::pair<std::string, std::string>> playerSpecs_;
};

 //namespace
#endif // SIMPLEMAINWINDOW_HH
