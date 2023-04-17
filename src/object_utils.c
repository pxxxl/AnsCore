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

void set_object_status(Object* object, int hp){
    object->status.hp = hp;
    object->status.burning_degree = 0;
    object->status.frozen_degree = 0;
    object->status.defending_degree = 0;
    object->status.weak_degree = 0;
    object->status.clock = 0;
}

// if you are going to set the storage to default_storage, you should use this function
void set_object_default_storage(Object* object, int speed, int damage, int range, int attack_interval){
    object->storage = malloc(sizeof(default_storage));
    default_storage* storage = (default_storage*)object->storage;
    storage->speed = speed;
    storage->damage = damage;
    storage->range = range;
    storage->attack_interval = attack_interval;
}

// set the object's config
void set_object_config(Object* object, int type, int side, int max_hp, int interval){
    object->config.type = type;
    object->config.side = side;
    object->config.max_hp = max_hp;
    object->config.interval = interval;
}

// do nothing
void default_persist_affect(void *self, int affect){
    // do nothing
}