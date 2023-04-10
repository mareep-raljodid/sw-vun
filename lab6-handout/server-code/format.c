#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>

#ifndef BUF_SIZE
#define BUF_SIZE 100
#endif

unsigned int  target = 0x11223344;
char *secret = "A secret message\n";
void dummy_function(char *str);

void myprintf(char *msg)
{
    unsigned int *framep;
    // Save the ebp value into framep
    asm("movl %%ebp, %0" : "=r"(framep));
    printf("Frame Pointer (inside myprintf):      0x%.8x\n", (unsigned int) framep);
    printf("The target variable's value (before): 0x%.8x\n",   target);

    // This line has a format-string vulnerability
    printf(msg);

    printf("The target variable's value (after):  0x%.8x\n",   target);
}


int main(int argc, char **argv)
{
    char buf[1500];
    
    printf("The input buffer's address:    0x%.8x\n",   (unsigned int)  buf);
    printf("The secret message's address:  0x%.8x\n",   (unsigned int)  secret);
    printf("The target variable's address: 0x%.8x\n",   (unsigned int)  &target);

    printf("Waiting for user input ......\n"); 
    int length = fread(buf, sizeof(char), 1500, stdin);
    printf("Received %d bytes.\n", length);

    dummy_function(buf);
    printf("(^_^)(^_^)  Returned properly (^_^)(^_^)\n");

    return 1;
}

// This function is used to insert a stack frame between main and myprintf.
// The size of the frame can be adjusted at the compilation time. 
// The function itself does not do anything.
void dummy_function(char *str)
{
    char dummy_buffer[BUF_SIZE];
    memset(dummy_buffer, 0, BUF_SIZE);

    myprintf(str);
}

