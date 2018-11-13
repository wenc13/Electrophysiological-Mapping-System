#include <QApplication>
#include "SBMEMainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    SBMEMainWindow MainWindow;
    MainWindow.show();
    return app.exec();
}
