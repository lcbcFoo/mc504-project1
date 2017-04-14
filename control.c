/* Implementation of the control functions */

#include "threads.h"
#include "graphics.h"
#include "control.h"
#include <ncurses.h>
#include <stdlib.h>

void start_animation(){
    mode = inital_message();

    if(mode == 0)
        normal_mode();
    else if(mode == 1)
        starvation_mode();
    else
        deadlock_mode();

    refresh();
    starvation_mode();
}

void normal_mode(){
    start_delay[0] = 5;
    start_delay[1] = 1;
    start_delay[2] = 3;
    start_delay[3] = 1;
    start_delay[4] = 3;

    sleeping_time[0] = 2;
    sleeping_time[1] = 3;
    sleeping_time[2] = 1;
    sleeping_time[3] = 3;
    sleeping_time[4] = 1;

    writing_time[0] = 1;
    writing_time[1] = 1;
    writing_time[2] = 2;
    writing_time[3] = 1;
    writing_time[4] = 1;


    pthread_t thr[N];
    int i, students_id[N];

    sem_init(&semaphore, 0, 1);
    sem_init(&sem_questions, 0, 1);
    sem_init(&sem_pen, 0, 1);
    total_questions = 0;
    for (i = 0; i < N; i++) {
        pens[i] = -1;
        students_id[i] = i;
        sem_init(&students[i], 0, 0);
        states[i] = T;
        questions[i] = 0;
    }

    display();

    for (i = 0; i < N; i++)
        pthread_create(&thr[i], NULL, student_function, (void*) &students_id[i]);

    for (i = 0; i < N; i++)
        pthread_join(thr[i], NULL);
}

void starvation_mode(){
    start_delay[0] = 1;
    start_delay[1] = 6;
    start_delay[2] = 1;
    start_delay[3] = 1;
    start_delay[4] = 6;

    sleeping_time[0] = 0;
    sleeping_time[1] = 1;
    sleeping_time[2] = 1;
    sleeping_time[3] = 1;
    sleeping_time[4] = 1;

    writing_time[0] = 5;
    writing_time[1] = 1;
    writing_time[2] = 1;
    writing_time[3] = 1;
    writing_time[4] = 1;


    pthread_t thr[N];
    int i, students_id[N];

    sem_init(&semaphore, 0, 1);
    sem_init(&sem_questions, 0, 1);
    sem_init(&sem_pen, 0, 1);
    total_questions = 0;
    for (i = 0; i < N; i++) {
        pens[i] = -1;
        students_id[i] = i;
        sem_init(&students[i], 0, 0);
        states[i] = T;
        questions[i] = 0;
    }

    display();

    for (i = 0; i < N; i++)
        pthread_create(&thr[i], NULL, student_function, (void*) &students_id[i]);

    for (i = 0; i < N; i++)
        pthread_join(thr[i], NULL);
}

void deadlock_mode(){
    start_delay[0] = 1;
    start_delay[1] = 1;
    start_delay[2] = 1;
    start_delay[3] = 1;
    start_delay[4] = 1;

    sleeping_time[0] = 1;
    sleeping_time[1] = 1;
    sleeping_time[2] = 1;
    sleeping_time[3] = 1;
    sleeping_time[4] = 1;

    writing_time[0] = 1;
    writing_time[1] = 1;
    writing_time[2] = 1;
    writing_time[3] = 1;
    writing_time[4] = 1;


    pthread_t thr[N];
    int i, students_id[N];

    sem_init(&semaphore, 0, 1);
    sem_init(&sem_questions, 0, 1);
    sem_init(&sem_pen, 0, 1);
    total_questions = 0;
    for (i = 0; i < N; i++) {
        pens[i] = -1;
        students_id[i] = i;
        sem_init(&students[i], 0, 0);
        states[i] = T;
        questions[i] = 0;
    }

    display();

    for (i = 0; i < N; i++)
        pthread_create(&thr[i], NULL, student_function, (void*) &students_id[i]);

    for (i = 0; i < N; i++)
        pthread_join(thr[i], NULL);
}
