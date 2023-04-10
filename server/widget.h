#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "localserver.h"

namespace Ui {
class Widget;
}

class LocalServer;

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void newCoordinatesSended();
    void serverOn();

private slots:
    void on_iniciar_clicked();

    void on_enviar_clicked();

    void on_quitar_clicked();

private:
    Ui::Widget *ui;
    LocalServer *mLocalServer;
    int pos_x;
    int pos_y;
};
#endif // WIDGET_H
