#include "../custom.h"

void player_shoot(Object* self, int type_id){
    int x = self->block->x;
    int y = self->block->y;
    int ori = self->block->orientation;
    int actual_x = x;
    int actual_y = y;
    switch(ori){
        case UP: actual_x++; actual_y--; break;
        case DOWN: actual_x++; actual_y+=3; break;
        case LEFT: actual_x--; actual_y++; break;
        case RIGHT: actual_x+=3; actual_y++; break;
    }
    int side = self->config.side == RED_TROOP ? RED_BULLET : BLUE_BULLET;
    Object* bullet = NULL;
    if(type_id == 106){
        bullet = create_ordinary_bullet_object(side);
    } 
    self->api->request_place(self->host, self, bullet, actual_x, actual_y, ori);
}