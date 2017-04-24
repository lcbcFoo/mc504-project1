/* Implementation of the thread-related functions */
#include "threads.h"
#include "graphics.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int testing_time = 0;

void think(int student_id){
    sleep(sleeping_time[student_id]);
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

    if(mode < 2){
        check_pens(LEFT);
        check_pens(RIGHT);
    }
    sem_post(&semaphore);
}

int check_left(int student_id) {
    if(mode != 1){
        if(pens[student_id] == -1){
            pens[student_id] = student_id;
            display();
            sleep(2);
            return 1;
        }
        else if(pens[student_id] == student_id)
            // sleep(1);
            // display();
            return 1;
        return 0;
    }
    else{ // starvation mode
        if((pens[student_id] == -1) && (pens[RIGHT] == -1)){
            pens[student_id] = student_id;
            pens[RIGHT] = student_id;
            sleep(1);
            display();
            return 1;
        }
    }
    return 0;
}

int check_right(int student_id){
    if(mode != 1){
        if(pens[RIGHT] == -1){
            pens[RIGHT] = student_id;
            display();
            sleep(1);
            return 1;
        }
        else
            return 0;
    }
    return 1;
}

// void check_pens(int student_id){
//     if(states[student_id] == D &&
//       check_left(student_id) &&
//       check_right(student_id)){
//         states[student_id] = W;
//         display();
//         sem_post(&students[student_id]);
//     }
//       display();
//       sem_post(&sem_pen);
// }

//////Tentativa
void check_pens(int student_id){
    if(states[student_id] == D){
      check_left(student_id);
      check_right(student_id);
      if(pens[student_id] == student_id && pens[RIGHT] == student_id){
        states[student_id] = W;
        sem_post(&students[student_id]);
      }
    }

      display();
      sem_post(&sem_pen);
}


void pick_pens(int student_id){
    sem_wait(&semaphore);
    states[student_id] = D;
    display();
    check_pens(student_id);
    sem_post(&semaphore);
    sem_wait(&students[student_id]);
}


void check_pens_deadlock(int student_id){
    if(states[student_id] == D &&
      check_left(student_id) &&
      check_right(student_id)){
        states[student_id] = W;
        display();
        sem_post(&students[student_id]);
    }
    display();
    if(++testing_time >= 4){
      sleep(3);
      final_layout();
    }
    sem_post(&sem_pen);
}

void pick_pens_deadlock(int student_id){
      states[student_id] = D;
      display();
      check_pens_deadlock(student_id);
      sem_wait(&students[student_id]);
}


void* student_function(void* v){
    int student_id = *(int *) v;


    if(mode < 2){
      sleep(start_delay[student_id]);

      while(1){
        pick_pens(student_id);
        writing(student_id);
        release_pens(student_id);
        think(student_id);
      }
    }

    else{
      sleep(start_delay[student_id]);

        while(1){
            pick_pens_deadlock(student_id);
            writing(student_id);
            release_pens(student_id);
            think(student_id);
        }
    }

}
