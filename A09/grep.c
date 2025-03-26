/*----------------------------------------------
 * Author: Allison Liao
 * Date: 03/28/25
 * Program mimicking cmd grep.
 ---------------------------------------------*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

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

int main(int argc, char** argv) {
  struct timeval tstart, tend;
  double timer;
  gettimeofday(&tstart, NULL);

  int count = 0;
  int all = 0;
  int a = 0;

  int n = atoi(argv[1]);
  char* keyword = argv[2];

  int* pids = malloc(sizeof(int) * n);

  printf("Searching %d files for keyword: %s\n", argc - 3, keyword);
  pid_t ret;
  int last_searched = 0;
  int rem_files = argc - 3;

  for (int i = 1; i < n + 1; i++) {
    int num_files = rem_files / (n - i + 1);
    ret = fork();
    pids[i - 1] = ret;

    if (ret == 0) {  // child
      printf("Process [%d] searching %d files (%d to %d)\n", getpid(),
             num_files, last_searched + 1, last_searched + num_files);
      // v is file array being searched
      char** v = malloc(32 * num_files);
      for (int j = 0; j < num_files; j++) {
        v[j] = argv[2 + last_searched + 1 + j];
      }

      count += search(keyword, num_files, v);
      exit(count);
    }

    // maintain loop
    last_searched += num_files;
    rem_files -= num_files;
  }

  gettimeofday(&tend, NULL);

  for (int i = 0; i < n; i++) {
    waitpid(pids[i], &a, 0);
    all += WEXITSTATUS(a);
  }

  printf("Total occurences: %d\n", all);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec) / 1.e6;
  printf("Elapsed time is %g\n", timer);
  free(pids);
  return 0;
}
