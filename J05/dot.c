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
  int dot_product;  // This will store the partial result
};

// Thread function
void* thread_dot(void* arg) {
  struct thread_args* data = (struct thread_args*) arg; 
  int sum = 0;
  for (int i = data->start; i < data->end; i++) {
    sum += data->u[i] * data->v[i];
  }
  data->dot_product = sum;  // Store result in struct field
  return NULL;
}

int main(int argc, char *argv[]) {
  srand(time(0));

  int v[SIZE];
  int u[SIZE];
  int dotproduct = 0;

  // Initialize vectors and compute ground truth
  for (int i = 0; i < SIZE; i++) {
    v[i] = rand() % 1000 - 500;
    u[i] = rand() % 1000 - 500;
    dotproduct += u[i] * v[i];
  }

  printf("Ground truth dot product: %d\n", dotproduct);

  // Create threads
  printf("Test with 4 threads\n");
  pthread_t threads[4];
  struct thread_args args[4];

  for (int i = 0; i < 4; i++) {
    args[i].start = i * 250;
    args[i].end = (i == 4 - 1) ? SIZE : (i + 1) * 250;
    args[i].u = u;
    args[i].v = v;
    args[i].dot_product = 0;
    pthread_create(&threads[i], NULL, thread_dot, &args[i]);
  }

  int thread_dotproduct = 0;
  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
    thread_dotproduct += args[i].dot_product;
  }

  printf("Answer with threads: %d\n", thread_dotproduct);

  return 0;
}
