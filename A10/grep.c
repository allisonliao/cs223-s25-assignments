/*----------------------------------------------
 * Author: Allison Liao
 * Date: 04/05/25
 * Program mimicking cmd grep with threads.
 ---------------------------------------------*/
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

struct search_params {
  pthread_t thread_id;
  char** files;
  int num_files;
  char* keyword;
  int last_searched;
  int count;
};

int search(char* key, int c, char** v) {  // returns total found
  // search files v[0] to v[c-1] for keyword 'key'
  int all = 0;

  for (int i = 0; i < c; i++) {
    char* filename = v[i];
    FILE* file;
    file = fopen(filename, "r");
    char line[100];
    strcpy(line, "temp");
    int count = 0;
    while (fgets(line, 100, file)) {
      if (strstr(line, key)) {
        printf(ANSI_COLOR_GREEN "%d)" ANSI_COLOR_BLUE "%s:" ANSI_COLOR_RED
                                "%s" ANSI_COLOR_RESET " %s",
               getpid(), filename, key, line);
        count++;
      }
    }

    if (count)
      printf("Process [%d] found %d lines containing keyword: %s\n", getpid(),
             count, key);
    all += count;
  }
  return all;
}

void* thread(void* p) {
  struct search_params* params = p;
  char** argv = params->files;
  int num_files = params->num_files;
  char* keyword = params->keyword;
  int last_searched = params->last_searched;
  printf("Process [%d] searching %d files (%d to %d)\n", getpid(), num_files,
         last_searched + 1, last_searched + num_files);
  // v is file array being searched
  char** v = malloc(32 * num_files);
  for (int j = 0; j < num_files; j++) {
    v[j] = argv[2 + last_searched + 1 + j];
  }

  params->count = search(keyword, num_files, v);
  return NULL;
}

int main(int argc, char** argv) {
  struct timeval tstart, tend;
  double timer;
  gettimeofday(&tstart, NULL);

  int count = 0;
  int all = 0;
  int a = 0;

  int n = atoi(argv[1]);
  char* keyword = argv[2];

  struct search_params** t_params = malloc(sizeof(struct search_params*) * n);

  printf("Searching %d files for keyword: %s\n", argc - 3, keyword);
  pthread_t thread_id;

  int last_searched = 0;
  int rem_files = argc - 3;

  for (int i = 0; i < n; i++) {
    int num_files = rem_files / (n - i);
    // ret = fork();

    // pids[i - 1] = ret;

    struct search_params* p = malloc(sizeof(struct search_params));
    p->files = argv;
    p->keyword = keyword;
    p->last_searched = last_searched;
    p->num_files = num_files;
    p->count = 0;

    pthread_create(&p->thread_id, NULL, thread, p);
    t_params[i] = p;

    // maintain loop
    last_searched += num_files;
    rem_files -= num_files;
  }

  for (int i = 0; i < n; i++) {
    pthread_join(t_params[i]->thread_id, NULL);
    count += t_params[i]->count;
    free(t_params[i]);
    t_params[i] = NULL;
  }

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec) / 1.e6;

  printf("Total occurences: %d\n", count);
  printf("Elapsed time is %g\n", timer);

  free(t_params);
  t_params = NULL;

  return 0;
}
