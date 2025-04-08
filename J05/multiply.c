#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define SIZE 100

// your code here
struct thread_args {
  int *m;
  int *u;
  int start;
  int end;
  int* product;
};


void* thread_multiply(void* arg) {
  struct thread_args* data = (struct thread_args*) arg; 
  for (int i = data->start; i < data->end; i++) {
    for (int j = 0; j < 100; j++) {
      data->product[i] += data->u[j] * data->m[i * SIZE + j]; // ???
    }
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int M[SIZE*SIZE];
  int u[SIZE];
  int result[SIZE];
  int result_threads[SIZE];
   
  for (int i = 0; i < SIZE; i++) {
    u[i] = rand() % 10 - 5;
    result[i] = 0;
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int value = rand() % 10 - 5;
      M[i*SIZE + j] = value;
      result[i] += value * u[j];
    }
  }

  // TODO: Implement your thread solution here
  printf("Test with 4 threads\n");

  for (int i = 0; i < SIZE; i++) {
    result_threads[i] = 0;
  }

  pthread_t threads[4];
  struct thread_args args[4];

  for (int i = 0; i < 4; i++) {
    args[i].start = i * (SIZE/4);
    args[i].end = (i == 4 - 1) ? SIZE : (i + 1) * (SIZE/4);
    args[i].m = M;
    args[i].u = u;
    args[i].product = result_threads;
    
    pthread_create(&threads[i], NULL, thread_multiply, &args[i]);
  }

  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
    
    for (int j = i * (SIZE/4); j < (i+1)*(SIZE/4); j++) {
      result_threads[j] = args[i].product[j];
    }
  }



  int error = 0;
  for (int i = 0; i < SIZE; i++) {
    error += abs(result[i] - result_threads[i]);
  }
  printf("Error between ground truth and multithreaded version: %d\n", error);

  return 0;
}
