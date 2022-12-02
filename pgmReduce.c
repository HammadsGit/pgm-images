#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pgmEcho.h"
#include "pgmRead.c"
#include "pgmWrite.c"


int main(int argc, char **argv){
    if(argc == 1){
        printf("Usage: %s inputImage.pgm reduction_factor outputImage.pgm\n", argv[0]);
        exit(0);
    }

    //checks if there aren't 4 args and gives an error.
    Checkfor4args( argc,  argv);


    // structure to read File.
    pgmStructs pgmCompStructMainFile;

    // Read File
    ReadFile(argv[1], &pgmCompStructMainFile);



    // variable for the factor.

    if(!isdigit(*argv[2])){
        printf("ERROR: Miscellaneous (factor is non integer.)");
        exit(EXIT_MISC_ERROR);
    }


    //assigning factor to the factor variable.
    int factor = atoi(argv[2]);
    float decimal_factor =  atoi(argv[2]);


    // will use these variables to loop through the row and col since, will be looping through 1d array.
    if(decimal_factor < 0 || decimal_factor-((int)decimal_factor)  != 0){
        printf("ERROR: Miscellaneous (pgmReduce, factor must be a positive number and whole number.)\n");
        exit(EXIT_MISC_ERROR);
    }

    if (factor > pgmCompStructMainFile.width && factor > pgmCompStructMainFile.height){
        printf("ERROR: Miscellaneous (pgmReduce, factor is greater than width and height.)\n");
        exit(EXIT_MISC_ERROR);
    }


    int rowcount = 0;
    int colcount = 0;

    // open file for writing (Since I am writing reduced data can't use normal Write function.)


    // original height and width before dividing.
    int original_height = pgmCompStructMainFile.height;
    int original_width = pgmCompStructMainFile.width;

    //width and height, after factor.
    pgmCompStructMainFile.width = (pgmCompStructMainFile.width) /(atoi(argv[2]));
    pgmCompStructMainFile.height = (pgmCompStructMainFile.width-1) / (atoi(argv[2]);

    //creates a struct for the reduced file.
    pgmStructs pgmCompStructReduced;
    pgmCompStructReduced.magic_Number = pgmCompStructMainFile.magic_Number;
    pgmCompStructReduced.width = pgmCompStructMainFile.width;
    pgmCompStructReduced.height = pgmCompStructMainFile.height;
    pgmCompStructReduced.nImageBytes = pgmCompStructReduced.width  * pgmCompStructReduced.height  * sizeof(unsigned char);
    pgmCompStructReduced.imageData =  (unsigned char *) malloc(pgmCompStructReduced.nImageBytes);
    pgmCompStructReduced.nextGrayValue = pgmCompStructReduced.imageData;
    pgmCompStructReduced.maxGray = pgmCompStructMainFile.maxGray;


    for (pgmCompStructMainFile.nextGrayValue = pgmCompStructMainFile.imageData; pgmCompStructMainFile.nextGrayValue < pgmCompStructMainFile.imageData +pgmCompStructMainFile.nImageBytes; pgmCompStructMainFile.nextGrayValue++) {
            // if the row and col modulus factor is equal to 0 then write the next gray value to the file to reduce it.
            if(rowcount % factor == 0 && colcount % factor == 0){
                //storing out the next gray value.
                *pgmCompStructReduced.nextGrayValue = *pgmCompStructMainFile.nextGrayValue;
                pgmCompStructReduced.nextGrayValue++;

            }
            //incrementing the col
            colcount += 1;

            //if col is equal to the width then increment the row.
            if(colcount == original_width){
                rowcount += 1;
                colcount = 0;
            }

        }

    //writes out the file.
    WriteFile(argv[3], &pgmCompStructReduced);

    //prints out the successful return.
    free(pgmCompStructMainFile.imageData);
    free(pgmCompStructReduced.imageData);
    printf("REDUCED");
    exit(EXIT_NO_ERRORS);


}





