#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QQmlEngine>
#include <QQmlComponent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);
}

Widget::~Widget() //destructor
{
    delete ui;
}

void Widget::setNewCoordinates(QObject *object, int &pos_x, int &pos_y){
    QObject *childText = object->children()[1];

    if(childText->property("x") == 0 &&
            childText->property("y") == 0)
    {
        qDebug() << childText->property("x").toInt() << pos_x;
        childText->setProperty("x", pos_x);
        childText->setProperty("y", pos_y);
        qDebug() << "esto es un if";
        //            setNewCoordinates(object, pos_x, pos_y);
    }
    else
    {
        qDebug() << childText->property("x").toInt() << pos_x;
        qDebug() << "esto es un else";
    }
};


void Widget::initializationQML(){
    QQmlEngine engine;
    QQmlComponent component(&engine, QUrl::fromLocalFile("/home/userti/Repos QT/TCPServer/client/client.qml"));
    QObject *object = component.create();
    setNewCoordinates(object, pos_x, pos_y);
};

void Widget::on_conectar_clicked() //botón conectar
{
    ui->conectar->setEnabled(false);
    mSocket->connectToHost("localhost", 12345);

    connect(mSocket, &QTcpSocket::readyRead, [&](){
        //recepcion de coordenadas desde servidor y transformacion a coordenadas pos_x y pos_y
        QTextStream T(mSocket);
        receivedPosxPosy = T.readAll();
        ui->listWidget->addItem(receivedPosxPosy);
        coordenadas = receivedPosxPosy.split(',');
        //        emit newCoordinatesReceived();
        for (int i = 0; i < coordenadas.size(); i++) {
            pos_x = coordenadas[0].toInt();
            pos_y = coordenadas[1].toInt();
        }
        //inicialización del QML
        initializationQML();
    });
}
void Widget::on_quitar_clicked() //botón cerrar
{
    close();
}

