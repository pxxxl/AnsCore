#include "../custom.h"

// Obstacle_wall
Object* create_obstacle_object(int type_id){
    Object* obs = (Object*)malloc(sizeof(Object));
    set_object_config(obs, 101, NEUTRAL, 65535, 3, 3, 5, TRUE, OBSTACLE);
    set_object_status(obs, 65535);
    int imageid = 0;
    switch(type_id){
        case 101: imageid = 101; break;
        case 102: imageid = 104; break;
        case 103: imageid = 103; break;
        case 104: imageid = 102; break;
    }
    set_object_anime(obs, FALSE, imageid, imageid, imageid, imageid, imageid);
    obs->birth = default_object_birth;
    obs->action = default_object_action;
    obs->death = default_object_death;
    obs->hurt = default_persist_affect;
    obs->heal = default_persist_affect;
    obs->freeze = default_persist_affect;
    obs->burn = default_persist_affect;
    obs->defend = default_persist_affect;
    obs->weak = default_persist_affect;
    return obs;
}
