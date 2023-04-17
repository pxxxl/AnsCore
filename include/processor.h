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
#include "anime.h"

#include "units.h"

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


struct ProcessorAPI{
    // make best effort to do the action
    void (*request_move)(Processor *host, Object *source, int direction, int step);
    void (*request_step)(Processor *host, Object *source, int direction);
    void (*request_suiside)(Processor *host, Object *source);
    void (*request_teleport)(Processor *host, Object *source, int des_x, int des_y);
    void (*request_freeze)(Processor *host, Object *source, Object* target, int degree);
    void (*request_burn)(Processor *host, Object *source, Object* target, int degree);
    void (*request_defend)(Processor *host, Object *source, Object* target, int degree);
    void (*request_weak)(Processor *host, Object *source, Object* target, int degree);
    void (*request_heal)(Processor *host, Object *source, Object* target, int heal);
    void (*request_hurt)(Processor *host, Object *source, Object* target, int damage);

    // NOTICE: USER SHOULD USE MALLOC TO ALLOCATE MEMORY FOR THE PACK, AND DON'T FREE IT
    void (*request_load_anime)(Processor *host, AnimePack *pack);

    // range is [x1, x2) and [y1, y2), invalid address excluded automately
    Object* (*detect_exist_object)(Processor *host, int x1, int y1, int x2, int y2);
    Object* (*get_object)(Processor *host, int x, int y);
    Object* (*find_closest_object_in_direction)(Processor *host, Object* object, int direction);
    Object* (*find_closest_object)(Processor *host, int x, int y);
    void (*generate_distance_list)(Processor *host, Object ****distance_list, Object*** blocks, int *length);

    BOOL (*is_valid_address)(Processor *host, int x, int y);
    BOOL (*cannot_hurt)(Processor *host, Object* attacker, Object* defender);
    BOOL (*at_edge)(Processor *host, Object* object);
    BOOL (*going_out_of_bound)(Processor *host, Object* object, int direction);
};


struct ProcessorAnimeData{
    AnimePack anime_pack[ANIME_PACK_CACHE_MAX_LENGTH];
    int anime_pack_size;

    PlayerDisplayPack player_display_pack[2];
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


// init the processor
Processor* init_processor();

// destroy the processor
void destroy_processor(Processor *self);