#ifndef readb_h
#define readb_h

#include <stdlib.h>
#include <unistd.h>

typedef struct buffer_t * BUFF; 


ssize_t readln(BUFF buffer, void** buf);

BUFF create_buffer(int filedes, size_t nbyte);
int destroy_buffer(BUFF buffer);

/*

*/

#endif