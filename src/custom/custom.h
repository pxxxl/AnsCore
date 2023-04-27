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

// skills id
#define SKILL_PLAYER_SHOOT 0
#define SKILL_PLACE_TESLA 1
#define SKILL_PLACE_LAVA_TOWER 2

#define CURRENT_SKILL_NUM 3

// unit type id
// #define UNIT_TYPE_PLAYER_OBJECT 100   Defined in processor.h
#define UNIT_TYPE_OBSTACLE_WALL 101
#define UNIT_TYPE_OBSTACLE_GREY_WALL 102
#define UNIT_TYPE_OBSTACLE_TREE 103
#define UNIT_TYPE_OBSTACLE_STONE 104
#define UNIT_TYPE_ORDINARY_BULLET 106
#define UNIT_TYPE_TEST_OBJECT 107
#define UNIT_TYPE_TESLA_TOWER 108
#define UNIT_TYPE_SKILL_BOX 109
#define UNIT_TYPE_LAVA_TOWER 110
#define UNIT_TYPE_FREEZE_TOWER 111

#include "../object/object.h"

// units
Object* create_obstacle_object(int type_id);
Object* create_skill_box();
Object* create_ordinary_bullet_object(int side);
Object* create_freeze_bullet_object(int side);
Object* create_burning_bullet_object(int side);
Object* create_defending_bullet_object(int side);
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

// utils
void place_skill_box(Processor* pro, int x, int y);
