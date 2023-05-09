#include "../custom.h"

void place_normal_infantry(Object* self, void* param){
    int x = self->block->x;
    int y = self->block->y;
    int ori = self->block->orientation;
    int actual_x = x;
    int actual_y = y;
    switch(ori){
        case UP: actual_y-=4; break;
        case DOWN: actual_y+=4; break;
        case LEFT: actual_x-=4; break;
        case RIGHT: actual_x+=4; break;
    }
    int side = self->config.side == RED ? RED : BLUE;
    Object* tesla = create_normal_infantry_object(side);
    self->api->request_place(self->host, self, tesla, actual_x, actual_y, ori);
}

void place_chrono_infantry(Object* self, void* param){
    int x = self->block->x;
    int y = self->block->y;
    int ori = self->block->orientation;
    int actual_x = x;
    int actual_y = y;
    switch(ori){
        case UP: actual_y-=4; break;
        case DOWN: actual_y+=4; break;
        case LEFT: actual_x-=4; break;
        case RIGHT: actual_x+=4; break;
    }
    int side = self->config.side == RED ? RED : BLUE;
    Object* tesla = create_chrono_infantry_object(side);
    self->api->request_place(self->host, self, tesla, actual_x, actual_y, ori);
}
void place_laser_infantry(Object* self, void* param){
    int x = self->block->x;
    int y = self->block->y;
    int ori = self->block->orientation;
    int actual_x = x;
    int actual_y = y;
    switch(ori){
        case UP: actual_y-=4; break;
        case DOWN: actual_y+=4; break;
        case LEFT: actual_x-=4; break;
        case RIGHT: actual_x+=4; break;
    }
    int side = self->config.side == RED ? RED : BLUE;
    Object* tesla = create_laser_infantry_object(side);
    self->api->request_place(self->host, self, tesla, actual_x, actual_y, ori);   
}