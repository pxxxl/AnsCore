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
};


struct Config;
typedef struct Config Config;
struct Config{
    int max_hp;
    int speed;
    int damage;
    int range;
    int interval;
    int type;
    int side;
};


struct Object{
    Status status;
    Config config;

    Block* block;
    Processor* host;
    ProcessorAPI* api;
    void* self;

    void (*init)(void *self);

    void (*birth)(void *self);
    void (*action)(void *self);
    void (*death)(void *self);

    void (*hurt)(void *self, int damage);
    void (*heal)(void *self, int heal);
    void (*freeze)(void *self, int degree);
    void (*burn)(void *self, int degree);
    void (*defend)(void *self, int degree);
    void (*weak)(void *self, int degree);
};

struct Player{
    Object* object;
    int side;

    int skill_tag[PLAYER_SKILL_NUM];
    int skill_num;

    // if -1, means no skill is chosen
    int skill_choice;
};

