/* Implementation of the graphic-related functions */

#include "graphics.h"
#include "threads.h"
#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>



int inital_message(){
    attron(COLOR_PAIR(1));
    mvprintw(0,0,"This is the Desperate Students (a variation of the dinning philosophers problem) animation!\n\nChoose which mode you want to see:\n\n");

    attron(COLOR_PAIR(4));
    printw("1)");
    attron(COLOR_PAIR(1));
    printw(" MC 102 - Everybody passes! (Synchronized threads)\n");
    attron(COLOR_PAIR(3));
    printw("2)");
    attron(COLOR_PAIR(1));
    printw(" MC 404 - Someone is left behind... (Starvation problem)\n");
    attron(COLOR_PAIR(2));
    printw("3)");
    attron(COLOR_PAIR(1));
    printw(" MC X58 - No one shall pass! (Deadlock problem)\n");
    refresh();

    char get;

    do{
        scanf(" %c", &get);
    }while(get > '3' || get < '1');

    clear();
    return (int) get - '1';
}

void display(){
    clear();
    printw("display\n");
    move(5, 0);
    /* Implementar os desenhos */
    for(int i = 0; i < N; i++){
        if(states[i] == W)
            printw("W ");
        else if(states[i] == T)
            printw("T ");
        else
            printw("D ");
    }


    move(25, 0);
    attron(COLOR_PAIR(1));
    printw("Questions answered:\n\n");
    for(int i = 0; i < N; i++){
        printw("Student %d: %d\n", i, questions[i]);
    }
    printw("\n\nTotal: %d\n", total_questions);

    refresh();
}

void final_layout(){
    sem_wait(&semaphore);
    clear();
    attron(COLOR_PAIR(1));
    printw("Questions answered:\n\n");
    for(int i = 0; i < N; i++){
        printw("Student %d: %d\n", i, questions[i]);
    }
    printw("\n\nTotal: %d\n", total_questions);
    refresh();
    while(1);
}
