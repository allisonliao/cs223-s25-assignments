/*----------------------------------------------
 * Author: Allison Liao
 * Date: 02/21/25
 * Method that reads from PPM file and writes
 ---------------------------------------------*/
 #include "write_ppm.h"
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 // implement *one* (but do not remove the other one)!
 
 void write_ppm(const char* filename, struct ppm_pixel* pixels, int w, int h) {
   FILE *output;
   output = fopen(filename, "wb");
   if (output == NULL) {
     printf("Error opening file. Exiting...");
     exit(1);
   }
 
   // write header
   fprintf(output, "P6\n");
   fprintf(output, "# Written by write_ppm.c\n");
   fprintf(output, "%d %d\n", w, h);
   fprintf(output, "255\n");
 
   // write pixels
   fwrite(pixels, sizeof(struct ppm_pixel), w * h, output);
   fclose(output);
 }
 
 void write_ppm_2d(const char* filename, struct ppm_pixel** pixels, int w, int h) {
 
 }
 