#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void main() {

  int i, j;
  FILE *outfile;
  outfile = fopen("input.txt", "w");

  srand(time(NULL));

  for(i=0; i<4; i++) {
    j = rand() % 20;
    fprintf(outfile, "INSERT %d\n", j);
  }

  fprintf(outfile, "ASCEND\n");
  fprintf(outfile, "DESCEND\n");

  for(i=0; i<4; i++) {
    j = rand() % 20;
    fprintf(outfile, "DELETE %d\n", j);
  }
  
  fprintf(outfile, "ASCEND\n");
  fprintf(outfile, "DESCEND\n");

  fclose(outfile);
}
