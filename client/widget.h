#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QTcpSocket;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void setNewCoordinates(QObject *object, int pos_x, int pos_y);
    void initializationQML(int &pos_x, int &pos_y);

signals:
    void newCoordinatesReceived();

private slots:
    void on_conectar_clicked();

    void on_quitar_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *mSocket;
    QString receivedPosxPosy;
    int pos_x, pos_y;
    QStringList coordenadas;

};
#endif // WIDGET_H
