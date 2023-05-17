#include "../custom.h"
#include "../../random.h"

#define ATTACK_RANGE 6
#define ATTACK_DAMAGE 3

extern ini NormalInfantryIni;
extern ini ChronoInfantryIni;

void attack(Object* self ,int tx, int ty){
    Object* obj = self->api->get_object(self->host, tx, ty);
    int ix = CENTER(self->block->x, self->block->length);
    int iy = CENTER(self->block->y, self->block->height);
    self->api->request_hurt(self->host, self, obj, ATTACK_DAMAGE);
    self->api->request_load_dynamic_effect(
                self->host,
                ix,
                iy,
                tx,
                ty,
                406,
                0
    );
    self->api->request_load_dynamic_effect(
                self->host,
                ix,
                iy,
                tx,
                ty,
                406,
                1
    );
    self->api->request_load_dynamic_effect(
                self->host,
                ix,
                iy,
                tx,
                ty,
                406,
                2
    );
}


void normal_infantry_action(Object* self){
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
        if(ABS(cx - ix) <= ATTACK_RANGE && ABS(cy - iy) <= ATTACK_RANGE){
            attack(self, cx, cy);
        }
        if(ix == cx){
            if(iy < cy){
                self->api->request_step(self->host, self, DOWN);
            }else if(iy > cy){
                self->api->request_step(self->host, self, UP);
            }else{
                
            }
        }else if(ix < cx){
            self->api->request_step(self->host, self, RIGHT);
        }else{
            self->api->request_step(self->host, self, LEFT);
        }
    }
}

typedef struct ChronoStorage{
    int chrono_max_time;
    int chrono_timer;
}ChronoStorage;

void chrono_infantry_action(Object* self){
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

    ChronoStorage* storage = self->storage;
    if(storage->chrono_timer == 0){
        //teleport
        self->api->request_load_static_effect(
                    self->host,
                    self->block->x - 1,
                    self->block->y - 1,
                    313,
                    0
        );
        unsigned randx = randint() % 38;
        unsigned randy = randint() % 21;
        self->api->request_teleport(self->host, self, randx, randy);
        storage->chrono_timer = storage->chrono_max_time;
    }else{
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
            if(ABS(cx - ix) <= ATTACK_RANGE && ABS(cy - iy) <= ATTACK_RANGE){
                attack(self, cx, cy);
            }
        }
        storage->chrono_timer--;
    }
}

Object* create_normal_infantry_object(int side){
    Object* obs = init_object(NormalInfantryIni, side);
    obs->action = normal_infantry_action;
    return obs;
}



Object* create_chrono_infantry_object(int side){
    Object* obs = init_object(ChronoInfantryIni, side);
    obs->action = chrono_infantry_action;
    ChronoStorage* storage = malloc(sizeof(ChronoStorage));
    storage->chrono_max_time = 10;
    storage->chrono_timer = 10;
    obs->storage = storage;
    return obs;
}