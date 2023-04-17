#pragma once

#include "macros.h"
#include "object.h"
#include "processor.h"


Object* create_obstacle_wall_object();
Object* create_skill_box();
Object* create_ordinary_bullet_object(int side);
Object* create_freeze_bullet_object(int side);
Object* create_burning_bullet_object(int side);
Object* create_defending_bullet_object(int side);
Object* create_weaking_bullet_object(int side);
Object* create_player_object(int side);
