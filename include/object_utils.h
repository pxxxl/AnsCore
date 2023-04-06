# pragma once 
#include "object.h"
#include "processor.h"

void default_set_object_status(Object* object, int hp);

void default_object_birth(void *self);
void default_object_action(void *self);
void default_object_death(void *self);
void default_object_hurt(void *self, int damage);
void default_object_heal(void *self, int heal);
void default_object_freeze(void *self, int degree);
void default_object_burn(void *self, int degree);
void default_object_defend(void *self, int degree);
void default_object_weak(void *self, int degree);