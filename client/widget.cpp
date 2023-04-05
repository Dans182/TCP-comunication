#include "widget.h"
#include "qquickitem.h"
#include "ui_widget.h"
#include <QTcpSocket>
#include <QTextStream>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mSocket = new QTcpSocket(this);

    connect(mSocket, &QTcpSocket::readyRead, [&](){
        QString receivedPosxPosy, pos_x, pos_y;
        QTextStream T(mSocket);
        receivedPosxPosy = T.readAll();
        ui->listWidget->addItem(receivedPosxPosy);
        QStringList coorde = receivedPosxPosy.split('\n');
        pos_x = receivedPosxPosy[0];
        pos_y = receivedPosxPosy[1];
        QQmlEngine engine;
        QQmlComponent component(&engine, QUrl::fromLocalFile("/home/userti/Repos QT/TCPServer/client/client.qml"));
        QObject *object = component.create();

        QQuickItem *item = qobject_cast<QQuickItem*>(object);
        int width = item->width();  // width = 200
//        if(object)


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

