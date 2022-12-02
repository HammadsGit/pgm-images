//
// Created by Hammad Shahid on 03/03/2022.
//


#include <stdio.h>
#include <stdlib.h>
#include "pgmEcho.h"
#include "pgmRead.c"



int main(int argc, char **argv) {
    // checking for 0 arguments.
    if(argc == 1){
        printf("Usage: %s inputImage.pgm inputImage.pgm\n", argv[0]);
        exit(0);
    }

    Checkfor3args(argc, argv);


    //creating 2 structure for each file
    pgmStructs pgmCompStruct1;
    pgmStructs pgmCompStruct2;

    // Read both Files
    ReadFile(argv[1], &pgmCompStruct1);
    ReadFile(argv[2], &pgmCompStruct2);

    //Count to check if files will be identical.
    int identical_count = 0;
    int all_count = 0;




    //count to check if width is identical
    if (pgmCompStruct1.width == pgmCompStruct2.width) {
        identical_count += 1;
        all_count += 1;
    } else {
        all_count += 1;
    }
    //count to check if height is identical
    if (pgmCompStruct1.height == pgmCompStruct2.height) {
        identical_count += 1;
        all_count += 1;
    } else {
        all_count += 1;
    }
    //count to check if maxGray is identical
    if (pgmCompStruct1.maxGray == pgmCompStruct2.maxGray) {
        identical_count += 1;
        all_count += 1;
    } else {
        all_count += 1;
    }

//count to check if grayvalues are identical.
    pgmCompStruct2.nextGrayValue = pgmCompStruct2.imageData;
    for (pgmCompStruct1.nextGrayValue = pgmCompStruct1.imageData; pgmCompStruct1.nextGrayValue <
                                                                  pgmCompStruct1.imageData +
                                                                  pgmCompStruct1.nImageBytes; pgmCompStruct1.nextGrayValue++) {
        if ((*pgmCompStruct1.nextGrayValue/pgmCompStruct1.maxGray) == (*pgmCompStruct2.nextGrayValue/pgmCompStruct2.maxGray)) {
            identical_count += 1;
            all_count += 1;
        } else {
            all_count += 1;
        }


        pgmCompStruct2.nextGrayValue++;
    }
    




    // if All_count (all compares meaning the ones that didn't even match) is equal to identical_count
    // that means file is identical since file there were no matches that were not identical.
    if (all_count == identical_count) {
        printf("IDENTICAL");
        return 0;
    } else //else file is Different.
    {
        printf("DIFFERENT");
        return 0;
    }

}
