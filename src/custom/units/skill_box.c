#include "../custom.h"
#include "../../random.h"


static void skill_box_action(Object* self){
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
    for(j = 1; j < length; j++){
        closest_object = self_distance_list[j];
        if(closest_object->config.type == UNIT_TYPE_PLAYER_OBJECT){
            int sx = self->block->x;
            int sy = self->block->y;
            int cx = closest_object->block->x;
            int cy = closest_object->block->y;
            int length = closest_object->block->length;
            int height = closest_object->block->height;
            int bare_min_x = sx - length;
            int bare_max_x = sx + 1;
            int bare_min_y = sy - height;
            int bare_max_y = sy + 1;
            if(cx <= bare_max_x && cx >= bare_min_x){
                if(cy <= bare_max_y && cy >= bare_min_y){
                    break;
                }
            }
        }
    }
    if(j != length){
        closest_object = self_distance_list[j];
        unsigned rand = randint();
        unsigned chosen = rand % CURRENT_SKILL_NUM;
        self->host->api->give_skill(self->host, closest_object, chosen);
        self->host->api->request_suiside(self->host, self);
    }
}


Object* create_skill_box(){
    Object* obs = (Object*)malloc(sizeof(Object));
    set_object_config(obs, 106, NEUTRAL, 1, 1, 1, BULLET_OBJECT_INTERVAL, TRUE);
    set_object_anime(obs, TRUE, 402, 402,  402, 402, 402);
    set_object_status(obs, 1);
    obs->storage = NULL;
    obs->birth = default_object_birth;
    obs->action = skill_box_action;
    obs->death = default_object_death;
    obs->hurt = default_persist_affect;
    obs->heal = default_persist_affect;
    obs->freeze = default_persist_affect;
    obs->burn = default_persist_affect;
    obs->defend = default_persist_affect;
    obs->weak = default_persist_affect;
    return obs;
}


// size 1*1, detect surrounding 3*3, if founded, suicide and give the player a skill