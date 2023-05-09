#include "../custom.h"
#include <stdio.h>
#include <stdlib.h>

#define ICE_TOWER_FREEZE_DEGREE 3
#define ICE_TOWER_SELF_DAMAGE 20
#define CANNON_TOWER_DAMAGE 50
#define CANNON_TOWER_SELF_DAMAGE 20
#define TESLA_TOWER_DAMAGE 50
#define TESLA_TOWER_RANGE 9
#define TESLA_TOWER_SELF_DAMAGE 20

extern ini TeslaTowerIni;
extern ini LavaTowerIni;
extern ini IceTowerIni;
extern ini CannonIni;

typedef struct TeslaStorage{
    int birth_silent;
}TeslaStorage;

void tesla_tower_action(Object* self){
    TeslaStorage* storage = (TeslaStorage*)self->storage;
    if(storage->birth_silent != 0){
        storage->birth_silent--;
        return;
    }
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
        if(other_side != self_side && (other_family == INFANTRY || other_family == TANK)){
            break;
        }
    }
    if(j != length){
        closest_object = self_distance_list[j];
        int cx = closest_object->block->x;
        int cy = closest_object->block->y;
        int ix = self->block->x;
        int iy = self->block->y;
        int distance_square = (cx - ix) * (cx - ix) + (cy - iy) * (cy - iy);
        if(distance_square <= TESLA_TOWER_RANGE * TESLA_TOWER_RANGE){
            self->api->request_hurt(self->host, self, closest_object, TESLA_TOWER_DAMAGE);
            self->api->request_load_dynamic_effect(
                self->host,
                ix + 1,
                iy + 1,
                cx + 1,
                cy + 1,
                402,
                0
            );
        }
    }
    self->api->request_hurt(self->host, self, self, TESLA_TOWER_SELF_DAMAGE);
}

Object* create_tesla_tower_object(int side){
    Object* obs = init_object(TeslaTowerIni, side);
    TeslaStorage* storage = (TeslaStorage*)malloc(sizeof(TeslaStorage));
    obs->storage = storage;
    storage->birth_silent = 10;
    obs->action = tesla_tower_action;
    return obs;
}


void lava_tower_action(Object* self){
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
        int other_family = self_distance_list[j]->config.family;
        int other_side = self_distance_list[j]->config.side;
        if(self_side != other_side && other_family == BULLET){
            break;
        }
    }
    if(j != length){
        closest_object = self_distance_list[j];
        int cx = closest_object->block->x;
        int cy = closest_object->block->y;
        int ix = self->block->x;
        int iy = self->block->y;
        int distance_square = (cx - ix) * (cx - ix) + (cy - iy) * (cy - iy);
        if(distance_square <= TESLA_TOWER_RANGE * TESLA_TOWER_RANGE){
            self->api->request_hurt(self->host, self, closest_object, TESLA_TOWER_DAMAGE);
            self->api->request_load_dynamic_effect(
                self->host,
                ix + 1,
                iy + 1,
                cx + 1,
                cy + 1,
                403,
                0
            );
        }
    }
    self->api->request_hurt(self->host, self, self, TESLA_TOWER_SELF_DAMAGE);
}

Object* create_lava_tower_object(int side){
    Object* obs = init_object(TeslaTowerIni, side);
    obs->action = lava_tower_action;
    return obs;
}

void ice_tower_action(Object* self){
    TeslaStorage* storage = (TeslaStorage*)self->storage;
    if(storage->birth_silent != 0){
        storage->birth_silent--;
        return;
    }
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
        if(other_side != self_side && (other_family == INFANTRY || other_family == TANK)){
            break;
        }
    }
    if(j != length){
        closest_object = self_distance_list[j];
        int cx = closest_object->block->x;
        int cy = closest_object->block->y;
        int ix = self->block->x;
        int iy = self->block->y;
        int distance_square = (cx - ix) * (cx - ix) + (cy - iy) * (cy - iy);
        if(distance_square <= TESLA_TOWER_RANGE * TESLA_TOWER_RANGE){
            self->api->request_freeze(self->host, self, closest_object, ICE_TOWER_FREEZE_DEGREE);
            self->api->request_load_dynamic_effect(
                self->host,
                ix + 1,
                iy + 1,
                cx + 1,
                cy + 1,
                404,
                0
            );
        }
    }
    self->api->request_hurt(self->host, self, self, ICE_TOWER_SELF_DAMAGE);
}

Object* create_ice_tower_object(int side){
    Object* obs = init_object(IceTowerIni, side);
    TeslaStorage* storage = (TeslaStorage*)malloc(sizeof(TeslaStorage));
    obs->storage = storage;
    storage->birth_silent = 10;
    obs->action = ice_tower_action;
    return obs;
}


