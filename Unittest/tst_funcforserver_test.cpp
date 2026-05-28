#include <QtTest>
#include "/Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task1.h"
#include "/Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task2.h"
#include "/Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task3.h"
#include "/Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task4.h"

// add necessary includes here

class FuncForServer_Test : public QObject
{
    Q_OBJECT

public:
    FuncForServer_Test();
    ~FuncForServer_Test();

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();

};

FuncForServer_Test::FuncForServer_Test()
{

}

FuncForServer_Test::~FuncForServer_Test()
{

}

void FuncForServer_Test::test_case1()
{
    std::vector<int> x = {2, 3, 5, 7};
    std::vector<int> y = {7, 9, 1, 7};

    QString res1 = test_result(x, y);

    QString value1 =
        "7.0000 3.4091 0.0000 -1.4091; "
        "9.0000 -0.8182 -4.2273 1.3182; "
        "1.0000 -1.9091 3.6818 -0.6136";

    QVERIFY2(res1 == value1, "task_1_false");
}

void FuncForServer_Test::test_case2()
{
    // f(x) = x^4 - 4x
    // f'(x) = 4x^3 - 4
    // Минимум находится около x = 1

    std::vector<int> x = {1, 0, 0, -4, 0};

    double res2 = globalmin(x);
    double value2 = 1.0000;

    QVERIFY2(std::abs(res2 - value2) < 0.01, "task_2_false");
}


void FuncForServer_Test::test_case3()
{
    QString pass = "timp";
    QString res3 = test_sha_256(pass);

    QString value3 = "7B3CDDE1ADB6FA345620A7E709050E4CC9B70732EBBF1FD27DE4B70102E344E8";

    QVERIFY2(res3.toUpper() == value3, "task_3_false");
}

void FuncForServer_Test::test_case4(){
    QString text = "dwgwziyqgp";
    QString key = "dwgw";
    QString res4 = vigenere( key, text);
    QString value4 = "grmrbddljk";
    QVERIFY2 (res4 == value4,"task_4_false");
}

QTEST_APPLESS_MAIN(FuncForServer_Test)

#include "tst_funcforserver_test.moc"
