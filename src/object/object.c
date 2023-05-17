#include "object.h"

void default_object_birth(Object *self){
    // do nothing
}

void default_object_action(Object *self){
    // do nothing
}

void default_object_death(Object *self){
    // do nothing
}

void default_object_hurt(Object *self, int damage){
    Object* object = (Object*)self;
    if(object->status.hp <= damage){
        object->status.hp = 0;
    }else{
        object->status.hp -= damage;
    }   
}

void default_object_heal(Object *self, int heal){
    Object* object = (Object*)self;
    if(object->status.hp + heal > object->config.max_hp)
        object->status.hp = object->config.max_hp;
    else
        object->status.hp += heal;
}

void default_object_freeze(Object *self, int degree){
    Object* object = (Object*)self;
    object->status.frozen_degree = degree;
}

void default_object_burn(Object *self, int degree){
    Object* object = (Object*)self;
    object->status.burning_degree = degree;
}

void default_object_defend(Object *self, int degree){
    Object* object = (Object*)self;
    object->status.defending_degree = degree;
}

void default_object_weak(Object *self, int degree){
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
void set_object_config(Object* object, int type, int side, int max_hp, int length, int height, int interval, BOOL auto_load_anime, int family){
    object->config.type = type;
    object->config.side = side;
    object->config.max_hp = max_hp;
    object->config.length = length;
    object->config.height = height;
    object->config.interval = interval;
    object->config.auto_load_anime = auto_load_anime;
    object->config.family = family;
}

void set_object_anime(Object* object, BOOL direction_4, int up_ori_image, int left_ori_image, int right_ori_image, int down_ori_image, int no_ori_image){
    object->anime.direction_4 = direction_4;
    object->anime.ori_image[UP] = up_ori_image;
    object->anime.ori_image[LEFT] = left_ori_image;
    object->anime.ori_image[RIGHT] = right_ori_image;
    object->anime.ori_image[DOWN] = down_ori_image;
    object->anime.ori_image[NONE] = no_ori_image;
}

// do nothing
void default_persist_affect(Object *self, int affect){
    // do nothing
}
