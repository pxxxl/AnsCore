#include "../custom.h"

void place_skill_box(Processor* pro, int x, int y){
    pro->api->request_place(pro, NULL, create_skill_box(), x, y, UP);
}

void place_bullet_box(Processor* pro, int x, int y){
    pro->api->request_place(pro, NULL, create_bullet_box(), x, y, UP);
}