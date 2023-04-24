#pragma once

struct Object;
typedef struct Object Object;

#include "../processor/processor.h"
#include "../macros.h"
#include "../base/base.h"
#include <malloc.h>

struct Status;
typedef struct Status Status;
struct Status{
    int hp;

    int frozen_degree;
    int burning_degree;
    int defending_degree;
    int weak_degree;

    int clock;
    BOOL moving;
};


struct Config;
typedef struct Config Config;
struct Config{
    int max_hp;
    int length;
    int height;
    int type;
    int side;
    int interval;
    BOOL auto_load_anime;
};

struct Anime;
typedef struct Anime Anime;
struct Anime{
    BOOL direction_4;               // TRUE: 4 direction image, enabling auto redirection FALSE: 4 direction image same
    int ori_image[5];
};


struct Object{
    //notice: the "status" is used by the processor, and the storage is used by the object itself
    //the "config" could be used by everyone
    Status status;
    Config config;
    Anime anime;
    void* storage;

    Block* block;
    Processor* host;
    ProcessorAPI* api;
    
    void (*birth)(Object *self);
    void (*action)(Object *self);
    void (*death)(Object *self);

    void (*hurt)(Object *self, int damage);
    void (*heal)(Object *self, int heal);
    void (*freeze)(Object *self, int degree);
    void (*burn)(Object *self, int degree);
    void (*defend)(Object *self, int degree);
    void (*weak)(Object *self, int degree);
};




typedef struct default_storage{
    int max_hp;
    int speed;
    int damage;
    int range;
    int attack_interval;
} default_storage;

// Utils

// if you are going to set the storage to default_storage, you should use this function
void set_object_default_storage(Object* object, int speed, int damage, int range, int attack_interval);

// set the object's config
void set_object_config(Object* object, int type, int side, int max_hp, int length, int height, int interval, BOOL auto_load_anime);

// hp = hp, degrees = 0
void set_object_status(Object* object, int hp);

// set object's anime
void set_object_anime(Object* object, BOOL direction_4, int up_ori_image, int left_ori_image, int right_ori_image, int down_ori_image, int no_ori_image);

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
