#include "../../include/units.h"
#include "../../include/object_utils.h"

Object* create_skill_box(){
    Object* obs = (Object*)malloc(sizeof(Object));
    set_object_config(obs, 106, NEUTRAL, 1, BULLET_OBJECT_INTERVAL);
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
static void skill_box_action(void* self){
    
}