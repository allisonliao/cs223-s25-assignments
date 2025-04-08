#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 100000

// your code here

struct thread_args {
  int *u;
  int *v;
  int start;
  int end;
  int dot_product;
};

void* thread_dot(void* arg) {
  struct thread_args* data = (struct thread_args*) arg; 
  int start = data->start;
  int end = data->end;
  int dot = data->dot_product;
  int* u = data->u;
  int* v = data->v;
  
  for (int i = start; i < end; i++) {
    dot += u[i] * v[i];
  }
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int v[SIZE];
  int u[SIZE];
  int dotproduct = 0;
   
  for (int i = 0; i < SIZE; i++) {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    dotproduct += u[i] * v[i];
  }
  printf("Ground truth dot product: %d\n", dotproduct);

  // TODO: Implement your thread solution here
  int thread_dotproduct = 0;
  printf("Test with 4 threads\n");
  pthread_t threads[4];
  struct thread_args** array = malloc(sizeof(struct thread_args*) * 4);
  for(int i = 0; i < 4; i++) {
    struct thread_args* args = array[i];
    //ids[i] = &args;
    args->start = i * 250;
    args->end = (i+1) * 250;
    args->u = u;
    args->v = v;
    args->dot_product = 0;
    pthread_create(&threads[i], NULL, thread_dot, NULL);
  }

  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
    thread_dotproduct += array[i]->dot_product;
  }

  printf("Answer with threads: %d\n", thread_dotproduct);

  free(array);

  return 0;
}
