/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/07/25
 * Displays n*m grid containing Wampus and 
 * recording distance at each cell.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
  int rows, cols;
  printf("Number of rows: ");
  scanf("%d",&rows);
  printf("Number of columns: ");
  scanf("%d",&cols);

  int *grid = malloc(sizeof(int)*rows*cols);

  if (grid == NULL) {
    printf("Cannot allocate grid. Exiting...\n");
    return 1;
  }
  
  srand(time(NULL));
  int wampus[2] = {rand()%(rows), rand()%(cols)};

  grid[wampus[0]*rows+wampus[1]] = -1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int pos = i*rows+j;
      if (grid[pos] != -1) {
        int dist = abs(i-wampus[0]) + abs(j-wampus[1]);
        grid[pos] = dist;
      }
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int pos = i*rows+j;
      if (grid[pos] == -1) {
        printf("%s", "W");
      } else {
        printf("%d", grid[pos]);
      }
      printf(" ");
    }
    printf("\n");
  }

  free(grid);
  return 0;
}
