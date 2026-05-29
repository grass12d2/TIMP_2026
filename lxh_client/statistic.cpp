#include "statistic.h"
#include "ui_statistic.h"

StatWindow::StatWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::StatWindow) {
    QStringList header;
    header << QString("Login")
           << QString("Correct answers: Task 1")
           << QString("Correct answers: Task 2")
           << QString("Correct answers: Task 3");
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setHorizontalHeaderLabels(header);
    this->UpdateWindow();
}

void StatWindow::UpdateWindow() {
    QJsonArray results = getAllStat();
    int counter = 0;
    int temp=ui->tableWidget->rowCount();
    while(temp>0)
    {       ui->tableWidget->removeRow(temp-1);
    temp--;
}
    for (auto user: results) {
        ui->tableWidget->insertRow(counter);
        ui->tableWidget->setItem(counter, 0, new QTableWidgetItem(user.toObject()["login"].toString()));
        QJsonObject tasks = user.toObject()["solved_tasks"].toObject();
        qDebug() << tasks;
        for (int i = 1; i < 4; i++) {
            //qDebug() << QString::number(i);
            //qDebug() << tasks[QString::number(i)].toInt();
            QString taskRes = QString::number(tasks[QString::number(i)].toInt());
            qDebug() << taskRes;
            ui->tableWidget->setItem(counter, i, new QTableWidgetItem(taskRes));

        }
        counter += 1;

    }
    //qDebug() << results;
    ui->tableWidget->resizeColumnsToContents();
    return;
}

StatWindow::~StatWindow()
{
    delete ui;
}


void StatWindow::on_action_triggered()
{
    reset_settings();
    // перезапуск приложения
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

