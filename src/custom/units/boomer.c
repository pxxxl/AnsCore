#include "../custom.h"

#define BOOM_RANGE 3
#define BOOM_TRIGGER_RANGE 3
#define BOOM_DAMAGE 10

extern ini BoomerTankIni;

typedef struct BoomerTankStorage{
    int prefer_vertical;
}BoomerTankStorage;

void boomer_boom(Object* self, void* param){
    int x = CENTER(self->block->x, self->block->length);
    int y = CENTER(self->block->y, self->block->height);
    int ix = self->block->x;
    int iy = self->block->y;
    int begin_x = x;
    int begin_y = y;
    int side = self->config.side == RED ? RED : BLUE;
    int family = self->config.family;
    for(int i = x - BOOM_RANGE; i < x + BOOM_RANGE + 1; i++){
        for(int j = y - BOOM_RANGE; j < y + BOOM_RANGE + 1; j++){
            Object* obj = self->api->get_object(self->host, i, j);
            if(obj == NULL){
                continue;
            }
            self->api->request_hurt(self->host, self, obj, BOOM_DAMAGE);
            int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
            self->api->request_load_static_sustaining_effect(self->host, ix, iy, boom_tags, 10, 0);
            self->api->request_suiside(self->host, self);
        }
    }
}


void boomer_action(Object* self){
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
        if(ABS(cx - ix) <= BOOM_TRIGGER_RANGE && ABS(cy - iy) <= BOOM_TRIGGER_RANGE){
            boomer_boom(self, NULL);
        }
        if(ix == cx){
            if(iy < cy){
                self->api->request_step(self->host, self, DOWN);
            }else if(iy > cy){
                self->api->request_step(self->host, self, UP);
            }else{
                
            }
        }else if(ix < cx){
            if(iy == cy){
                self->api->request_step(self->host, self, RIGHT);
            }else if(iy < cy){
                self->api->request_step(self->host, self, RIGHT);
            }else{
                self->api->request_step(self->host, self, UP);
            }
        }else{
            if(iy == cy){
                self->api->request_step(self->host, self, LEFT);
            }else if(iy < cy){
                self->api->request_step(self->host, self, DOWN);
            }else{
                self->api->request_step(self->host, self, LEFT);
            }
        }
    }
}

void boomer_death(Object* self){
    boomer_boom(self, NULL);
}

Object* create_boomer_tank_object(int side){
    Object* obs = init_object(BoomerTankIni, side);
    obs->action = boomer_action;
    obs->death = boomer_death;
    return obs;
}