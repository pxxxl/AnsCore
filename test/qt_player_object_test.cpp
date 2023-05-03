#include <QApplication>
#include <QtWidgets>
#include "fmt/core.h"

extern "C"{
    #include "../src/processor/processor.h"
    #include "../src/custom/custom.h"
    #include "../src/random.h"
}
#include "../src/IO/qt_draw.h"



TWidget* widget = nullptr;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setKeyboardInputInterval(10);
    widget = new TWidget;
    widget->show();
    auto pro = init_processor(BASE_MAX_X, BASE_MAX_Y);

    auto player1 = create_player_object(BLUE);
    auto player2 = create_player_object(RED);
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
    Player players[2];
    SkillFunc skill_map[1000];
    int skill_num = 0;
    get_skill_map(skill_map, &skill_num);
    pro->fillin_skill_map(pro, skill_map, skill_num);

    QTimer* timer = new QTimer;
    auto info = init_draw();
    int tags[8] = {101, 102, 103, 104, 101, 102, 103, 104};

    QObject::connect(timer, &QTimer::timeout, [&]() {
        static int cnter = 0;
        static int cnt = 0;
        static int box_cnt = 0;
        static int box_cnt_2 = 100;
        if(cnt == 0){
            //pro->api->request_load_static_sustaining_effect(pro, cnter++%BASE_MAX_X, 0, tags, 8, 0);
            if(box_cnt == 0){
                unsigned randx = randint() % 38;
                unsigned randy = randint() % 21;
                place_skill_box(pro, randx, randy);
            }
            if(box_cnt_2 == 0){
                unsigned randx = randint() % 38;
                unsigned randy = randint() % 21;
                place_bullet_box(pro, randx, randy);
            }
            widget->key_step();
            pro->step(pro);
            
            auto anime = pro->export_anime_data(pro);
            players[0].hp=anime.player_display_pack[0].hp;
            players[1].hp=anime.player_display_pack[1].hp;
            players[0].skillNum=anime.player_display_pack[0].skill_num;
            players[1].skillNum=anime.player_display_pack[1].skill_num;
            for(int i = 0 ;i < 6;i++){
                players[0].skills[i]=anime.player_display_pack[0].skill_tag[i];
                players[1].skills[i]=anime.player_display_pack[1].skill_tag[i];
            }
            players[0].selectSkill=anime.player_display_pack[0].skill_choice;
            players[1].selectSkill=anime.player_display_pack[1].skill_choice;

            anime_repack(anime.anime_pack, anime.anime_pack_size, infoEffect, &lengthEffect, infoMove, &lengthMove);
            import_info(info, infoMove, lengthMove, infoEffect, lengthEffect);
            renew_status(players);
            refresh(*info, cnt);
            box_cnt++;
            box_cnt_2++;

            if(box_cnt == 500){
                box_cnt = 0;
            }
            if(box_cnt_2 == 200){
                box_cnt_2 = 0;
            }
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
