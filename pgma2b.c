#include "pgmEcho.h"
#include "pgmRead.c"
#include "pgmWrite.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    Checkfor0args(argc, argv);

    Checkfor3args(argc, argv);

    pgmStructs pgmCompStruct3;


    ReadFile(argv[1], &pgmCompStruct3);


    if (pgmCompStruct3.magic_number[0] == 'P' && pgmCompStruct3.magic_number[1] == '2') {
        pgmCompStruct3.magic_number[1] = '5';

        WriteFile(argv[2], &pgmCompStruct3);

        /*----------------------------------------------------------------------------------------------------------*/

        printf("CONVERTED");
        return 0;
    }

    else{
        printf("ERROR: Bad Magic Number (%s)\n", argv[1]);
        return EXIT_BAD_MAGIC_NUMBER;
    }


}

