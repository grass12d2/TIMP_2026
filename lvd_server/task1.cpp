#include "task1.h"

#include <QRandomGenerator>
#include <QVariantMap>
#include <QString>

#include <vector>
#include <algorithm>
#include <cmath>

static const int Number = 4;

// Генерация случайного числа
static int randomIntSpline(int min, int max)
{
    return QRandomGenerator::global()->bounded(min, max + 1);
}

// Генерация разных значений x и сортировка по возрастанию
static std::vector<int> rand_x()
{
    std::vector<int> x;

    while (x.size() < Number)
    {
        int value = randomIntSpline(1, 9);

        if (std::find(x.begin(), x.end(), value) == x.end())
        {
            x.push_back(value);
        }
    }

    std::sort(x.begin(), x.end());
    return x;
}

// Генерация значений y
static std::vector<int> rand_y()
{
    std::vector<int> y(Number);

    for (int i = 0; i < Number; ++i)
    {
        y[i] = randomIntSpline(1, 9);
    }

    return y;
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

// Формирование текста задания
static QString topic(const std::vector<int>& x, const std::vector<int>& y)
{
    QString result;

    result += "x  ";
    for (int i = 0; i < Number; ++i)
    {
        result += QString::number(x[i]) + "  ";
    }

    result += "\n************************\n";

    result += "y  ";
    for (int i = 0; i < Number; ++i)
    {
        result += QString::number(y[i]) + "  ";
    }

    return result;
}

// Построение естественного кубического сплайна
QString test_result(std::vector<int> x, std::vector<int> y)
{
    // Сортируем точки по x, чтобы сплайн строился правильно
    std::vector<std::pair<int, int>> points;

    for (int i = 0; i < Number; ++i)
    {
        points.push_back(std::make_pair(x[i], y[i]));
    }

    std::sort(points.begin(), points.end());

    for (int i = 0; i < Number; ++i)
    {
        x[i] = points[i].first;
        y[i] = points[i].second;
    }

    int n = Number - 1; // количество интервалов

    std::vector<double> a(Number);
    std::vector<double> b(n);
    std::vector<double> c(Number);
    std::vector<double> d(n);
    std::vector<double> h(n);

    // a[i] = y[i]
    for (int i = 0; i < Number; ++i)
    {
        a[i] = y[i];
    }

    // h[i] = x[i+1] - x[i]
    for (int i = 0; i < n; ++i)
    {
        h[i] = x[i + 1] - x[i];
    }

    // alpha для системы уравнений
    std::vector<double> alpha(Number, 0.0);

    for (int i = 1; i < n; ++i)
    {
        alpha[i] = 3.0 * ((a[i + 1] - a[i]) / h[i]
                   - (a[i] - a[i - 1]) / h[i - 1]);
    }

    // Метод прогонки для нахождения коэффициентов c[i]
    std::vector<double> l(Number);
    std::vector<double> mu(Number);
    std::vector<double> z(Number);

    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    for (int i = 1; i < n; ++i)
    {
        l[i] = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    // Условие естественного сплайна: c[n] = 0
    l[n] = 1.0;
    z[n] = 0.0;
    c[n] = 0.0;

    for (int j = n - 1; j >= 0; --j)
    {
        c[j] = z[j] - mu[j] * c[j + 1];

        b[j] = (a[j + 1] - a[j]) / h[j]
               - h[j] * (c[j + 1] + 2.0 * c[j]) / 3.0;

        d[j] = (c[j + 1] - c[j]) / (3.0 * h[j]);
    }

    // Ответ в формате:
    // a b c d; a b c d; a b c d
    QString result;

    for (int i = 0; i < n; ++i)
    {
        result += formatNumber(a[i]) + " "
                + formatNumber(b[i]) + " "
                + formatNumber(c[i]) + " "
                + formatNumber(d[i]);

        if (i != n - 1)
        {
            result += "; ";
        }
    }

    return result;
}

// Функция генерации задания для клиента
QVariantMap get_result()
{
    QVariantMap task;

    std::vector<int> x = rand_x();
    std::vector<int> y = rand_y();

    task["text"] = QString("Постройте естественный сплайн для функции интерполяции:\n%1")
                       .arg(topic(x, y));

    task["answer"] = test_result(x, y);

    return task;
}