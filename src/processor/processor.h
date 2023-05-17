#pragma once

struct ProcessorAPI;
typedef struct ProcessorAPI ProcessorAPI;

struct Processor;
typedef struct Processor Processor;

struct ProcessorAnimeData;
typedef struct ProcessorAnimeData ProcessorAnimeData;

struct ProcessorAPIRequest;
typedef struct ProcessorAPIRequest ProcessorAPIRequest;

#define API_REQUEST_MAX_NUM 10000             // the max number of the api request
#define API_REQUEST_MOVE 1                  // move
#define API_REQUEST_TELEPORT 2              // teleport
#define API_REQUEST_FREEZE 3                // freeze
#define API_REQUEST_BURN 4                  // burn
#define API_REQUEST_DEFEND 5                // defend
#define API_REQUEST_WEAK 6                  // weak
#define API_REQUEST_HEAL 7                  // heal
#define API_REQUEST_HURT 8                  // hurt
#define API_REQUEST_LOAD_ANIME 9            // load anime
#define API_REQUEST_STEP 10                 // step
#define API_REQUEST_PLACE 11                // place
#define API_REQUEST_SUISIDE 12              // suiside
#define API_REQUEST_USE_SKILL 13            // use skill
#define MAX_SKILL_NUM 100                   // the total number of the skills
#define UNIT_TYPE_PLAYER_OBJECT_A 100         // the type of the player object
#define UNIT_TYPE_PLAYER_OBJECT_B 115         // the type of the player object
#define PLAYER_SKILL_MAX_NUM 6              // the max number of the skills of the player
#define PLAYER1 1                           // the id of the player 1
#define PLAYER2 2                           // the id of the player 2


#include "../base/base.h"
#include "../object/object.h"
#include "../macros.h"

typedef struct PlayerObject{
    Object* object;
    int skill_tag[PLAYER_SKILL_MAX_NUM];
    int skill_num;
    int skill_choice;// if -1, means no skill is chosen
}PlayerObject;

typedef struct AnimePack{
    int pack_type;              //ANIME_PACK_TYPE_MOVE_INFO or ANIME_PACK_TYPE_EFFECT_INFO
    int tag;                    //tag: the tag of the animation, and it is used to get the image
    int x, y;                   //the position of the animation
    int des_x, des_y;           //the destination of the animation(only used in move animation)
    int delay;                  //when the delay is not 0, this pack will not be loaded in this step, and it will decrease by 1 in each step
} AnimePack;

typedef struct PlayerDisplayPack{
    int hp;
    int side;                    // RED_TROOP or BLUE_TROOP
    int skill_tag[PLAYER_SKILL_MAX_NUM];    // the tag of the skill
    int skill_num;
    int skill_choice;            // if -1, means no skill is chosen
} PlayerDisplayPack;

typedef struct PlayerDash{
    int player_1_direction_key;
    int player_1_attack_key;
    int player_1_change_skill_key;
    int player_1_use_skill_key;
    
    int player_2_direction_key;
    int player_2_attack_key;
    int player_2_change_skill_key;
    int player_2_use_skill_key;
}PlayerDash;

struct ProcessorAnimeData{
    AnimePack anime_pack[ANIME_PACK_CACHE_MAX_LENGTH];
    int anime_pack_size;

    PlayerDisplayPack player_display_pack[2];
};

struct ProcessorAPIRequest{
    int type;
    Object* source;
    Object* target;
    int x;
    int y;
    int ext_1;
    int ext_2;
    int ext_3;
    void* ext_4;
};

typedef void (*SkillFunc)(Object* self, void* param);


struct ProcessorAPI{
    // make best effort to do the action
    void (*request_place)(Processor *host, Object *source, Object *target, int x, int y, int ori);
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
    void (*request_use_skill)(Processor *host, Object *source, int skill_id, void* params);
    void (*request_use_skill_player)(Processor *host, int player_id, void* params);
    
    // NOTICE: USER SHOULD USE MALLOC TO ALLOCATE MEMORY FOR THE PACK, AND DON'T FREE IT
    void (*request_load_anime)(Processor *host, AnimePack *pack);
    void (*request_load_static_effect)(Processor* host, int x, int y, int tag, int delay);
    void (*request_load_static_sustaining_effect)(Processor* host, int x, int y, int tags[], int length, int delay);
    void (*request_load_dynamic_effect)(Processor* host, int x, int y, int des_x, int des_y, int tag, int delay);
    void (*request_load_move_effect)(Processor* host, int x, int y, int step, int direction, int tag, int delay);

    void (*give_skill)(Processor *host, Object *source, int skill_id);
    void (*change_skill_choice)(Processor *host, int player_id, int right_shift, int left_shift);
    // range is [x1, x2) and [y1, y2), invalid address excluded automately
    Object* (*detect_exist_object)(Processor *host, int x1, int y1, int x2, int y2);
    Object* (*get_object)(Processor *host, int x, int y);
    Object* (*find_closest_object_in_direction)(Processor *host, Object* object, int direction);
    Object* (*find_closest_object)(Processor *host, Object* object);
    Object* (*find_object_around)(Processor *host, Object* object, int radius);
    void (*get_distance_list)(Processor *host, Object ****distance_list, Object*** object_list, int *length);

    BOOL (*is_valid_address)(Processor *host, int x, int y);
    BOOL (*cannot_hurt)(Processor *host, Object* attacker, Object* defender);
    BOOL (*at_edge)(Processor *host, Object* object);
    BOOL (*going_out_of_bound)(Processor *host, Object* object, int direction);
};



/*
    * AnimePack
    * 
    * This struct is used to store the information of
    * the animation.
    * 
    * pack_type: the type of the animation
    * if pack_type == ANIME_PACK_TYPE_MOVE_INFO:
    *   the animation is a move animation
    * if pack_type == ANIME_PACK_TYPE_EFFECT_INFO:
    *   the animation is a effect animation
*/



struct Processor{
    Base *base;
    ProcessorAPI *api;
    PlayerObject player[2];

    AnimePack anime_cache[ANIME_PACK_CACHE_MAX_LENGTH];
    int anime_cache_size;

    Object* object_at_birth[OBJECT_AT_BIRTH_MAX_LENGTH];
    int object_at_birth_size;
    Object* object_at_death[OBJECT_AT_DEATH_MAX_LENGTH];
    int object_at_death_size;

    ProcessorAPIRequest request_queue[API_REQUEST_MAX_NUM];
    int request_queue_size;

    SkillFunc skill_map[MAX_SKILL_NUM];

    int distance_list_generated;
    Object ***distance_list;
    Object **object_list;
    int object_list_length;

    void (*step)(Processor *self);
    ProcessorAnimeData (*export_anime_data)(Processor *self);
    ProcessorAnimeData (*export_anime_data_x_vertical)(Processor *self);
    ProcessorAnimeData (*export_anime_data_y_plus_120)(Processor *self);
    void (*fillin_skill_map)(Processor *self, SkillFunc* skill_map, int length);
};


// init the processor
Processor* init_processor(int length, int height);

// destroy the processor
void destroy_processor(Processor *self);

void clear_player_dash(PlayerDash *player_dash, int side);

