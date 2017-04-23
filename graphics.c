/* Implementation of the graphic-related functions */

#include "graphics.h"
#include "threads.h"
#include <unistd.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define IMAGE_ROW 5
#define IMAGE_COLUMN 30

char arq_name[] = "image.txt";
char arq0_name[] = "image0.txt";
char arq10_name[] = "image10.txt";

char image[15][30];
char image0[20][30];
char image10[20][30];


int inital_message(){
    /* Read image file */
    FILE* arq = fopen(arq_name, "r");

    if(arq == NULL)
        exit(0);

    int i = 0;
    while(fgets(image[i++], sizeof(image), arq));
    fclose(arq);

    /* Read image file */
    arq = fopen(arq0_name, "r");

    if(arq == NULL)
        exit(0);

    i = 0;
    while(fgets(image0[i++], sizeof(image0), arq));
    fclose(arq);

    /* Read image file */
    arq = fopen(arq10_name, "r");

    if(arq == NULL)
        exit(0);

    i = 0;
    while(fgets(image10[i++], sizeof(image10), arq));
    fclose(arq);

    attron(COLOR_PAIR(1));
    mvprintw(5,0,"This is the Desperate Students (a variation of the dinning philosophers problem) animation!\n\nChoose which mode you want to see:\n\n");

    attron(COLOR_PAIR(3));
    printw("1)");
    attron(COLOR_PAIR(1));
    printw(" MC 102 - Everybody passes! (Synchronized threads)\n");
    attron(COLOR_PAIR(5));
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
    int aux = 0;
    /* Implementar os desenhos */
    for(int i = 0; i < N; i++){
        aux = 3;
        move(3, i * (IMAGE_COLUMN + aux));
        if(states[i] == W)
            printw("I am writing!");
        else if(states[i] == T)
            printw("I think I know nothing .-.");
        else if((pens[i] == i || (pens[i + 1]) % N == i))
            printw("I need one more pen...");
        else
            printw("I HAVE NO PEN!!!");
    }

    for(int i = 0; i < N; i++){
        if(states[i] == W)
            attron(COLOR_PAIR(3));
        else if(states[i] == T)
            attron(COLOR_PAIR(4));
        else if(pens[i] == i || (pens[i + 1]) % N == i)
            attron(COLOR_PAIR(5));
        else
            attron(COLOR_PAIR(2));

        int aux = 0;
        for(int j = 0; j < 15; j++){
            aux = 3;
            move(IMAGE_ROW + j, i * (IMAGE_COLUMN + aux));
            printw("%s", image[j]);
        }
    }

    move(27,0);
    attron(COLOR_PAIR(1));
    printw("Colors:\n\n");
    attron(COLOR_PAIR(3));
    printw("Green: Writing\n");
    attron(COLOR_PAIR(4));
    printw("Blue: Thinking\n");
    attron(COLOR_PAIR(5));
    printw("Yellow: Desperate (has 1 pen)\n");
    attron(COLOR_PAIR(2));
    printw("Red: REALLY DESPERATE (no pens)\n");

    attron(COLOR_PAIR(1));
    for(int i = 0; i < N; i++){
        aux = 3;
        move(23, i * (IMAGE_COLUMN + aux) + 7);
        printw("Answers: %d", questions[i]);
    }
    move(45,0);
    refresh();
}

void final_layout(){
    sem_wait(&semaphore);
    clear();

    clear();
    int aux = 0;

    for(int i = 0; i < N; i++){
        aux = 3;
        move(3, i * (IMAGE_COLUMN + aux));
        if(questions[i])
            printw(" MOM, I PASSED!!!");
        else
            printw("    Damn it...");
    }

    for(int i = 0; i < N; i++){
        if(questions[i])
            attron(COLOR_PAIR(3));
        else
            attron(COLOR_PAIR(2));

        for(int j = 0; j < 20; j++){
            int aux = 3;
            move(IMAGE_ROW + j, i * (IMAGE_COLUMN + aux));
            if(questions[i])
                printw("%s", image10[j]);
            else
                printw("%s", image0[j]);
        }
    }

    attron(COLOR_PAIR(1));
    for(int i = 0; i < N; i++){
        aux = 3;
        move(25, i * (IMAGE_COLUMN + aux) + 4);
        printw("Answers: %d", questions[i]);
    }

    printw("\n\n\nTotal Answers: %d\n", total_questions);
    move(45,0);
    refresh();
    while(1);
}
