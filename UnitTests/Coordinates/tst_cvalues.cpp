#include <QtTest>
#include <QCoreApplication>
#include "setboard.hh"
#include "interfaces/istop.hh"
#include "city.hh"
#include "actors/player.hh"

// add necessary includes here

class cValues : public QObject
{
    Q_OBJECT

public:
    cValues();
    ~cValues();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

cValues::cValues()
{

}

cValues::~cValues()
{

}

void cValues::initTestCase()
{

}

void cValues::cleanupTestCase()
{

}

void cValues::test_case1()
{
        auto loc = getRandomLocation();

        //QVERIFY(paiva.giveDay() <= 0);
        if ((loc.giveX() > 500) or (loc.giveX() > 500 ))
        {
            QFAIL("koordinaatit menee yli laidan");
        }


}

QTEST_MAIN(cValues)

#include "tst_cvalues.moc"
