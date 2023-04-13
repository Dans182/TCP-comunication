#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("Servidor");
    Widget w;
    w.show();
    w.on_iniciar_clicked();

    return a.exec();
}
