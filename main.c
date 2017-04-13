/* Main file of the project */

#include <ncurses.h>
#include "control.h"


int main(){

    /* Initialize colors support from ncurses.h */
	initscr();
	start_color();

	/* Define color pairs */
	init_pair(1,COLOR_WHITE,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_BLACK);
	bkgd(COLOR_PAIR(1));
    refresh();

    /* Starts animation */
    start_animation();
    endwin();

    return 0;
}
