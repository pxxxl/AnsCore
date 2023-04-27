#include "../custom.h"
void get_skill_map(SkillFunc* skill_map, int* skill_num){
    *skill_num = CURRENT_SKILL_NUM;
    skill_map[0] = player_shoot;
    skill_map[1] = place_tesla;
    skill_map[2] = place_lava_tower;
}
