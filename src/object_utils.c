#include "../include/object_utils.h"

void default_object_birth(void *self){
    // do nothing
}

void default_object_action(void *self){
    // do nothing
}

void default_object_death(void *self){
    // do nothing
}

void default_object_hurt(void *self, int damage){
    Object* object = (Object*)self;
    object->status.hp -= damage;
}

void default_object_heal(void *self, int heal){
    Object* object = (Object*)self;
    if(object->status.hp + heal > object->config.max_hp)
        object->status.hp = object->config.max_hp;
    else
        object->status.hp += heal;
}

void default_object_freeze(void *self, int degree){
    Object* object = (Object*)self;
    object->status.frozen_degree = degree;
}

void default_object_burn(void *self, int degree){
    Object* object = (Object*)self;
    object->status.burning_degree = degree;
}

void default_object_defend(void *self, int degree){
    Object* object = (Object*)self;
    object->status.defending_degree = degree;
}

void default_object_weak(void *self, int degree){
    Object* object = (Object*)self;
    object->status.weak_degree = degree;
}

void default_set_object_status(Object* object, int hp){
    object->status.hp = hp;
    object->status.burning_degree = 0;
    object->status.frozen_degree = 0;
    object->status.defending_degree = 0;
    object->status.weak_degree = 0;
}
