/* Implementation of the threads-related functions */
#include "threads.h"
#include "graphics.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


void think(int student_id){
    sleep(sleeping_time[student_id]);
}

void check_pens(int student_id){
    if(states[student_id] == D && check_left(student_id) && check_right(student_id)){
        states[student_id] = W;
        display();
        sem_post(&students[student_id]);
    }

    sem_post(&sem_pen);
}

int check_left(int student_id) {
    if(pens[student_id] == -1){
        pens[student_id] = student_id;
        display();
        sleep(1);
        return 1;
    }
    else if(pens[student_id] == student_id)
        return 1;
    return 0;
}

int check_right(int student_id){
    if(pens[RIGHT] == -1){
        pens[RIGHT] = student_id;
        display();
        sleep(1);
        return 1;
    }
    return 0;
}

void pick_pens(int student_id){
    sem_wait(&semaphore);
    states[student_id] = D;
    display();
    check_pens(student_id);
    sem_post(&semaphore);
    sem_wait(&students[student_id]);
}

void writing(int student_id){
    sem_wait(&sem_questions);
    questions[student_id]++;
    total_questions++;

    if(total_questions == MAX)
        final_layout();

    sem_post(&sem_questions);

    sleep(writing_time[student_id]);
}

void release_pens(int student_id){
    sem_wait(&semaphore);
    states[student_id] = T;

    pens[RIGHT] = -1;
    pens[student_id] = -1;

    display();

    if(mode == 0){
        check_pens(LEFT);
        check_pens(RIGHT);
    }
    sem_post(&semaphore);
}

void* student_function(void* v){
    int student_id = *(int *) v;

    sleep(start_delay[student_id]);

    while(1){
        pick_pens(student_id);
        writing(student_id);
        release_pens(student_id);
        think(student_id);
    }
}
