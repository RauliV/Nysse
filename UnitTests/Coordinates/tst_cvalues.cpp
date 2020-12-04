#include <QtTest>
#include <QCoreApplication>

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

}

QTEST_MAIN(cValues)

#include "tst_cvalues.moc"
