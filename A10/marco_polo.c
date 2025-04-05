#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

pid_t child_pid = -1;
pid_t parent_pid = -1;

void parent_handler(int sig) {
  if (sig == SIGALRM) {
    printf("Polo [%d]\n", getpid());
    fflush(stdout);
  }
}

void child_handler(int sig) {
  if (sig == SIGALRM) {
    printf("Marco [%d]\n", getpid());
    fflush(stdout);
    kill(parent_pid, SIGALRM);
  }
}

int main() {
  parent_pid = getpid();
  child_pid = fork();

  if (child_pid < 0) {
    perror("fork failed");
    exit(1);
  }

  if (child_pid == 0) {
    // child
    signal(SIGALRM, child_handler);
    signal(SIGTERM, SIG_DFL);  // child gets terminated by SIGTERM
    while (1) {
      pause();  // wait for signals
    }
  } else {
    // parent
    printf("Parent is %d\n", parent_pid);
    signal(SIGALRM, parent_handler);

    char command;
    while (1) {
      command = getchar();

      if (command == 'm') {
        kill(child_pid, SIGALRM);
      } else if (command == 'q') {
        kill(child_pid, SIGTERM);  // terminate child
        wait(NULL);                // wait for child to exit
        break;
      }
    }
  }

  return 0;
}
