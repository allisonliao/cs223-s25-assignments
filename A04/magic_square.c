/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/14/25
 * Checks whether a nxm square is a 'magic square'
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

int fail() {
  printf("M is NOT a magic square!\n");
  return 0;
}

int main() {
  int n,m;
  scanf("%d %d", &n, &m);

  int *array = malloc(sizeof(int) * n * m);

  int magic_constant = -1;

  for (int i = 0; i < n; i++) {
    int rowsum = 0;
    for (int j = 0; j < m; j++) {
      scanf("%d", &array[i * n + j]);
      rowsum += array[i*n+j];
    }
    if (magic_constant == -1) {magic_constant = rowsum;}
    else if (rowsum != magic_constant) {return fail();}
  }

  for (int j = 0; j < m; j++) {
    int rowsum = 0;
    for (int i = 0; i < n; i++) {
      rowsum += array[i*n+j];
    }
    if (rowsum != magic_constant) {return fail();}
  }

  printf("M is a magic square (magic constant = %d)\n", magic_constant);

  return 0;
}
