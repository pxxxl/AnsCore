#include "../custom.h"

#define LASER_DAMAGE 5

extern ini LaserTankIni;
extern ini LaserInfantryIni;

void laser_shoot(Object* self, void* param){
    int x = CENTER(self->block->x, self->block->length);
    int y = CENTER(self->block->y, self->block->height);
    int ori = self->block->orientation;
    int begin_x = x;
    int begin_y = y;
    int half_x = self->block->length / 2;
    int half_y = self->block->height / 2;
    int side = self->config.side == RED ? RED : BLUE;
    switch(ori){
        case UP: 
            begin_y -= 1 + half_y;
            for(int i = begin_y; i >= 0; i--){
                Object* target = self->api->get_object(self->host, begin_x, i);
                if(target != NULL){
                    if(target->config.side != self->config.side){
                        self->api->request_hurt(self->host, self, target, 10);
                    }
                }
                self->api->request_load_static_effect(self->host, begin_x, i, 410, 0);
            }
        case DOWN: 
            begin_y += 1 + half_y;
            for(int i = begin_y; i < self->host->base->height; i++){
                Object* target = self->api->get_object(self->host, begin_x, i);
                if(target != NULL){
                    if(target->config.side != self->config.side){
                        self->api->request_hurt(self->host, self, target, 10);
                    }
                }
                self->api->request_load_static_effect(self->host, begin_x, i, 410, 0);
            }
        case LEFT:
            begin_x -= 1 + half_x;
            for(int i = begin_x; i >= 0; i--){
                Object* target = self->api->get_object(self->host, i, begin_y);
                if(target != NULL){
                    if(target->config.side != self->config.side){
                        self->api->request_hurt(self->host, self, target, 10);
                    }
                }
                self->api->request_load_static_effect(self->host, i, begin_y, 411, 0);
            }
        case RIGHT:
            begin_x += 1 + half_x;
            for(int i = begin_x; i < self->host->base->length; i++){
                Object* target = self->api->get_object(self->host, i, begin_y);
                if(target != NULL){
                    if(target->config.side != self->config.side){
                        self->api->request_hurt(self->host, self, target, 10);
                    }
                }
                self->api->request_load_static_effect(self->host, i, begin_y, 411, 0);
            }
    }
}


void laser_action(Object* self){
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
        if(other_side != self_side && other_family != BULLET){
            break;
        }
    }
    if(j != length){
        closest_object = self_distance_list[j];
        int cx = CENTER(closest_object->block->x, closest_object->block->length);
        int cy = CENTER(closest_object->block->y, closest_object->block->height);
        int ix = CENTER(self->block->x, self->block->length);
        int iy = CENTER(self->block->y, self->block->height);
        if(iy < cy){
            self->api->request_step(self->host, self, DOWN);
        }else if(iy > cy){
            self->api->request_step(self->host, self, UP);
        }else{
            if(ix < cx){
                self->block->orientation = RIGHT;
                laser_shoot(self, NULL);
            }else if(ix > cx){
                self->block->orientation = LEFT;
                laser_shoot(self, NULL);
            }else{
                
            }
        }
    }
}

Object* create_laser_tank_object(int side){
    Object* obs = init_object(LaserTankIni, side);
    obs->action = laser_action;
    return obs;
}

Object* create_laser_infantry_object(int side){
    Object* obs = init_object(LaserInfantryIni, side);
    obs->action = laser_action;
    return obs;
}