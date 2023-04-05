#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QTcpServer>

class QTcpSocket;

class LocalServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit LocalServer(QObject *parent = 0);
    void envia(const int &pos_x, int &pos_y);

private:
    QTcpSocket *mSocket;
};
#endif // LOCALSERVER_H
