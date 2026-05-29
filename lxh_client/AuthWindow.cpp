#include "AuthWindow.h"
#include "ui_AuthWindow.h"

AuthWindow::AuthWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::AuthWindow) {
    mWindow = new MainWindow();
    connect(mWindow, &MainWindow::openWindow, this, &MainWindow::show);
    ui->setupUi(this);
    ui->passwordLabel_2->setVisible(false);
    ui->passwordTextEdit_2->setVisible(false);
    ui->EmailLabel->setVisible(false);
    ui->EmailTextEdit->setVisible(false);
}

AuthWindow::~AuthWindow() {
    delete ui;
}


void AuthWindow::on_pushButton_clicked() {
    QString loginString = ui->LoginTextEdit->text();
    QString passwordString = ui->PasswordTextEdit->text();
    QString emailString = ui->EmailTextEdit->text();
    if (ui->passwordLabel_2->isVisible()) {
        QString passwordVerifyString = ui->passwordTextEdit_2->text();
        if (passwordString != passwordVerifyString) {
            QMessageBox::critical(this, "Ошибка", "Пароли не совпадают");
            return;
        }
        bool status = register_account(loginString, passwordString, emailString);
        if (!status) {
            QMessageBox::information(this, "Регистрация", "Регистрация не удалась.");
            return;
        }
        else {
            QMessageBox::information(this, "Регистрация", "Вы успешно зарегистрировались!");
        }
    } else {
        bool status = login(loginString, passwordString);
        qDebug() << status;
        if (!status) {
            QMessageBox::information(this, "Авторизация", "Введён неправильный логин или пароль");
            return;
        }
        else {
            QMessageBox::information(this, "Авторизация", "Вы успешно авторизовались!");
        }
    }
    mWindow->update_data();
    mWindow->show();
    this->close();
}

void AuthWindow::on_ChangeModeButton_clicked() {
    // если мы в режиме регистрации
    if (not ui->passwordLabel_2->isVisible()) {
        ui->passwordLabel_2->setVisible(true);
        ui->passwordTextEdit_2->setVisible(true);
        ui->EmailLabel->setVisible(true);
        ui->EmailTextEdit->setVisible(true);
        ui->ChangeModeButton->setText("Авторизоваться");
        ui->ChangeModeLabel->setText("Уже есть аккаунт?");
    }
    // если в режиме авторизации
    else {
        ui->passwordLabel_2->setVisible(false);
        ui->passwordTextEdit_2->setVisible(false);
        ui->EmailLabel->setVisible(false);
        ui->EmailTextEdit->setVisible(false);
        ui->ChangeModeButton->setText("Зарегистрироваться");
        ui->ChangeModeLabel->setText("Нет аккаунта?");
    }
}

