#include "../custom.h"

void tesla_tower_action(Object* self){
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
        if(other_side != self_side && (other_side == RED_TROOP || other_side == BLUE_TROOP)){
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
    Object* obs = (Object*)malloc(sizeof(Object));
    if(side != RED_TROOP && side != BLUE_TROOP){
        printf("Error: create_tesla_tower_object: side is not valid");
        exit(1);
    }
    set_object_config(obs, 108, side, 300, 3, 3, TESLA_TOWER_INTERVAL, TRUE);
    set_object_status(obs, 300);
    set_object_anime(obs, TRUE, 106, 106, 106, 106, 106);
    obs->storage = NULL;
    obs->birth = default_object_birth;
    obs->action = tesla_tower_action;
    obs->death = default_object_death;
    obs->hurt = default_object_hurt;
    obs->heal = default_object_heal;
    obs->freeze = default_object_freeze;
    obs->burn = default_object_burn;
    obs->defend = default_object_defend;
    obs->weak = default_object_weak;
    return obs;
}

