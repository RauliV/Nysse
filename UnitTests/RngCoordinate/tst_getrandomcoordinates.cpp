#include <QtTest>

// add necessary includes here

class getRandomCoordinates : public QObject
{
    Q_OBJECT

public:
    getRandomCoordinates();
    ~getRandomCoordinates();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

getRandomCoordinates::getRandomCoordinates()
{

}

getRandomCoordinates::~getRandomCoordinates()
{

}

void getRandomCoordinates::initTestCase()
{

}

void getRandomCoordinates::cleanupTestCase()
{

}

void getRandomCoordinates::test_case1()
{

}

QTEST_APPLESS_MAIN(getRandomCoordinates)

#include "tst_getrandomcoordinates.moc"
