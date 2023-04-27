#include "qt_draw.h"
extern "C"{
    #include "../random.h"
}


extern TWidget* widget;

unsigned randint(){
    return widget->get_rand_0_to_99();
}