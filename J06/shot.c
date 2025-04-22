#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sigint_handler(int sig) {
  printf("Help! I've been shot!\n");
  exit(0);
}

int main() {
  while (1) {
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
      perror("signal");
      return 1;
    }
    sleep(1);
  }
  
  
  return 0;
}
