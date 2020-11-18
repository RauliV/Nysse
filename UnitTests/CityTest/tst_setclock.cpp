#include <QtTest>
#include <QCoreApplication>

// add necessary includes here

class setClock : public QObject
{
    Q_OBJECT

public:
    setClock();
    ~setClock();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

setClock::setClock()
{
    //QCOMPARE(clock())
}

setClock::~setClock()
{

}

void setClock::initTestCase()
{

}

void setClock::cleanupTestCase()
{

}

void setClock::test_case1()
{

}

QTEST_MAIN(setClock)

#include "tst_setclock.moc"
