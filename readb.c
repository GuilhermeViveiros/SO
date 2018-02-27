#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdlib.h>
#include "readb.h"
#include <stdio.h>

typedef struct buffer_t{

    char* x;
    size_t nbyte;
    int filedes; 
    int end;
    int st; 
    int flag;
    
    // -> iniciated 0
    // -> with content 1

}* BUFF; 


BUFF create_buffer( int filedes, size_t nbyte){
    BUFF buffer=(BUFF)malloc ( sizeof(struct buffer_t) );

    if(filedes == -1){
        perror(" the file didn't work well. \n");
        exit(-1);
    }

    buffer->x = malloc( nbyte );
    buffer->filedes = filedes;
    buffer->nbyte   = nbyte;
    buffer->flag    = 0;
    buffer->st  = 0 ; 
    buffer->end = 0 ;
    
    return buffer;
}

int destroy_buffer(BUFF buffer){
    free(buffer->x);
    free(buffer);
    
    return 1;
}

static int buffer_full ( BUFF buffer){
    if( buffer->st >= buffer->end ){
        buffer->flag = 0;
        return 1;
    }
    return 0;

}


ssize_t readln(BUFF buffer, void** buf){

    int n,i=0,j;
    char c, * new;

    buffer_full( buffer ); 

    // flag === 0;
    // tem de ler
    if ( ! buffer->flag ) { 
        n = read (buffer->filedes , buffer->x , buffer->nbyte );
        
        buffer->end = n;
        buffer->st = 0;
        buffer->flag =1;

    }

    for ( i= buffer->st ; i< buffer->end; i++){
            if( buffer->x[i] == '\n')
                break;
        
        }   
    //i++;
    
    n = i - buffer->st;
    new = malloc( n );
    
    for ( j= 0 ; j + buffer->st < i+1  ; j++ )
        new[j] = buffer->x[buffer->st + j]; 

    buffer->st = i+1;
    *buf= (void*)new; 
    return n;
}