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

#include "../macros.h"
#include "../object/object.h"
#include "../processor/processor.h"

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
Object* create_freeze_tower_object(int side);

// skills
void player_shoot(Object* self, int type_id);
void place_tesla(Object* self);
