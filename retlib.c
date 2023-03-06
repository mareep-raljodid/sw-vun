#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 12
#endif

int bof(char *str)
{
    char buffer[BUF_SIZE];

    /* print out information for experimental purpose */
    printf("Address of buffer[] inside bof():  0x%.8x\n", (unsigned)buffer);
    unsigned int *framep;
    asm("movl %%ebp, %0" : "=r" (framep)); // Copy ebp into framep
    printf("Frame Pointer value inside bof():  0x%.8x\n", (unsigned)framep);
    
    strcpy(buffer, str);   
    return 1;
}

int main(int argc, char **argv)
{
   char input[1000];
   FILE *badfile;
   badfile = fopen("badfile", "r");
   fread(input, sizeof(char), 1000, badfile);

   /* print out information for experimental purpose */
   printf("Address of input[] inside main():  0x%x\n", (unsigned int) input);

   bof(input); 
   printf("(^_^)(^_^) Returned Properly (^_^)(^_^)\n");
   return 1;
}
