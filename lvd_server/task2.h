// #ifndef TASK2_H
// #define TASK2_H
// #include <QVariant>
// #include <QRandomGenerator>
// #include <QtMath>
// #include <vector>
// #include <QString>

// QVariantMap Findtheminimumpoint();
// QString test_result(std::vector<int> x, std::vector<int> y);

// #endif // TASK2_H
#ifndef TASK2_H
#define TASK2_H

#include <QVariantMap>
#include <vector>

QVariantMap Findtheminimumpoint();

double globalmin(const std::vector<int>& c);

#endif // TASK2_H