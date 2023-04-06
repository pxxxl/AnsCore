#include "../include/qt_graphic_drive.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MeshWidget meshWidget;
    meshWidget.setWindowTitle("MeshWidget");
    meshWidget.setFixedSize(640, 360);
    meshWidget.show();

    // Test refresh() method
    Info info = { nullptr, 0, nullptr, 0 };
    meshWidget.refresh(info, 0);

    return app.exec();
}
