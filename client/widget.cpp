#include "widget.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickWindow>
#include <QQmlProperty>
#include <QPoint>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QString receivedPosxPosy;
        int pos_x, pos_y;
        QTextStream T(mSocket);
        receivedPosxPosy = T.readAll();
        ui->listWidget->addItem(receivedPosxPosy);
        qDebug() << "receivedPosxPosy" << receivedPosxPosy;
        QStringList coordenadas = receivedPosxPosy.split(',');
        qDebug() << "coorde" << coordenadas << coordenadas[0] << coordenadas[1];
        QList<QPoint> puntos;
        for (int i = 0; i < coordenadas.size(); i++) {
            pos_x = coordenadas[0].toInt();
            pos_y = coordenadas[1].toInt();
            puntos.append(QPoint(pos_x, pos_y));
            qDebug() << pos_x << pos_y;
        }
        //qDebug() << xx << yy;
        //                for (int i = 0; i < puntos.size(); i++) {
        //                    qDebug() << puntos[i].x() << "," << puntos[i].y();
        //                }

        //                return 0;
        //pos_x = receivedPosxPosy[0];
        //pos_y = receivedPosxPosy[1];
        QQmlEngine engine;
        QQmlComponent component(&engine, QUrl::fromLocalFile("/home/userti/Repos QT/TCPServer/client/client.qml"));
        QObject *object = component.create();
        object->findChild<QObject*>("miTexto");
        //QPoint position = (pos_x, pos_y);
        //qDebug() << object;
        object->setProperty("x", pos_x);
        qDebug() << "x" << pos_x << pos_y;
        object->setProperty("y", pos_y);




        //QQmlProperty(object, "width").write(500);


        //        component.create();
        //        qDebug() << "1";
        //        if(component.create()){
        //            qDebug() << "2";
        //            component.disconnect();
        //            qDebug() << "3";
        //            component.create();
        //            qDebug() << "4";
        //        };
        //        qDebug() << "5";
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

