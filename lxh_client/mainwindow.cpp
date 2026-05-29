#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->update_data();
    tWindow = new TaskForm();
    connect(tWindow, &TaskForm::openWindow, this, &TaskForm::show);

    statWindow = new StatWindow();
    connect(statWindow, &StatWindow::openWindow, this, &StatWindow::show);
}

bool MainWindow::update_data()
{
    ui->StatLabel->setText(getStat());
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openTask(QVariantMap task) {
    int taskId = task["id"].toInt();
    QString taskText = task["text"].toString();
    tWindow->initTask(taskText, taskId);
    tWindow->show();
}


void MainWindow::on_task1_clicked()
{
    QVariantMap task = getTask(1);
    openTask(task);
}

void MainWindow::on_task2_clicked()
{
    QVariantMap task = getTask(2);
    openTask(task);
}

void MainWindow::on_task3_clicked()
{
    QVariantMap task = getTask(4);
    openTask(task);
}

void MainWindow::on_task4_clicked()
{
    QVariantMap task = getTask(3);
    openTask(task);
}

void MainWindow::on_stat_clicked(){
    statWindow->UpdateWindow();
    statWindow->show();
}

void MainWindow::on_account_exit_triggered() {
    reset_settings();
    // перезапуск приложения
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

