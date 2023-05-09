#include "../custom.h"
void get_skill_map(SkillFunc* skill_map, int* skill_num){
    *skill_num = CURRENT_SKILL_NUM;
    skill_map[0] = player_shoot;
    skill_map[1] = place_tesla;
    skill_map[2] = place_lava_tower;
    skill_map[3] = player_shoot_3;
    skill_map[4] = defend_sheild;
    skill_map[5] = place_ice_tower;
    skill_map[6] = place_cannon_tower;
    skill_map[7] = place_laser_tank;
    skill_map[8] = place_boomer_tank;
    skill_map[9] = place_chrono_infantry;
    skill_map[10] = place_normal_infantry;
    skill_map[11] = place_laser_infantry;
}
