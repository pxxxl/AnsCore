#include <QApplication>
#include <QtWidgets>

extern "C"{
    #include "../src/processor/processor.h"
    #include "../src/custom/custom.h"
}
#include "../src/IO/qt_draw.h"


MyWidget* widget = nullptr;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    widget = new MyWidget;
    widget->show();

    auto pro = init_processor(BASE_MAX_X, BASE_MAX_Y);
    
    auto player1 = create_player_object(BLUE_TROOP);
    auto player2 = create_player_object(RED_TROOP);
    /*
    auto wall1 = create_obstacle_object(101);
    auto wall2 = create_obstacle_object(101);
    auto wall3 = create_obstacle_object(101);
    auto wall4 = create_obstacle_object(101);
    auto stone1 = create_obstacle_object(104);
    auto stone2 = create_obstacle_object(104);
    auto stone3 = create_obstacle_object(104);
    auto tree1 = create_obstacle_object(103);
    auto tree2 = create_obstacle_object(103);
    auto tree3 = create_obstacle_object(103);
    auto grey1 = create_obstacle_object(102);
    auto grey2 = create_obstacle_object(102);
    auto grey3 = create_obstacle_object(102);
    auto grey4 = create_obstacle_object(102);
    */
    pro->api->request_place(pro, NULL, player1, 0, 3, UP);
    pro->api->request_place(pro, NULL, player2, 18, 15, DOWN);
    /*
    pro->api->request_place(pro, NULL, wall1, 9, 3, UP);
    pro->api->request_place(pro, NULL, wall2, 12, 3, UP);
    pro->api->request_place(pro, NULL, wall3, 15, 3, UP);
    pro->api->request_place(pro, NULL, wall4, 18, 3, UP);
    pro->api->request_place(pro, NULL, stone1, 0, 12, UP);
    pro->api->request_place(pro, NULL, stone2, 0, 15, UP);
    pro->api->request_place(pro, NULL, stone3, 0, 18, UP);
    pro->api->request_place(pro, NULL, tree1, 3, 0, UP);
    pro->api->request_place(pro, NULL, tree2, 6, 0, UP);
    pro->api->request_place(pro, NULL, tree3, 6, 3, UP);
    pro->api->request_place(pro, NULL, grey1, 3, 18, UP);
    pro->api->request_place(pro, NULL, grey2, 6, 18, UP);
    pro->api->request_place(pro, NULL, grey3, 9, 18, UP);
    pro->api->request_place(pro, NULL, grey4, 12, 18, UP);
    */
   

    InfoEffect infoEffect[100];
    int lengthEffect = 0;
    InfoMove infoMove[100];
    int lengthMove = 0;

    QTimer* timer = new QTimer;
    auto info = init_draw();
    int tags[8] = {101, 102, 103, 104, 101, 102, 103, 104};

    QObject::connect(timer, &QTimer::timeout, [&]() {
        static int cnter = 0;
        static int cnt = 0;
        if(cnt == 0){
            //pro->api->request_load_static_sustaining_effect(pro, cnter++%BASE_MAX_X, 0, tags, 8, 0);
            pro->step(pro);
            auto anime = pro->export_anime_data(pro);
            anime_repack(anime.anime_pack, anime.anime_pack_size, infoEffect, &lengthEffect, infoMove, &lengthMove);
            import_info(info, infoMove, lengthMove, infoEffect, lengthEffect);
            refresh(*info, cnt);
        }else{
            refresh(*info, cnt);
        }
        cnt++;
        if(cnt == 8){
            cnt = 0;
        }
    });
    timer->start(10);
    return app.exec();
}
