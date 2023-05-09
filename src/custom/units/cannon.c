#include "../custom.h"
extern ini CannonIni;

void cannon_shoot(Object* self, void* param);

void cannon_tower_action(Object* self){
    cannon_shoot(self, NULL);
}

Object* create_cannon_tower_object(int side){
    Object* obs = init_object(CannonIni, side);
    obs->storage = NULL;
    obs->action = cannon_tower_action;
    return obs;
}

void cannon_shoot(Object* self, void* param){
    int x = self->block->x;
    int y = self->block->y;
    int ori;

    Object*** distance_list;
    Object** object_list;
    int length;
    self->api->get_distance_list(self->host, &distance_list, &object_list, &length);
    int i;
    for(i = 0; i < length; i++){
        if(object_list[i] == self){
            break;
        }
    }
    Object** self_distance_list = distance_list[i];
    int j;
    Object* closest_object;


    int self_side = self->config.side;
    for(j = 1; j < length; j++){
        int other_side = self_distance_list[j]->config.side;
        int other_family = self_distance_list[j]->config.family;
        if(other_side != self_side && other_family == TOWER){
            break;
        }
    }
    if(j != length){
        closest_object = self_distance_list[j];
        int cx = CENTER(closest_object->block->x, closest_object->block->length);
        int cy = CENTER(closest_object->block->y, closest_object->block->height);
        int ix = CENTER(self->block->x, self->block->length);
        int iy = CENTER(self->block->y, self->block->height);
        if(cx > ix){
            self->block->orientation = RIGHT;
        }else if(cx < ix){
            self->block->orientation = LEFT;
        }
    }

    if(self->block->orientation == LEFT){
        ori = LEFT;
    }else if(self->block->orientation == RIGHT){
        ori = RIGHT;
    }else{
        ori = UP;
    }
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