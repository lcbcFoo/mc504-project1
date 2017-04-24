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
char arqL_name[] = "image_left.txt";
char arqR_name[] = "image_right.txt";
char arqB_name[] = "image_both.txt";

char image[15][30];
char image0[20][30];
char image10[20][30];
char imageL[15][30];
char imageR[15][30];
char imageB[15][30];


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

    /* Read image file */
    arq = fopen(arqL_name, "r");

    if(arq == NULL)
        exit(0);

    i = 0;
    while(fgets(imageL[i++], sizeof(imageL), arq));
    fclose(arq);

    /* Read image file */
    arq = fopen(arqR_name, "r");

    if(arq == NULL)
        exit(0);

    i = 0;
    while(fgets(imageR[i++], sizeof(imageR), arq));
    fclose(arq);

    /* Read image file */
    arq = fopen(arqB_name, "r");

    if(arq == NULL)
        exit(0);

    i = 0;
    while(fgets(imageB[i++], sizeof(imageB), arq));
    fclose(arq);


    attron(COLOR_PAIR(1));
    mvprintw(5,0,"This is a variation of the Dinning Philosophers problem: The Problem of the Desperate Students!\n\n\n\n     Choose which mode you want to see:\n\n\n");

    attron(COLOR_PAIR(3));
    printw("1)");
    attron(COLOR_PAIR(1));
    printw(" MC102 - Everybody passes! (Synchronized threads)\n\n");
    attron(COLOR_PAIR(5));
    printw("2)");
    attron(COLOR_PAIR(1));
    printw(" MC404 - Someone is left behind... (Starvation problem)\n\n");
    attron(COLOR_PAIR(2));
    printw("3)");
    attron(COLOR_PAIR(1));
    printw(" MEC G - No one shall pass! (Deadlock problem)\n");
    move(45,0);
    refresh();

    char get;

    do{
        scanf(" %c", &get);
    }while(get > '4' || get < '1');

    clear();
    return (int) get - '1';
}

void display(){
    sem_wait(&sem_graphics);
    clear();
    int aux = 0;
    /* Graphics implementation based on the .txt files */
    for(int i = 0; i < N; i++){
        aux = 3;
        move(3, i * (IMAGE_COLUMN + aux));
        if(states[i] == W)
            printw("I am writing!");
        else if(states[i] == T)
            printw("I think I know nothing .-.");
        else if((pens[i] == i || (pens[(i + 1) % N]) == i))
            printw("I need one more pen...");
        else
            printw("I HAVE NO PEN!!!");
    }

    for(int i = 0; i < N; i++){
        int aux = 0;
        if(states[i] == W){
            attron(COLOR_PAIR(3));
            for(int j = 0; j < 15; j++){
                aux = 3;
                move(IMAGE_ROW + j, i * (IMAGE_COLUMN + aux));
                printw("%s", imageB[j]);
            }
        }

        else if(states[i] == T){
            attron(COLOR_PAIR(4));
            for(int j = 0; j < 15; j++){
                aux = 3;
                move(IMAGE_ROW + j, i * (IMAGE_COLUMN + aux));
                printw("%s", image[j]);
            }
        }

        else if(pens[i] == i && pens[(i + 1) % N] != i){
            attron(COLOR_PAIR(5));
            for(int j = 0; j < 15; j++){
                aux = 3;
                move(IMAGE_ROW + j, i * (IMAGE_COLUMN + aux));
                printw("%s", imageL[j]);
            }
        }
        else if(pens[(i + 1) % N] == i && pens[i] != i){
            attron(COLOR_PAIR(5));
            for(int j = 0; j < 15; j++){
                aux = 3;
                move(IMAGE_ROW + j, i * (IMAGE_COLUMN + aux));
                printw("%s", imageR[j]);
            }
        }
        else if(pens[i] == i && pens[(i + 1) % N] == i){
            attron(COLOR_PAIR(3));
            for(int j = 0; j < 15; j++){
                aux = 3;
                move(IMAGE_ROW + j, i * (IMAGE_COLUMN + aux));
                printw("%s", imageB[j]);
            }
            move(3, i * (IMAGE_COLUMN + aux));
            attron(COLOR_PAIR(1));
            printw("UHUUUUUUUUUUUUUUUUUUUL!");

        }
        else{
            attron(COLOR_PAIR(2));
            for(int j = 0; j < 15; j++){
                aux = 3;
                move(IMAGE_ROW + j, i * (IMAGE_COLUMN + aux));
                printw("%s", image[j]);
            }
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
    sem_post(&sem_graphics);
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
