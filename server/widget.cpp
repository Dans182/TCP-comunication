#include "widget.h"
#include "ui_widget.h"
#include "localserver.h"
#include <QMessageBox>
#include <QRandomGenerator>
//#include <QTimer>

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
        emit serverOn();
    }
}

void Widget::on_enviar_clicked()
{
    pos_x = QRandomGenerator::global()->bounded(1000);
    pos_y = QRandomGenerator::global()->bounded(1000);
    mLocalServer->envia(pos_x, pos_y);
    emit newCoordinatesSended();
}

void Widget::on_quitar_clicked()
{
    close();
}

