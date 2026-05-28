QT += testlib sql network
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17

INCLUDEPATH += /Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server

TEMPLATE = app

SOURCES += \
    tst_funcforserver_test.cpp \
    /Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task1.cpp \
    /Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task2.cpp \
    /Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task3.cpp \
    /Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task4.cpp

HEADERS += \
    /Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task1.h \
    /Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task2.h \
    /Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task3.h \
    /Users/luongduc/Documents/TIMP_2026/TechProg_MPU-main/lvd_server/task4.h