#include "../include/qt/qt_graphic_drive.h"
#include "../include/draw.h"
#include <QApplication>
#include <QtWidgets>

MyWidget* widget = nullptr;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    widget = new MyWidget;
    widget->show();

    QTimer* timer = new QTimer;
    auto info = init_draw();
    QObject::connect(timer, &QTimer::timeout, [&]() {
        static int cnt = 0;
        if(cnt == 0){
            import_info(info, NULL, 0, NULL, 0);
            refresh(*info, cnt);
        }else{
            refresh(*info, cnt);
        }
        cnt++;
    });
    timer->start(100);
    return app.exec();
}
