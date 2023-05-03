#include "../custom.h"

ini ObstacalTreeIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = FALSE,
    .persist_object = TRUE,

    .type_id = 103,
    .type = OBSTACLE,
    .max_hp = 65535,
    .length = 3,
    .height = 3,
    .interval = 500,
    .image_none_ori_id = 103,
};

ini ObstacalWallIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = FALSE,
    .persist_object = TRUE,

    .type_id = 101,
    .type = OBSTACLE,
    .max_hp = 65535,
    .length = 3,
    .height = 3,
    .interval = 500,
    .image_none_ori_id = 101,
};

ini ObstacalStoneIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = FALSE,
    .persist_object = TRUE,

    .type_id = 104,
    .type = OBSTACLE,
    .max_hp = 65535,
    .length = 3,
    .height = 3,
    .interval = 500,
    .image_none_ori_id = 102,
};

ini ObstacalGreyWallIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = FALSE,
    .persist_object = TRUE,

    .type_id = 102,
    .type = OBSTACLE,
    .max_hp = 65535,
    .length = 3,
    .height = 3,
    .interval = 500,
    .image_none_ori_id = 102,
};

ini PlayerObjectAIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = TRUE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 100,
    .type = TANK,
    .max_hp = 500,
    .length = 3,
    .height = 3,
    .interval = 0,
    .image_none_ori_id = 207,
    .image_up_id = 207,
    .image_down_id = 204,
    .image_left_id = 205,
    .image_right_id = 206,
};

ini PlayerObjectBIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = TRUE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 115,
    .type = TANK,
    .max_hp = 500,
    .length = 3,
    .height = 3,
    .interval = 0,
    .image_none_ori_id = 211,
    .image_up_id = 211,
    .image_down_id = 208,
    .image_left_id = 209,
    .image_right_id = 210,
};

ini TeslaTowerIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 108,
    .type = TOWER,
    .max_hp = 300,
    .length = 3,
    .height = 3,
    .interval = 10,
    .image_none_ori_id = 106,
};

ini LavaTowerIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 110,
    .type = TOWER,
    .max_hp = 300,
    .length = 3,
    .height = 3,
    .interval = 5,
    .image_none_ori_id = 108,
};

ini BulletOrdinaryIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 111,
    .type = BULLET,
    .max_hp = 1,
    .length = 1,
    .height = 1,
    .interval = 0,
    .image_none_ori_id = 401,
};

ini BulletFreezeIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 112,
    .type = BULLET,
    .max_hp = 1,
    .length = 1,
    .height = 1,
    .interval = 0,
    .image_none_ori_id = 404,
};

ini BulletBurningIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 113,
    .type = BULLET,
    .max_hp = 1,
    .length = 1,
    .height = 1,
    .interval = 0,
    .image_none_ori_id = 405,
};

ini BulletWeakingIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 114,
    .type = BULLET,
    .max_hp = 1,
    .length = 1,
    .height = 1,
    .interval = 0,
    .image_none_ori_id = 406,
};

ini BulletPackIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 114,
    .type = BULLET,
    .max_hp = 1,
    .length = 1,
    .height = 1,
    .interval = 0,
    .image_none_ori_id = 407,
};

ini SkillPackIni = {
    .auto_load_anime = TRUE,
    .four_direction_image = FALSE,
    .default_object = TRUE,
    .persist_object = FALSE,

    .type_id = 114,
    .type = BULLET,
    .max_hp = 1,
    .length = 1,
    .height = 1,
    .interval = 0,
    .image_none_ori_id = 402,
};


Object* init_object(ini init, int side){
    Object* obj = (Object*)malloc(sizeof(Object));
    set_object_config(
        obj, 
        init.type_id, 
        side, 
        init.max_hp, 
        init.length, 
        init.height, 
        init.interval,
        init.auto_load_anime,
        init.type
    );
    set_object_status(obj, init.max_hp);
    set_object_anime(
        obj,
        init.four_direction_image,
        init.image_up_id,
        init.image_left_id,
        init.image_right_id,
        init.image_down_id,
        init.image_none_ori_id
    );
    obj->storage = NULL;
    obj->birth = default_object_birth;
    obj->action = default_object_action;;
    obj->death = default_object_death;
    if(init.default_object == TRUE){
        obj->hurt = default_object_hurt;
        obj->heal = default_object_heal;
        obj->freeze = default_object_freeze;
        obj->burn = default_object_burn;
        obj->defend = default_object_defend;
        obj->weak = default_object_weak;
    }else if(init.persist_object == TRUE){
        obj->hurt = default_persist_affect;
        obj->heal = default_persist_affect;
        obj->freeze = default_persist_affect;
        obj->burn = default_persist_affect;
        obj->defend = default_persist_affect;
        obj->weak = default_persist_affect;
    }
    return obj;
}