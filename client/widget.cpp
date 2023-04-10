#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QPoint>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&](){
        //recepcion de datos de servidor y transformacion a coordenadas
        QString receivedPosxPosy;
        int pos_x, pos_y;
        QTextStream T(mSocket);
        receivedPosxPosy = T.readAll();
        ui->listWidget->addItem(receivedPosxPosy);
        QStringList coordenadas = receivedPosxPosy.split(',');
        QList<QPoint> puntos;
        for (int i = 0; i < coordenadas.size(); i++) {
            pos_x = coordenadas[0].toInt();
            pos_y = coordenadas[1].toInt();
            puntos.append(QPoint(pos_x, pos_y));
        }

        //inicialización del QML
        QQmlEngine engine;
        QQmlComponent component(&engine, QUrl::fromLocalFile("/home/userti/Repos QT/TCPServer/client/client.qml"));
        //inicializo la ventana.
        QObject *object = component.create();
        object->findChild<QObject *>("clientWindow");
        QObject *child = object->children()[1];
        //qDebug() << child;
        child->setProperty("x", pos_x);
        child->setProperty("y", pos_y);

    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_conectar_clicked()
{
    ui->conectar->setEnabled(false);
    mSocket->connectToHost(ui->servidor->text(), ui->puerto->value());
}

void Widget::on_quitar_clicked()
{
    close();
}

