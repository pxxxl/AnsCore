#pragma once

// intervals
#define PLAYER_OBJECT_INTERVAL 0
#define OBSTACLE_OBJECT_INTERVAL 65535
#define BULLET_OBJECT_INTERVAL 0
#define SKILL_BOX_INTERVAL 0
#define TESLA_TOWER_INTERVAL 10


// Statistics
#define ORDINARY_BULLET_DAMAGE 50
#define FREEZING_BULLET_DAMAGE 25
#define FREEZING_BULLET_DEGREE 2
#define BURNING_BULLET_DAMAGE 25
#define BURNING_BULLET_DEGREE 2
#define DEFENDING_BULLET_DEGREE 2
#define WEAKENING_BULLET_DEGREE 2
#define TESLA_TOWER_DAMAGE 50
#define TESLA_TOWER_RANGE 9
#define TESLA_TOWER_SELF_DAMAGE 20
#define DEFEND_SHIELD_HALF_LENGTH 4
#define DEFEND_SHIELD_HALF_HEIGHT 4

// skills id
#define SKILL_PLAYER_SHOOT 0
#define SKILL_PLACE_TESLA 1
#define SKILL_PLACE_LAVA_TOWER 2
#define SKILL_PLAYER_SHOOT_3 3
#define SKILL_PLAYER_SHOOT_FREEZE 4
#define SKILL_PLAYER_SHOOT_BURNING 5
#define SKILL_PLAYER_SHOOT_WEAKING 6
#define SKILL_DEFEND_SHEILD 7

#define CURRENT_SKILL_NUM 3

// unit type id
// #define UNIT_TYPE_PLAYER_OBJECT 100   Defined in processor.h
#define UNIT_TYPE_OBSTACLE_WALL 101
#define UNIT_TYPE_OBSTACLE_GREY_WALL 102
#define UNIT_TYPE_OBSTACLE_TREE 103
#define UNIT_TYPE_OBSTACLE_STONE 104
#define UNIT_TYPE_ORDINARY_BULLET 111
#define UNIT_TYPE_TEST_OBJECT 107
#define UNIT_TYPE_TESLA_TOWER 108
#define UNIT_TYPE_SKILL_BOX 109
#define UNIT_TYPE_LAVA_TOWER 110
#define UNIT_TYPE_FREEZE_BULLET 112
#define UNIT_TYPE_FIRE_BULLET 113
#define UNIT_TYPE_WEAKENING_BULLET 114

#define CURRENT_SPECIAL_BULLET_NUM 3

#include "../object/object.h"

typedef struct ini{
    BOOL auto_load_anime;
    BOOL four_direction_image;
    BOOL default_object;
    BOOL persist_object;

    int type_id;
    int type;
    int max_hp;
    int length;
    int height;
    int interval;
    int image_none_ori_id;
    int image_up_id;
    int image_down_id;
    int image_left_id;
    int image_right_id;
}ini;

typedef struct PlayerObjectStorage{
    int player_direction_key;
    int player_attack_key;
    int player_change_skill_key;
    int player_use_skill_key;
    int attack_interval;
    int skill_interval;
    int spetial_bullet_type;
    int spetial_bullet_remain;
} PlayerObjectStorage;

Object* init_object(ini init, int side);

// units
Object* create_obstacle_object(int type_id);
Object* create_skill_box();
Object* create_bullet_box();
Object* create_ordinary_bullet_object(int side);
Object* create_freeze_bullet_object(int side);
Object* create_burning_bullet_object(int side);
Object* create_weaking_bullet_object(int side);
Object* create_player_object(int side);
Object* create_tesla_tower_object(int side);
Object* create_lava_tower_object(int side);
Object* create_freeze_tower_object(int side);

// skills
void get_skill_map(SkillFunc* skill_map, int* skill_num);

void player_shoot(Object* self, void* param);
void place_tesla(Object* self, void* param);
void place_lava_tower(Object* self, void* param);
void player_shoot_3(Object* self, void* param);
void player_shoot_freeze(Object* self, void* param);
void player_shoot_burning(Object* self, void* param);
void player_shoot_weaking(Object* self, void* param);
void defend_sheild(Object* self, void* param);

// utils
void place_skill_box(Processor* pro, int x, int y);
void place_bullet_box(Processor* pro, int x, int y);


