#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include "write_ppm.h"

struct thread_data {
  int starti;
  int endi;
  int width;
  int height;
  struct ppm_pixel color;
  struct ppm_pixel* image;
};

void *start(void* userdata) {
  struct thread_data* data = (struct thread_data*) userdata;
  for (int i = data->starti; i < data->endi; i++) {
    for (int j = 0; j < data->width; j++) {
      data->image[i*data->width + j].blue = data->color.blue;
      data->image[i*data->width + j].red = data->color.red;
      data->image[i*data->width + j].green = data->color.green;
    }
    
  }
  return 0;
}

int main(int argc, char** argv) {

  if (argc != 2)
  {
    printf("usage: %s <num>\n", argv[0]);
    exit(0);
  }
  int N = strtol(argv[1], NULL, 10);

  int size = 1024;
  struct ppm_pixel* image = malloc(sizeof(struct ppm_pixel) * size * size);
  struct ppm_pixel* colors = malloc(sizeof(struct ppm_pixel) * N);
  pthread_t* threads = malloc(sizeof(pthread_t) * N);
  struct thread_data* data = malloc(sizeof(struct thread_data) * N);

  unsigned int seed = time(0);
  int stripe = size/N;

  for (int i = 0; i < N; i++) {
    data[i].color.blue = rand_r(&seed) % (255) + 1;
    data[i].color.red = rand_r(&seed) % (255) + 1;
    data[i].color.green = rand_r(&seed) % (255) + 1;
    data[i].width = size;
    data[i].height = size;
    data[i].starti = i * stripe;
    data[i].endi = (i+1) * stripe;
    data[i].image = image;
    pthread_create(&threads[i], NULL, start, &data[i]);
  }


  for (int i = 0; i < N; i++) {
    pthread_join(threads[i], NULL);
  }

  write_ppm("stripes.ppm", image, size, size);
  free(image);
  free(colors);
  free(threads);
  free(data);
}
