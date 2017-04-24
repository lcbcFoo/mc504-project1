/* Header for the  threads-related functions */

/* The algorithm used in the threads implementation is based on the code
 * examples given in class by prof. Islene Calciolari Garcia and on the
 * examples presented by the book "Modern Operating Systems", 4th edition,
 * Pearson, 2014, written by A. S. Tanenbaum and H. Bos
 */

#include <pthread.h>
#include <semaphore.h>

/* define number of students and max total writings */
#define N 5
#define MAX 15
#define MAX_TIME 30

#define RIGHT (student_id + 1) % N
#define LEFT (student_id + N - 1) % N

typedef enum {T, D, W} state_t;

/* Current state of each student */
state_t states[N];

/* Semaphore for picking a pen*/
sem_t semaphore;

/* Semaphore to avoid "printing overlap"*/
sem_t sem_graphics;

/* Semaphore for holding pens for each student */
sem_t students[N];

/* Semaphore for incrementing total questions */
sem_t sem_questions;

/* 0 if pen is free, 1 if pen is being used */
int pens[N];
int mode;

/* Counters */
int questions[N];
int total_questions;

/* Specify how long every student must sleep depending on the animation mode */
int sleeping_time[N];
int start_delay[N];
int writing_time[N];


void think(int student_id);

void writing(int student_id);

void release_pens(int student_id);

int check_left(int student_id);

int check_right(int student_id);

void check_pens(int student_id);

void pick_pens(int student_id);

void check_pens_deadlock(int student_id);

void pick_pens_deadlock(int student_id);

void* student_function(void* v);
