#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QPoint>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_conectar_clicked()
{
    ui->conectar->setEnabled(false);
    mSocket->connectToHost(ui->servidor->text(), ui->puerto->value());

    connect(mSocket, &QTcpSocket::readyRead, [&](){
        //recepcion de datos de servidor y transformacion a coordenadas
        QTextStream T(mSocket);
        receivedPosxPosy = T.readAll();
        ui->listWidget->addItem(receivedPosxPosy);
        coordenadas = receivedPosxPosy.split(',');
        emit newCoordinatesReceived();
        for (int i = 0; i < coordenadas.size(); i++) {
            pos_x = coordenadas[0].toInt();
            pos_y = coordenadas[1].toInt();
        }

        //inicialización del QML
        QQmlEngine engine;
        QQmlComponent component(&engine, QUrl::fromLocalFile("/home/userti/Repos QT/TCPServer/client/client.qml"));
        QObject *object = component.create();
        QObject *child = object->children()[1];
        child->setProperty("x", pos_x);
        child->setProperty("y", pos_y);
        child->startTimer(2000, &mSocket);

    });
}

void Widget::on_quitar_clicked()
{
    close();
}

