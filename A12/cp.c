/*----------------------------------------------
 * Author: Allison Liao
 * Date: 04/18/25
 * Implements producer/consumer with circular array and two threads.
 ---------------------------------------------*/

#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N 10
pthread_mutex_t mux = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
int num_items = 0, in = 0, out = 0, buff[N];

int produce_item() { return rand() % 10; }

void consume_item(int item) { printf("Received item: %d\n", item); }

void* producer() {
  while (1) {
    int item = produce_item();
    pthread_mutex_lock(&mux);
    while (num_items >= N) {
      pthread_cond_wait(&full, &mux);
    }
    buff[in] = item;
    in = (in + 1) % N;
    num_items++;
    pthread_cond_signal(&empty);
    pthread_mutex_unlock(&mux);
  }
}

void* consumer() {
  while (1) {
    int item = produce_item();
    pthread_mutex_lock(&mux);
    while (num_items == 0) {
      pthread_cond_wait(&empty, &mux);
    }
    item = buff[out];
    out = (out + 1) % N;
    num_items--;
    pthread_cond_signal(&full);
    pthread_mutex_unlock(&mux);
    consume_item(item);
    sleep(1.0);
  }
}

int main() {
  pthread_t threads[2];
  pthread_create(&threads[0], NULL, producer, NULL);
  pthread_create(&threads[1], NULL, consumer, NULL);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  return 0;
}
