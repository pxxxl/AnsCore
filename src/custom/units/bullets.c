#include "../custom.h"
#include <stdlib.h>

extern ini BulletOrdinaryIni;
extern ini BulletFreezeIni;
extern ini BulletBurningIni;
extern ini BulletWeakingIni;

void ordinary_bullet_action(Object* self);
void freeze_bullet_action(Object* self);
void burning_bullet_action(Object* self);
void defending_bullet_action(Object* self);
void weaking_bullet_action(Object* self);

static void ordinary_bullet_hit(Object* self, Object* target, int damage){
    self->api->request_hurt(self->host, self, target, damage);
}

static void freeze_bullet_hit(Object* self, Object* target, int degree){
    self->api->request_freeze(self->host, self, target, degree);
}

static void burning_bullet_hit(Object* self, Object* target, int degree){
    //self->api->request_burn(self->host, self, target, degree);
    self->api->request_hurt(self->host, self, target, 100);
}

static void weaking_bullet_hit(Object* self, Object* target, int degree){
    //self->api->request_weak(self->host, self, target, degree);
    self->api->request_hurt(self->host, self, target, 100);
}

// state: move or hit or edge suiside
// when move, add a move (current_place -> next_place) anime
// when hit, add a bomb (next_place) anime
// when edge suiside, nothing

void bullet_move_and_hit_action(Object* self, void (*bullet_hit)(Object* self, Object* target, int degree), int damage, int anime_tag, int boom_anime_tags[], int boom_length){
    int x = self->block->x;
    int y = self->block->y;
    int target_x = x;
    int target_y = y;
    int side = self->config.side;
    int ori = self->block->orientation;
    switch(ori){
        case UP: target_y-=1; break;
        case DOWN: target_y+=1; break;
        case LEFT: target_x-=1; break;
        case RIGHT: target_x+=1; break;
    }

    Object* check = self->api->detect_exist_object(self->host, target_x, target_y, target_x + 1, target_y + 1);
    if(check == NULL){
        if(self->api->is_valid_address(self->host, target_x, target_y)){
            self->api->request_step(self->host, self, ori);
        }else{
            self->api->request_suiside(self->host, self);
        }
    }else{
        //check = self->api->find_closest_object_in_direction(self->host, self, ori);
        if(self->api->cannot_hurt(self->host, self, check)){
            self->api->request_suiside(self->host, self);
        }else{
            bullet_hit(self, check, damage);
            self->api->request_suiside(self->host, self);
            self->api->request_load_static_sustaining_effect(self->host, target_x-1, target_y-1, boom_anime_tags, boom_length, 0);
        }
    }
}


Object* create_ordinary_bullet_object(int side){
    Object* obs = init_object(BulletOrdinaryIni, side);
    obs->action = ordinary_bullet_action;
    return obs;
}

Object* create_freeze_bullet_object(int side){
    Object* obs = init_object(BulletFreezeIni, side);
    obs->action = freeze_bullet_action;
    return obs;
}

Object* create_burning_bullet_object(int side){
    Object* obs = init_object(BulletBurningIni, side);
    obs->action = burning_bullet_action;
    return obs;
}

Object* create_weaking_bullet_object(int side){
    Object* obs = init_object(BulletWeakingIni, side);
    obs->action = weaking_bullet_action;
    return obs;
}

void ordinary_bullet_action(Object* self){
    int anime_tag = 401;
    int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
    bullet_move_and_hit_action(self, ordinary_bullet_hit, ORDINARY_BULLET_DAMAGE, anime_tag, boom_tags, 10);
}

void freeze_bullet_action(Object* self){
    int anime_tag = 401;
    int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
    bullet_move_and_hit_action(self, freeze_bullet_hit, FREEZING_BULLET_DAMAGE, anime_tag, boom_tags, 10);
}

void burning_bullet_action(Object* self){
    int anime_tag = 401;
    int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
    bullet_move_and_hit_action(self, burning_bullet_hit, BURNING_BULLET_DAMAGE, anime_tag, boom_tags, 10);
}

void weaking_bullet_action(Object* self){
    int anime_tag = 401;
    int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
    bullet_move_and_hit_action(self, weaking_bullet_hit, 0 , anime_tag, boom_tags, 10);
}



