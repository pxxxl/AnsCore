#include "../include/player_object.h"
#include "../include/object_utils.h"

/*
Object* create_player_object();
void player_object_action(void *self);
*/

Object* create_player_object(){
    Object* object = (Object*)malloc(sizeof(Object));

    default_set_object_status(object, 100);
    object->config.max_hp = 100;
    object->config.speed = 1;
    object->config.damage = 10;
    object->config.range = 1;
    object->config.interval = 1;
    object->config.type = 1;

    object->birth = default_object_birth;
    object->action = player_object_action;
    object->death = default_object_death;
    object->hurt = default_object_hurt;
    object->heal = default_object_heal;
    object->freeze = default_object_freeze;
    object->burn = default_object_burn;
    object->defend = default_object_defend;
    object->weak = default_object_weak;
    return object;
}

static void player_object_action(void *self){
    // do nothing
}
