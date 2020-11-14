#include "creategame.hh"
#include "city.hh"
#include "graphics/simplemainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);
    CourseSide::SimpleMainWindow window;

    window.show();
    std::shared_ptr<Interface::ICity> pointer;
    //pointer = Interface::createGame();
    //pointer->startGame();
    return a.exec();

}
