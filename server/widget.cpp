#include "widget.h"
#include "ui_widget.h"
#include "localserver.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>
#include <QLineEdit>
#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlComponent>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mLocalServer = new LocalServer(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_iniciar_clicked()
{
    if (!mLocalServer->listen(QHostAddress::Any, ui->puerto->value())) {
        QMessageBox::critical(this, "Error", mLocalServer->errorString());
    }
    else {
        QMessageBox::information(this, "servidor", "Iniciado...");
        ui->iniciar->setEnabled(false);
    }
}

void Widget::on_enviar_clicked()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
    timer->start(1000);
    pos_x = QRandomGenerator::global()->bounded(1000);
    pos_y = QRandomGenerator::global()->bounded(1000);
    mLocalServer->envia(pos_x, pos_y);
}

void Widget::on_quitar_clicked()
{
    close();
}

