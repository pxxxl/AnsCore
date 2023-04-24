#include <QApplication>
#include <QtWidgets>
#include "../src/IO/draw.h"
#include "../src/IO/qt_draw.h"

void gen_bricks(InfoEffect* infoeffect, int* lengthEffect){
    *lengthEffect = 11;
    for(int i = 0; i < 10; i++){
        infoeffect[i].tag = 101;
        infoeffect[i].x = i * 3;
        infoeffect[i].y = 2 * 3;
    }
    infoeffect[10].tag = 205;
    infoeffect[10].x = 3 * 3;
    infoeffect[10].y = 1;
}
void gen_bricks_gc(InfoEffect** infoeffect){
    
}

MyWidget* widget = nullptr;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    widget = new MyWidget;
    widget->show();

    InfoEffect infoEffect[100];
    int lengthEffect;
    InfoMove infoMove[100];
    int lengthMove;
    gen_bricks(infoEffect, &lengthEffect);

    QTimer* timer = new QTimer;
    auto info = init_draw();
    import_info(info, NULL, 0, infoEffect, lengthEffect);
    refresh(*info, 0);
    /*
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
    */
    return app.exec();
}
