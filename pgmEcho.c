
/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Hammad Shahid               */
/***********************************/

#include <stdlib.h>
#include <stdio.h>
#include "pgmEcho.h"
#include "pgmRead.c"
#include "pgmWrite.c"


int main(int argc, char **argv){
    //if arg values are not 3 then give error.
    Checkfor0args(argc, argv);
    Checkfor3args(argc, argv);

    int ReadFileErrorValue = ReadFile(argv[1], &pgmStructs1);


    //passing in the first pgm file to read data.
    if(ReadFileErrorValue == EXIT_NO_ERRORS){
        int WriteFileErrorValue = WriteFile(argv[2], &pgmStructs1);

        if (WriteFileErrorValue != EXIT_NO_ERRORS){
            return WriteFileErrorValue;
        }
        else{
            free(pgmStructs1.imageData);
            printf("ECHOED");
            return 0;
        }
    }
    else{
        free(pgmStructs1.imageData);
        exit(ReadFileErrorValue);
    };



}
