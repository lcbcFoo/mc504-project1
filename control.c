/* Implementation of the control functions */

#include "threads.h"
#include "graphics.h"
#include "control.h"
#include <ncurses.h>
#include <stdlib.h>

void start_animation(){
    mode = inital_message();
    define_mode_times();
    start_mode();
}

void start_mode(){

    pthread_t thr[N];
    int i, students_id[N];

    sem_init(&semaphore, 0, 1);
    sem_init(&sem_questions, 0, 1);
    sem_init(&sem_graphics, 0, 1);
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


void define_mode_times(){
    if(mode == 0){
        start_delay[0] = 2;
        start_delay[1] = 12;
        start_delay[2] = 2;
        start_delay[3] = 2;
        start_delay[4] = 12;

        sleeping_time[0] = 0;
        sleeping_time[1] = 2;
        sleeping_time[2] = 2;
        sleeping_time[3] = 2;
        sleeping_time[4] = 2;

        writing_time[0] = 10;
        writing_time[1] = 2;
        writing_time[2] = 2;
        writing_time[3] = 2;
        writing_time[4] = 2;
    }

    else if(mode == 1){
        start_delay[0] = 2;
        start_delay[1] = 1;
        start_delay[2] = 6;
        start_delay[3] = 2;
        start_delay[4] = 4;

        sleeping_time[0] = 4;
        sleeping_time[1] = 2;
        sleeping_time[2] = 6;
        sleeping_time[3] = 6;
        sleeping_time[4] = 2;

        writing_time[0] = 2;
        writing_time[1] = 6;
        writing_time[2] = 2;
        writing_time[3] = 2;
        writing_time[4] = 6;
    }

    else{
        start_delay[0] = 1;
        start_delay[1] = 2;
        start_delay[2] = 3;
        start_delay[3] = 4;
        start_delay[4] = 5;

        sleeping_time[0] = 6;
        sleeping_time[1] = 1;
        sleeping_time[2] = 4;
        sleeping_time[3] = 2;
        sleeping_time[4] = 1;

        writing_time[0] = 2;
        writing_time[1] = 4;
        writing_time[2] = 2;
        writing_time[3] = 2;
        writing_time[4] = 2;
    }
}
