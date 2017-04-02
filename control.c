/* Implementation of the control functions */

#include "control.h"
#include <ncurses.h>
#include <stdlib.h>

void start_animation(){
    int mode = inital_message();
    printw("mode: %d\n", mode);

    refresh();
    while(1);
}
