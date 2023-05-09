#include "../custom.h"
#include "../../random.h"

extern ini SkillPackIni;
extern ini BulletPackIni;

static void skill_box_action(Object* self){
    Object*** distance_list;
    Object** object_list;
    int length;
    self->api->get_distance_list(self->host, &distance_list, &object_list, &length);
    int i;
    for(i = 0; i < length; i++){
        if(object_list[i] == self){
            break;
        }
    }
    Object** self_distance_list = distance_list[i];
    int j;
    Object* closest_object;
    for(j = 1; j < length; j++){
        closest_object = self_distance_list[j];
        if(closest_object->config.type == UNIT_TYPE_PLAYER_OBJECT_A || closest_object->config.type == UNIT_TYPE_PLAYER_OBJECT_B){
            int sx = self->block->x;
            int sy = self->block->y;
            int cx = closest_object->block->x;
            int cy = closest_object->block->y;
            int length = closest_object->block->length;
            int height = closest_object->block->height;
            int bare_min_x = sx - length;
            int bare_max_x = sx + 1;
            int bare_min_y = sy - height;
            int bare_max_y = sy + 1;
            if(cx <= bare_max_x && cx >= bare_min_x){
                if(cy <= bare_max_y && cy >= bare_min_y){
                    break;
                }
            }
        }
    }
    if(j != length){
        closest_object = self_distance_list[j];
        unsigned rand = randint();
        unsigned chosen = rand % CURRENT_SKILL_NUM;

        // customize chosen skill
        chosen = SKILL_PLACE_BOOMER_TANK;

        self->host->api->give_skill(self->host, closest_object, chosen);
        self->host->api->request_suiside(self->host, self);
    }
}


Object* create_skill_box(){
    Object* obs = init_object(SkillPackIni, NEUTRAL);
    obs->action = skill_box_action;
    return obs;
}

static void bullet_box_action(Object* self){
    Object*** distance_list;
    Object** object_list;
    int length;
    self->api->get_distance_list(self->host, &distance_list, &object_list, &length);
    int i;
    for(i = 0; i < length; i++){
        if(object_list[i] == self){
            break;
        }
    }
    Object** self_distance_list = distance_list[i];
    int j;
    Object* closest_object;
    for(j = 1; j < length; j++){
        closest_object = self_distance_list[j];
        if(closest_object->config.type == UNIT_TYPE_PLAYER_OBJECT_A || closest_object->config.type == UNIT_TYPE_PLAYER_OBJECT_B){
            int sx = self->block->x;
            int sy = self->block->y;
            int cx = closest_object->block->x;
            int cy = closest_object->block->y;
            int length = closest_object->block->length;
            int height = closest_object->block->height;
            int bare_min_x = sx - length;
            int bare_max_x = sx + 1;
            int bare_min_y = sy - height;
            int bare_max_y = sy + 1;
            if(cx <= bare_max_x && cx >= bare_min_x){
                if(cy <= bare_max_y && cy >= bare_min_y){
                    break;
                }
            }
        }
    }
    if(j != length){
        closest_object = self_distance_list[j];
        unsigned rand = randint();
        unsigned chosen = rand % CURRENT_SPECIAL_BULLET_NUM;
        int special_bullet_type = 0;
        switch(chosen){
            case 0: special_bullet_type = UNIT_TYPE_FREEZE_BULLET; break;
            case 1: special_bullet_type = UNIT_TYPE_FIRE_BULLET; break;
            case 2: special_bullet_type = UNIT_TYPE_WEAKENING_BULLET; break;
        }
        PlayerObjectStorage* storage = closest_object->storage;
        storage->spetial_bullet_remain = 10;
        storage->spetial_bullet_type = special_bullet_type;
        self->host->api->request_suiside(self->host, self);
    }
}

Object* create_bullet_box(){
    Object* obs = init_object(BulletPackIni, NEUTRAL);
    obs->action = bullet_box_action;
    return obs;
}


// size 1*1, detect surrounding 3*3, if founded, suicide and give the player a skill