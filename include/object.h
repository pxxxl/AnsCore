#pragma once

struct Object;
typedef struct Object Object;

struct Player;
typedef struct Player Player;

#include "processor.h"
#include "macros.h"
#include "base.h"
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
};


struct Config;
typedef struct Config Config;
struct Config{
    int max_hp;
    int type;
    int side;
    int interval;
};


struct Object{
    //notice: the "status" is used by the processor, and the storage is used by the object itself
    //the "config" could be used by everyone
    Status status;
    Config config;
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

struct Player{
    Object* object;
    int side;

    int skill_tag[SKILL_NUM];
    int skill_num;

    // if -1, means no skill is chosen
    int skill_choice;
};

