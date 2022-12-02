#include <stdio.h>
#include <stdlib.h>
#include "pgmEcho.h"
#include "pgmRead.c"
#include "pgmWrite.c"



int main(int argc, char **argv){
    Checkfor0args(argc, argv);

    Checkfor3args(argc, argv);

    //creat struct for file.
    pgmStructs pgmCompStruct4;

    //Read struct
    ReadFile(argv[1], &pgmCompStruct4);

    //if file is P5.
    if (pgmCompStruct4.magic_number[0] == 'P' && pgmCompStruct4.magic_number[1] == '5') {
        //change it to p2.
        pgmCompStruct4.magic_number[1] = '2';
        //Write the data
        WriteFile(argv[2], &pgmCompStruct4);
        //if no errors then its successfully converted.
        printf("CONVERTED");
        return 0;
    }
    else{
        // else there was a bad magic number.
        printf("ERROR: Bad Magic Number (%s)\n", argv[1]);
        return EXIT_BAD_MAGIC_NUMBER;
    }
}
