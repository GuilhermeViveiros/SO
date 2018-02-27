#include "readb.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>


int main(int argc, char *argv[] ){

    int f;
    int n, i,v,j, len;
    char** lfile;
    BUFF x;
    
    char buf[40000]; 
    
    char* crazy;

    //f = open("fat.dat" ,O_RDONLY ); 
    
    if( argc < 2){
        perror(" Sua Exelencia esqueceu-se dos argumentos!\n");
        exit(-1);
    }

    len = argc - 1 ;
    //lfile = argv[1]; 

    for(j=0; j< len; j++){
        
        f = open( argv[j+1] ,O_RDONLY );
        x = create_buffer( f, 1024 ); // signals.

        i=1;
        printf("Starting to read: '%s' |\n\n",argv[j+1]);
        while( (n = readln(x, (void**)&crazy ) ) > 1  ){
        
            crazy[n-1]='\0';// substituir o \n 
            v = sprintf(buf,"    %s ->  %d\n",crazy, i++);
            write(1, buf ,v );
            free(crazy);
        }
        destroy_buffer(x); // signals.
        putchar('\n');
    }

    return 0; 
    
}