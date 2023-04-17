# pragma once 
#include "object.h"
#include "processor.h"

// hp = hp, degrees = 0
void set_object_status(Object* object, int hp);

typedef struct default_storage{
    int max_hp;
    int speed;
    int damage;
    int range;
    int attack_interval;
} default_storage;

// if you are going to set the storage to default_storage, you should use this function
void set_object_default_storage(Object* object, int speed, int damage, int range, int attack_interval);

// set the object's config
void set_object_config(Object* object, int type, int side, int max_hp, int interval);

// do nothing
void default_object_birth(void *self);

// do nothing
void default_object_action(void *self);

// do nothing
void default_object_death(void *self);

// object->status.hp -= damage;
void default_object_hurt(void *self, int damage);

// heal object, but not over max_hp
void default_object_heal(void *self, int heal);

// object->status.frozen_degree = degree;
void default_object_freeze(void *self, int degree);

// object->status.burning_degree = degree;
void default_object_burn(void *self, int degree);

// object->status.defending_degree = degree;
void default_object_defend(void *self, int degree);

// object->status.weak_degree = degree;
void default_object_weak(void *self, int degree);

// do nothing
void default_persist_affect(void *self, int affect);

