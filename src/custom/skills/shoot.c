#include "../custom.h"

void player_shoot(Object* self, void* param){
    int x = self->block->x;
    int y = self->block->y;
    int ori = self->block->orientation;
    int actual_x = x;
    int actual_y = y;
    switch(ori){
        case UP: actual_x++; actual_y-=2; break;
        case DOWN: actual_x++; actual_y+=4; break;
        case LEFT: actual_x-=2; actual_y++; break;
        case RIGHT: actual_x+=4; actual_y++; break;
    }
    int side = self->config.side == RED ? RED : BLUE;
    Object* bullet = NULL;
    bullet = create_ordinary_bullet_object(side);
    self->api->request_place(self->host, self, bullet, actual_x, actual_y, ori);
}