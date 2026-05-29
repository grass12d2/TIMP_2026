#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>
#include <clientfunctions.h>

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(QWidget *parent = nullptr);
    ~TaskForm();
    void initTask(QString taskText, int taskId);

private slots:

    void on_TryButton_clicked();

    void on_LoseButton_clicked();

signals:
    void openWindow();

private:
    Ui::TaskForm *ui;
    int taskId;
};

#endif // TASKFORM_H
