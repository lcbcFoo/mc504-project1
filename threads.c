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
    int flag = 0;

    for(int i = 0; flag && i < N; i++){
        if(i != student_id && i != i + 2 % N && states[i] != D){
            flag = 0;
        }
    }

    if(flag)
        return;

    if(states[student_id] == D && states[LEFT] != W && states[RIGHT] != W){
        states[student_id] = W;
        display();
        sem_post(&students[student_id]);
    }
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
    display();
    check_pens(LEFT);
    check_pens(RIGHT);
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
