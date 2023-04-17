#include "../include/qt_graphic_drive.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MyWidget* widget = new MyWidget;
    widget->show();

    KeyboardEventFilter* eventFilter = new KeyboardEventFilter;
    app.installEventFilter(eventFilter);

    QTimer* timer = new QTimer;
    QObject::connect(timer, &QTimer::timeout, [=]() {
        static int count = 0;
        static int refresh_count = 0;
        static Info info = { "John", 30 };
        if (count % 10 == 0)
        {
            widget->import_info(info);
            refresh_count = 0;
            info.age++;
        }
        widget->refresh();
        count++;
        refresh_count++;
        if (refresh_count >= 10)
        {
            refresh_count = 0;
            QCoreApplication::processEvents();
        }
    });
    timer->start(100);

    return app.exec();
}
