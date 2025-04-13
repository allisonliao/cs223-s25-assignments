#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "read_ppm.h"
#include "write_ppm.h"

typedef struct {
  int thread_id;
  int num_threads;
  int width;
  int height;
  int threshold;
  int blur_radius;
  struct ppm_pixel* original;
  struct ppm_pixel* bright;
  struct ppm_pixel* blurred;
  struct ppm_pixel* result;
} ThreadData;

unsigned char clamp_color(int val) {
  if (val > 255) return 255;
  if (val < 0) return 0;
  return (unsigned char)val;
}

void* process_slice(void* arg) {
  ThreadData* data = (ThreadData*)arg;
  int start_row = (data->height / data->num_threads) * data->thread_id;
  int end_row = start_row + (data->height / data->num_threads);

  printf("Thread sub-image slice: rows (%d,%d)\n", start_row, end_row);

  int w = data->width;
  int h = data->height;

  // extract bright areas
  for (int row = start_row; row < end_row; ++row) {
    for (int col = 0; col < w; ++col) {
      int idx = row * w + col;
      struct ppm_pixel p = data->original[idx];
      int brightness = (p.red + p.green + p.blue) / 3;

      if (brightness > data->threshold) {
        data->bright[idx] = p;
      } else {
        data->bright[idx].red = data->bright[idx].green =
            data->bright[idx].blue = 0;
      }
    }
  }

  // box blur
  for (int row = start_row; row < end_row; ++row) {
    for (int col = 0; col < w; ++col) {
      int r_sum = 0, g_sum = 0, b_sum = 0;
      int count = 0;

      for (int dy = -data->blur_radius; dy <= data->blur_radius; ++dy) {
        for (int dx = -data->blur_radius; dx <= data->blur_radius; ++dx) {
          int ny = row + dy;
          int nx = col + dx;
          if (ny >= 0 && ny < h && nx >= 0 && nx < w) {
            int nidx = ny * w + nx;
            struct ppm_pixel p = data->bright[nidx];
            r_sum += p.red;
            g_sum += p.green;
            b_sum += p.blue;
            count++;
          }
        }
      }

      int idx = row * w + col;
      data->blurred[idx].red = r_sum / count;
      data->blurred[idx].green = g_sum / count;
      data->blurred[idx].blue = b_sum / count;
    }
  }

  // add blurred to original
  for (int row = start_row; row < end_row; ++row) {
    for (int col = 0; col < w; ++col) {
      int idx = row * w + col;
      struct ppm_pixel o = data->original[idx];
      struct ppm_pixel b = data->blurred[idx];

      data->result[idx].red = clamp_color(o.red + b.red);
      data->result[idx].green = clamp_color(o.green + b.green);
      data->result[idx].blue = clamp_color(o.blue + b.blue);
    }
  }

  return NULL;
}

int main(int argc, char* argv[]) {
  int N = 4;
  int threshold = 200;
  int blursize = 24;
  const char* filename = "earth-small.ppm";

  int opt;
  while ((opt = getopt(argc, argv, ":N:t:b:f:")) != -1) {
    switch (opt) {
      case 'N':
        N = atoi(optarg);
        break;
      case 't':
        threshold = atoi(optarg);
        break;
      case 'b':
        blursize = atoi(optarg);
        break;
      case 'f':
        filename = optarg;
        break;
      case '?':
        printf(
            "usage: %s -N <NumThreads> -t <brightness threshold> -b <box blur "
            "size> -f <ppmfile>\n",
            argv[0]);
        return 1;
    }
  }

  int width, height;
  struct ppm_pixel* original = read_ppm(filename, &width, &height);
  if (!original) {
    fprintf(stderr, "Error: couldn't read input file %s\n", filename);
    return 1;
  }

  struct ppm_pixel* bright = malloc(sizeof(struct ppm_pixel) * width * height);
  struct ppm_pixel* blurred = malloc(sizeof(struct ppm_pixel) * width * height);
  struct ppm_pixel* result = malloc(sizeof(struct ppm_pixel) * width * height);

  memset(bright, 0, sizeof(struct ppm_pixel) * width * height);
  memset(blurred, 0, sizeof(struct ppm_pixel) * width * height);
  memset(result, 0, sizeof(struct ppm_pixel) * width * height);

  pthread_t* threads = malloc(sizeof(pthread_t) * N);
  ThreadData* thread_data = malloc(sizeof(ThreadData) * N);

  int blur_radius = blursize / 2;

  for (int i = 0; i < N; ++i) {
    thread_data[i] = (ThreadData){.thread_id = i,
                                  .num_threads = N,
                                  .width = width,
                                  .height = height,
                                  .threshold = threshold,
                                  .blur_radius = blur_radius,
                                  .original = original,
                                  .bright = bright,
                                  .blurred = blurred,
                                  .result = result};
    pthread_create(&threads[i], NULL, process_slice, &thread_data[i]);
  }

  for (int i = 0; i < N; ++i) {
    pthread_join(threads[i], NULL);
  }

  write_ppm("glow.ppm", result, width, height);

  free(original);
  free(bright);
  free(blurred);
  free(result);
  free(threads);
  free(thread_data);

  return 0;
}
