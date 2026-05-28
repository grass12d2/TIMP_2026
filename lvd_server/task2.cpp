#include "task2.h"

#include <QRandomGenerator>
#include <QString>
#include <QVariantMap>

#include <vector>
#include <cmath>
#include <limits>

static const int CoeffCount = 5;

// Генерация случайного целого числа
static int randomIntTask2(int min, int max)
{
    return QRandomGenerator::global()->bounded(min, max + 1);
}

// Форматирование числа: ровно 4 знака после точки
static QString formatNumber(double value)
{
    if (std::abs(value) < 0.00005)
    {
        value = 0.0;
    }

    return QString::number(value, 'f', 4);
}

// Генерация коэффициентов функции:
// f(x) = ax^4 + bx^3 + cx^2 + dx + e
// Важно: a > 0, чтобы функция имела минимум.
static std::vector<int> equation()
{
    std::vector<int> coeffs(CoeffCount);

    coeffs[0] = randomIntTask2(1, 5);      // a > 0
    coeffs[1] = randomIntTask2(-5, 5);     // b
    coeffs[2] = randomIntTask2(-5, 5);     // c
    coeffs[3] = randomIntTask2(-5, 5);     // d
    coeffs[4] = randomIntTask2(-5, 5);     // e

    return coeffs;
}

// Значение функции:
// f(x) = ax^4 + bx^3 + cx^2 + dx + e
static double functionValue(const std::vector<int>& c, double x)
{
    return c[0] * std::pow(x, 4)
         + c[1] * std::pow(x, 3)
         + c[2] * std::pow(x, 2)
         + c[3] * x
         + c[4];
}

// Производная функции:
// f'(x) = 4ax^3 + 3bx^2 + 2cx + d
static double derivativeValue(const std::vector<int>& c, double x)
{
    return 4.0 * c[0] * x * x * x
         + 3.0 * c[1] * x * x
         + 2.0 * c[2] * x
         + c[3];
}

// Один запуск метода градиентного спуска
static double gradientDescentFromStart(const std::vector<int>& c, double start)
{
    double x = start;
    double learningRate = 0.001;

    for (int i = 0; i < 200000; ++i)
    {
        double grad = derivativeValue(c, x);

        if (std::abs(grad) < 0.0000001)
        {
            break;
        }

        double nextX = x - learningRate * grad;

        // Защита от переполнения и ухода слишком далеко
        if (!std::isfinite(nextX) || std::abs(nextX) > 1000.0)
        {
            break;
        }

        // Если значение функции ухудшается, уменьшаем шаг
        if (functionValue(c, nextX) > functionValue(c, x))
        {
            learningRate *= 0.5;
        }
        else
        {
            x = nextX;
        }

        if (learningRate < 0.0000000001)
        {
            break;
        }
    }

    return x;
}

// Основная функция поиска точки минимума.
// Используем несколько стартовых точек, чтобы результат был устойчивее.
double globalmin(const std::vector<int>& c)
{
    std::vector<double> starts = {-10.0, -5.0, -2.0, 0.0, 2.0, 5.0, 10.0};

    double bestX = starts[0];
    double bestValue = std::numeric_limits<double>::infinity();

    for (double start : starts)
    {
        double currentX = gradientDescentFromStart(c, start);
        double currentValue = functionValue(c, currentX);

        if (currentValue < bestValue)
        {
            bestValue = currentValue;
            bestX = currentX;
        }
    }

    return bestX;
}

// Красивый вывод многочлена
static QString polynomialText(const std::vector<int>& c)
{
    QString text;

    text += QString::number(c[0]) + "x^4";

    if (c[1] >= 0)
        text += "+";
    text += QString::number(c[1]) + "x^3";

    if (c[2] >= 0)
        text += "+";
    text += QString::number(c[2]) + "x^2";

    if (c[3] >= 0)
        text += "+";
    text += QString::number(c[3]) + "x";

    if (c[4] >= 0)
        text += "+";
    text += QString::number(c[4]);

    text += "=0";

    return text;
}

// Функция генерации задания для клиента
QVariantMap Findtheminimumpoint()
{
    QVariantMap task;

    std::vector<int> coeffs = equation();

    double result = globalmin(coeffs);

    task["text"] = QString("Найдите точку минимума функции, используя метод градиентный спуск:\n%1")
                       .arg(polynomialText(coeffs));

    task["answer"] = formatNumber(result);

    return task;
}