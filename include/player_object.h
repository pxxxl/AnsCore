#pragma once

#include "macros.h"
#include "object.h"
#include "processor.h"

Object* create_player_object();

void player_object_init(void *self);
void player_object_birth(void *self);
void player_object_action(void *self);
void player_object_death(void *self);
void player_object_hurt(void *self, int damage);
void player_object_heal(void *self, int heal);
void player_object_freeze(void *self, int degree);
void player_object_burn(void *self, int degree);
void player_object_defend(void *self, int degree);
void player_object_weak(void *self, int degree);