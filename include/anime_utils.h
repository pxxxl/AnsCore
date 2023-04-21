#include "anime.h"
#include "processor.h"

void add_fixed_effect(Processor* host, int x, int y, int tag, int delay);
void add_fixed_sustaining_effect(Processor* host, int x, int y, int tags[], int length);
void add_move_effect(Processor* host, int x, int y, int des_x, int des_y, int tag, int delay);