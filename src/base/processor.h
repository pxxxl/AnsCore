#pragma once

struct ProcessorAPI;
typedef struct ProcessorAPI ProcessorAPI;

struct Processor;
typedef struct Processor Processor;

struct ProcessorAnimeData;
typedef struct ProcessorAnimeData ProcessorAnimeData;

struct ProcessorAPIRequest;
typedef struct ProcessorAPIRequest ProcessorAPIRequest;

#include "base.h"
#include "object.h"
#include "macros.h"
#include "anime_pack.h"

#include "../character/player_object.h"

struct ProcessorAPIRequest{
    int type;
    Object* source;
    Object* target;
    int x;
    int y;
    int ext_1;
    int ext_2;
    void* ext_3;
};

struct Processor{
    Base *base;
    ProcessorAPI *api;
    Player* player[2];

    AnimePack anime_cache[ANIME_PACK_CACHE_MAX_LENGTH];
    int anime_cache_size;

    Object* object_at_birth[OBJECT_AT_BIRTH_MAX_LENGTH];
    int object_at_birth_size;
    Object* object_at_death[OBJECT_AT_DEATH_MAX_LENGTH];
    int object_at_death_size;

    ProcessorAPIRequest request_queue[API_REQUEST_MAX_NUM];
    int request_queue_size;

    Object* (*place_object)(Processor *self, Object* object, int x, int y, int length, int height);
    void (*step)(Processor *self);
    ProcessorAnimeData (*export_anime_data)(Processor *self);
};


struct ProcessorAPI{
    void (*request_move)(Processor *host, Object *source, int direction, int step);
    void (*request_teleport)(Processor *host, Object *source, int des_x, int des_y);
    void (*request_freeze)(Processor *host, Object *source, Object* target, int degree);
    void (*request_burn)(Processor *host, Object *source, Object* target, int degree);
    void (*request_defend)(Processor *host, Object *source, Object* target, int degree);
    void (*request_weak)(Processor *host, Object *source, Object* target, int degree);
    void (*request_heal)(Processor *host, Object *source, Object* target, int heal);
    void (*request_hurt)(Processor *host, Object *source, Object* target, int damage);

    // NOTICE: USER SHOULD USE MALLOC TO ALLOCATE MEMORY FOR THE PACK, AND DON'T FREE IT
    void (*request_load_anime)(Processor *host, AnimePack *pack);

    Object* (*detect_exist_object)(Processor *host, int x1, int y1, int x2, int y2);
    Object* (*get_object)(Processor *host, int x, int y);
    Object* (*find_closest_object_in_direction)(Processor *host, Object* object, int direction);
    Object* (*find_closest_object)(Processor *host, int x, int y);
};



// init the processor
Processor* init_processor();

// destroy the processor
void destroy_processor(Processor *self);

// place an object at this place
// return ptr to the object if success, return NULL if failed 
Object* place_object(Processor *self, Object* object, int x, int y, int length, int height);

// step the processor
void step(Processor *self);

// export the anime data
ProcessorAnimeData export_anime_data(Processor *self);

// below are provided to the objects
// objects could only use these functions to interact with the processor or other objects

// request to move the object
void request_move(Processor *host, Object *source, int direction, int step);

// request to teleport the object
void request_teleport(Processor *host, Object *source, int des_x, int des_y);

// request to freeze the object
// freeze: the object will not "action"
// degree-- for each step
void request_freeze(Processor *host, Object *source, Object* target, int degree);

// request to burn the object
// burn: the object will lose hp, hp -= 1
// degree-- for each step
void request_burn(Processor *host, Object *source, Object* target, int degree);

// request to defend the object
// defend: hurt will be reduced by degree
void request_defend(Processor *host, Object *source, Object* target, int degree);

// request to weaken the object
// weaken: hurt will be increased by degree
void request_weak(Processor *host, Object *source, Object* target, int degree);

// request to heal the object
void request_heal(Processor *host, Object *source, Object* target, int heal);

// request to hurt the object
void request_hurt(Processor *host, Object *source, Object* target, int damage);

// request to load the anime
// NOTICE: USER SHOULD USE MALLOC TO ALLOCATE MEMORY FOR THE PACK, AND DON'T FREE IT
void request_load_anime(Processor *host, AnimePack *pack);

// detect if there is an object in the area
// return the object if there is, return NULL if not
// range [x1, x2), [y1, y2)
Object* detect_exist_object(Processor *host, int x1, int y1, int x2, int y2);

// get the object at this place
// return the object if there is, return NULL if not
Object* get_object(Processor *host, int x, int y);

// find the closest object in the direction
// return the closest if there is, return NULL if not
Object* find_closest_object_in_direction(Processor *host, Object* object, int direction);

// find the closest object
// return the closest if there is, return NULL if not
Object* find_closest_object(Processor *host, Object* object);
