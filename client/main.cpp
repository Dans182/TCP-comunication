#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationDisplayName("Cliente");
    Widget w;
    w.show();

    return app.exec();
}
