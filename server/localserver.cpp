#include <localserver.h>
#include <QTcpSocket>
#include <QTextStream>
#include <QDebug>

LocalServer::LocalServer(QObject *parent)
    : QTcpServer(parent)
{
   mSocket = nullptr;

   connect(this, &LocalServer::newConnection, [&](){
       mSocket = nextPendingConnection();
   });
}

void LocalServer::envia(const int &pos_x, int &pos_y)
{
    if(mSocket){
        QTextStream T(mSocket);
        T << pos_x << "\n" << pos_y;
        qDebug() << pos_x << pos_y;

        mSocket->flush();
    }
}
