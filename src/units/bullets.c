#include "../../include/units.h"
#include "../../include/object_utils.h"

Object* create_ordinary_bullet_object(int side){
    Object* obs = (Object*)malloc(sizeof(Object));
    if(side != RED_BULLET && side != BLUE_BULLET){
        printf("Error: create_ordinary_bullet_object: side is not valid");
        exit(1);
    }
    set_object_config(obs, 106, side, 1, BULLET_OBJECT_INTERVAL);
    set_object_status(obs, 1);
    obs->storage = NULL;
    obs->birth = default_object_birth;
    obs->action = ordinary_bullet_action;
    obs->death = default_object_death;
    obs->hurt = default_persist_affect;
    obs->heal = default_persist_affect;
    obs->freeze = default_persist_affect;
    obs->burn = default_persist_affect;
    obs->defend = default_persist_affect;
    obs->weak = default_persist_affect;
    return obs;
}

Object* create_freeze_bullet_object(int side){
    Object* obs = (Object*)malloc(sizeof(Object));
    if(side != RED_BULLET && side != BLUE_BULLET){
        printf("Error: create_ordinary_bullet_object: side is not valid");
        exit(1);
    }
    set_object_config(obs, 106, side, 1, BULLET_OBJECT_INTERVAL);
    set_object_status(obs, 1);
    obs->storage = NULL;
    obs->birth = default_object_birth;
    obs->action = freeze_bullet_action;
    obs->death = default_object_death;
    obs->hurt = default_persist_affect;
    obs->heal = default_persist_affect;
    obs->freeze = default_persist_affect;
    obs->burn = default_persist_affect;
    obs->defend = default_persist_affect;
    obs->weak = default_persist_affect;
    return obs;
}

Object* create_burning_bullet_object(int side){
    Object* obs = (Object*)malloc(sizeof(Object));
    if(side != RED_BULLET && side != BLUE_BULLET){
        printf("Error: create_ordinary_bullet_object: side is not valid");
        exit(1);
    }
    set_object_config(obs, 106, side, 1, BULLET_OBJECT_INTERVAL);
    set_object_status(obs, 1);
    obs->storage = NULL;
    obs->birth = default_object_birth;
    obs->action = burning_bullet_action;
    obs->death = default_object_death;
    obs->hurt = default_persist_affect;
    obs->heal = default_persist_affect;
    obs->freeze = default_persist_affect;
    obs->burn = default_persist_affect;
    obs->defend = default_persist_affect;
    obs->weak = default_persist_affect;
    return obs;
}

Object* create_defending_bullet_object(int side){
    Object* obs = (Object*)malloc(sizeof(Object));
    if(side != RED_BULLET && side != BLUE_BULLET){
        printf("Error: create_ordinary_bullet_object: side is not valid");
        exit(1);
    }
    set_object_config(obs, 106, side, 1, BULLET_OBJECT_INTERVAL);
    set_object_status(obs, 1);
    obs->storage = NULL;
    obs->birth = default_object_birth;
    obs->action = defending_bullet_action;
    obs->death = default_object_death;
    obs->hurt = default_persist_affect;
    obs->heal = default_persist_affect;
    obs->freeze = default_persist_affect;
    obs->burn = default_persist_affect;
    obs->defend = default_persist_affect;
    obs->weak = default_persist_affect;
    return obs;
}

Object* create_weaking_bullet_object(int side){
    Object* obs = (Object*)malloc(sizeof(Object));
    if(side != RED_BULLET && side != BLUE_BULLET){
        printf("Error: create_ordinary_bullet_object: side is not valid");
        exit(1);
    }
    set_object_config(obs, 106, side, 1, BULLET_OBJECT_INTERVAL);
    set_object_status(obs, 1);
    obs->storage = NULL;
    obs->birth = default_object_birth;
    obs->action = weaking_bullet_action;
    obs->death = default_object_death;
    obs->hurt = default_persist_affect;
    obs->heal = default_persist_affect;
    obs->freeze = default_persist_affect;
    obs->burn = default_persist_affect;
    obs->defend = default_persist_affect;
    obs->weak = default_persist_affect;
    return obs;
}

static void ordinary_bullet_action(Object* self){
    int anime_tag = 401;
    int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
    bullet_move_and_hit_action(self, ordinary_bullet_hit, anime_tag, boom_tags, 10);
}

static void freeze_bullet_action(Object* self){
    int anime_tag = 401;
    int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
    bullet_move_and_hit_action(self, freeze_bullet_hit, anime_tag, boom_tags, 10);
}

static void burning_bullet_action(Object* self){
    int anime_tag = 401;
    int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
    bullet_move_and_hit_action(self, burning_bullet_hit, anime_tag, boom_tags, 10);
}

static void defending_bullet_action(Object* self){
    int anime_tag = 401;
    int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
    bullet_move_and_hit_action(self, defending_bullet_hit, anime_tag, boom_tags, 10);
}

static void weaking_bullet_action(Object* self){
    int anime_tag = 401;
    int boom_tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
    bullet_move_and_hit_action(self, weaking_bullet_hit, anime_tag, boom_tags, 10);
}

static void bullet_move_and_hit_action(Object* self, void (*bullet_hit)(Object* self, Object* target, int degree), int anime_tag, int boom_anime_tags[], int boom_length){
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

    Object* check = self->api->detect_exist_object(self->host, x, y, target_x, target_y);
    if(check == NULL){
        if(self->api->is_valid_address(self->host, target_x, target_y)){
            self->api->request_step(self->host, self, ori);
            bullet_anime_action(self, anime_tag, boom_anime_tags, boom_length, FALSE);
        }else{
            self->api->request_suiside(self->host, self);
        }
    }else{
        check = self->api->find_closest_object_in_direction(self->host, self, ori);
        if(self->api->cannot_hurt(self->host, self, check)){
            self->api->request_suiside(self->host, self);
        }else{
            bullet_hit(self, check, 1);
            self->api->request_suiside(self->host, self);
            bullet_anime_action(self, anime_tag, boom_anime_tags, boom_length, TRUE);
        }
    }
}

// state: move or hit or edge suiside
// when move, add a move (current_place -> next_place) anime
// when hit, add a bomb (next_place) anime
// when edge suiside, nothing
static void bullet_anime_action(Object* self, int anime_tag, int boom_anime_tags[], int boom_length, BOOL hitted){
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

    if(!hitted){
        //move or at edge suiside
        if(self->api->going_out_of_bound(self->host, self, self->block->orientation)){
            // no anime effect
            return;
        }else{
            add_move_effect(self->host, x, y, target_x, target_y, anime_tag, 0);
        }
    }else{
        //hit
        int tags[10] = {301, 302, 303, 304, 305, 306, 307, 308, 309, 310};
        add_fixed_sustaining_effect(self->host, target_x, target_y, boom_anime_tags, boom_length);
    }
}

static void ordinary_bullet_hit(Object* self, Object* target, int damage){
    self->api->request_hurt(self->host, self, target, damage);
}

static void freeze_bullet_hit(Object* self, Object* target, int degree){
    self->api->request_freeze(self->host, self, target, degree);
}

static void burning_bullet_hit(Object* self, Object* target, int degree){
    self->api->request_burn(self->host, self, target, degree);
}

static void defending_bullet_hit(Object* self, Object* target, int degree){
    self->api->request_defend(self->host, self, target, degree);
}

static void weaking_bullet_hit(Object* self, Object* target, int degree){
    self->api->request_weak(self->host, self, target, degree);
}

