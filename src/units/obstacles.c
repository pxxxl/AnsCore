#include "../../include/object.h"
#include "../../include/object_utils.h"

// Obstacle_wall
Object* create_obstacle_wall_object(){
    Object* obs = (Object*)malloc(sizeof(Object));
    default_set_object_config(obs, 65535, 0, 0, 0, 0, 0, NEUTRAL);
    default_set_object_status(obs, 65535);
    obs->birth = default_object_birth;
    obs->action = default_object_action;
    obs->death = default_object_death;
    obs->hurt = default_persist_affect;
    obs->heal = default_persist_affect;
    obs->freeze = default_persist_affect;
    obs->burn = default_persist_affect;
    obs->defend = default_persist_affect;
    obs->weak = default_persist_affect;
    return obs;
}

static void obstacle_wall_action(Object* self){
    AnimePack* pack = (AnimePack*)malloc(sizeof(AnimePack));
    pack->delay = 0;
    pack->pack_type = ANIME_PACK_TYPE_EFFECT_INFO;
    pack->tag = 101;
    pack->x = self->block->x;
    pack->y = self->block->y;
    self->api->request_load_anime(self->host, pack);
}