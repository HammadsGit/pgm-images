#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pgmEcho.h"
#include "pgmRead.c"
#include "pgmWrite.c"


int main(int argc, char **argv) {

    //check only if ./pgmTile is entered.
    if(argc == 1){
        printf("Usage: %s inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm", argv[0]);
        exit(0);
    }

    //check if the user entered wrong amount of arguments.
    Checkfor4args(argc, argv);


    // struct to store filenames
    typedef struct {
        char name[256];

    } fname_arr;



    // creating a struct for to be able to read through
    pgmStructs pgmCompStructMainFile;
    // Read the file send in.
    ReadFile(argv[1], &pgmCompStructMainFile);
    // initalise the factor inside a variable.
    int factor = atoi(argv[2]);

    //get the factor width and height.



    int factor_width = ceil(pgmCompStructMainFile.width / factor);
    int factor_height = ceil(pgmCompStructMainFile.height / factor);


    // declares the output filename into file-name.
    char filename[256];

    //copies the filename from the argument.
    strcpy(filename, argv[3]);


    //if filename doesn't include <row> & <column> & .pgm its a bad filename.
    if(strstr(filename, "<row>") == NULL || strstr(filename, "<column>") == NULL || strstr(filename, ".pgm") == NULL){
        printf("ERROR: Miscellaneous (Tile bad template.)\n");
        exit(EXIT_MISC_ERROR);
    }



    // removes _row_col
    char *result = strstr(filename, "<row>");
    int index = result - filename;

    // removes the first occurance of <
    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);



    // will remove r
    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);


    // will remove o
    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);



    // will remove w
    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);


    // replaces with +, to remember index of row position.
    int position_of_plus = index;
    filename[index] = '+';



    result = strstr(filename, "<column>");
    index = result - filename;

    // removes the first occurance of < in column

    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);



    // removes  occurance of c

    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);


    // removes  occurance of o

    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);



    // removes  occurance of l

    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);


    // removes  occurance of u

    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);


    // removes  occurance of m

    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);


    // removes  occurance of n

    memmove(&filename[index], &filename[index + 1], strlen(filename) - index);


    //replace last character with -
    int position_of_minus = index;
    filename[index] = '-';



    // Character values for integers that need to be changed to the string filename.
    char X[20];
    char Y[20];

    //used to determine the amount of file names required.
    int factor_squared = factor * factor;

    // creates struct array to store filenames.
    fname_arr arrays[factor_squared];

    // file name storing counter to add filenames to struct
    int fname_storing_counter = 0;




    // changes file names.
    for(int x=0; x<factor; x++){
        sprintf(X, "%d", x);
        filename[position_of_plus] = *X;


        for(int y=0; y<factor; y++){
            sprintf(Y, "%d", y);
            filename[position_of_minus] = *Y;


            // adds .pgm at the end of the file name.
            char pgmfname[256] = "";
            strcpy(pgmfname, filename);




            //stores the filenames in an array
            strcpy(arrays[fname_storing_counter].name, pgmfname);
            fname_storing_counter += 1;

        }


    }

    // accessing names from array
    int original_height = pgmCompStructMainFile.height;
    int original_width = pgmCompStructMainFile.width;



    pgmCompStructMainFile.width = factor_width;
    pgmCompStructMainFile.height = factor_height;





    //opening the first file for writing
    FILE *fp = fopen(arrays[0].name, "w");

    //check if file is null

    Check_Empty_File(arrays[0].name, &pgmCompStructMainFile);


    
    //row and col to count the indexes.
    int row_count = 0;
    int col_count = 0;

    //start row and col to know the beginning of the block.
    int start_row = 0;
    int start_col = 0;

    //Row End and Col to know the end of the block.
    int row_End = factor_width;
    int col_End = factor_height;

    int file_counter = 0;

    long nimageBytesForTileTopLeft = (pgmCompStructMainFile.width * pgmCompStructMainFile.height)  * sizeof (unsigned char);
    unsigned char *imageDataTopLeft = (unsigned char *) malloc(nimageBytesForTileTopLeft);
    unsigned char *nextGrayValueTopLeft = imageDataTopLeft;


    int valid = 0;

    int count = 0;
    int Data_count = 0;


    while(valid != factor_squared){
//        printf("While loop");
        //incrementing filename to grab specific file for the data.
        if(file_counter >= 0){
            fp = fopen(arrays[file_counter].name, "w");
        }

        if(*pgmCompStructMainFile.magic_Number == MAGIC_NUMBER_ASCII_PGM){
            size_t nBytesWritten = fprintf(fp, "P2\n%d %d\n%d\n", pgmCompStructMainFile.width, pgmCompStructMainFile.height,
                                           pgmCompStructMainFile.maxGray);
        }
        else if(*pgmCompStructMainFile.magic_Number == MAGIC_NUMBER_RAW_PGM){
            size_t nBytesWritten = fprintf(fp, "P5\n%d %d\n%d\n", pgmCompStructMainFile.width, pgmCompStructMainFile.height,
                                           pgmCompStructMainFile.maxGray);
        }

        for (pgmCompStructMainFile.nextGrayValue = pgmCompStructMainFile.imageData;pgmCompStructMainFile.nextGrayValue < pgmCompStructMainFile.imageData + pgmCompStructMainFile.nImageBytes; pgmCompStructMainFile.nextGrayValue++) {
            if(row_End > original_height){
                row_End = original_height;
            }
            if(col_End > original_width){
                col_End = original_width;
            }



//            printf("%d, %d, %d, %d\n", rowcount, colcount, Row_End, Col_End);
            if((row_count >=start_row && row_count < row_End) && (col_count >= start_col && col_count < col_End)){


                count += 1;


                unsigned char *nextGrayValueTopLeft = pgmCompStructMainFile.nextGrayValue;
                int nextCol = (nextGrayValueTopLeft - imageDataTopLeft + 1) % pgmCompStructMainFile.width;

                // determine what type of file to write in the data.
                if(*pgmCompStructMainFile.magic_Number == MAGIC_NUMBER_RAW_PGM){
                    fputc(*nextGrayValueTopLeft, fp);
                }
                else if(*pgmCompStructMainFile.magic_Number == MAGIC_NUMBER_ASCII_PGM){

                    fprintf(fp, "%d%c", *nextGrayValueTopLeft, (nextCol ? ' ' : '\n'));
                }

            }


            //if the data has reached the end block of the specific row then move down to the next row tile.
            if(row_count+1 == row_End && col_count + 1 == (original_width)){
                //row moves down
                row_End += factor_width;
                start_row += factor_width;

                //col is set 0, to start from the beginning of the row.
                col_End = factor_height;
                start_col = 0;

                //file is closed since the tile is finished.
                fclose(fp);
                //append one so we can move onto the next file in the next loop.
                file_counter += 1;

                //File data sucessfully read so increase the counter to let the while loop know.
                valid += 1;

                // reset row and col counters for the next block.
                row_count = 0;
                col_count = 0;
                //break since data is read, and ready to read next block.
                count = 0;
                break;
            }

            if(row_count+1 == row_End && col_count + 1 == col_End){

                //increase the col to move to the next tile in the row.
                start_col += factor_height;
                col_End += factor_height;



                //file is closed since the tile is finished.
                fclose(fp);
                //append one so we can move onto the next file in the next loop.
                file_counter += 1;

                //File data sucessfully read so increase the counter to let the while loop know.
                valid += 1;

                // reset row and col counters for the next block.
                row_count = 0;
                col_count = 0;
                //break since data is read, and ready to read next block.
                count = 0;
                break;

            }
            col_count += 1;

            //if col is equal to the width then increment the row.
            if(col_count == original_width){
                row_count += 1;
                col_count = 0;
            }





        }




    }

    printf("TILED");
    return(EXIT_NO_ERRORS);


}
