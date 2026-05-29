#ifndef STATISTIC_H
#define STATISTIC_H
#include <clientfunctions.h>
#include <QMainWindow>
#include <QProcess>

namespace Ui {
class StatWindow;
}

class StatWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StatWindow(QWidget *parent = nullptr);
    ~StatWindow();

private slots:
    void on_action_triggered();

signals:
    void openWindow();

private:
    Ui::StatWindow *ui;
public:
    void UpdateWindow();
};

#endif // STATISTIC_H
