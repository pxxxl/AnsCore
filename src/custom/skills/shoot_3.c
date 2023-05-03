#include "../custom.h"

void player_shoot_3(Object* self, void* param){
    int x = self->block->x;
    int y = self->block->y;
    int ori = self->block->orientation;
    int actual_x[3];
    int actual_y[3];
    int center_x = x + 1;
    int center_y = y + 1;
    switch(ori){
        case UP:
            for(int i = 0 ; i < 3 ; i++){
                actual_x[i] = center_x;
                actual_y[i] = center_y - 2 - i * 2;
            }
            break;
        case DOWN: 
            for(int i = 0 ; i < 3 ; i++){
                actual_x[i] = center_x;
                actual_y[i] = center_y + 2 + i * 2;
            }
            break;
        case LEFT:  
            for(int i = 0 ; i < 3 ; i++){
                actual_x[i] = center_x - 2 - i * 2;
                actual_y[i] = center_y;
            }
            break;
        case RIGHT: 
            for(int i = 0 ; i < 3 ; i++){
                actual_x[i] = center_x + 2 + i * 2;
                actual_y[i] = center_y;
            }
            break;
    }
    int side = self->config.side == RED ? RED : BLUE;
    Object* bullet[3];
    for(int i = 0 ; i < 3 ; i++){
        bullet[i] = create_ordinary_bullet_object(side);
        self->api->request_place(self->host, self, bullet[i], actual_x[i], actual_y[i], ori);
    }
}