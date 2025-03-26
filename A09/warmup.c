/*----------------------------------------------
 * Author: Allison Liao
 * Date: 03/28/25
 * Program that spawns processes according to spec.
 ---------------------------------------------*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t ret;
  printf("%d] A0\n", getpid());
  ret = fork();
  if (ret == 0) { // child (B1)
    printf("%d] B1\n", getpid());
  } else { // parent (B0)
    printf("%d] B0\n", getpid());
    ret = fork();
    if (ret == 0) { // child (C1)
      printf("%d] C1\n", getpid());

    } else { // parent (C0)
      printf("%d] C0\n", getpid());
    }
  }
  printf("%d] Bye\n", getpid());
  
  return 0;
}
