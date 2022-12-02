#include "pgmEcho.h"
#include "pgmRead.c"
#include "pgmWrite.c"
#include "math.h"


int main(int argc, char **argv) {
    //counting the command line arguments
    int count = 0;
    while (argv[++count] != NULL);


//    printf("%d", count);
    if (argc == 1) {
        printf("Usage: %s outputImage.pgm width height (row column inputImage.pgm)+", argv[0]);
        exit(0);
    }


    //if the command line argument is not a divisor of 3, taking away, ./pgmAssemble.
    if ((count - 1) % 3 != 0) { /* wrong arg count */
        /* print an error message        */
        printf("ERROR: Bad Argument Count\n");
        /* and return an error code      */
        return EXIT_BAD_ARG_COUNT;
    } /* wrong arg count */

    char output_file[256];

    //copying the output file
    strcpy(output_file, argv[1]);

    char output_file_width[12];
    char output_file_height[12];

    //copying the output width and height
    strcpy(output_file_width, argv[2]);
    strcpy(output_file_height, argv[3]);

//    printf("%s,%s", output_file_width, output_file_height);

    //creating struct store all the file data.
    typedef struct pgmAssembleStruct {
        char row[12];
        char col[12];
        char input_file[256];
    } pgmAssembleStruct;

    //creating an array for the comamnd line arguments so can store them.
    pgmAssembleStruct arrays[(count - 1) / 3];

    // finding out when to loop till to store the comand line arugments.
    int Loop_till = (argc - 4) / 3;

//    printf("%d", Loop_till);

    //grabbing the highest arguments to make a 2day array.
    int h_width = -10;
    int h_height = -10;

    //looping and grabbing the highest and lowest values.
    for (int y = 0; y < Loop_till; y++) {
        int width = atoi(argv[(y * 3) + 4]);
        if (width > h_width) {
            h_width = width;
        }

        int height = atoi(argv[(y * 3) + 5]);

        if (height > h_height) {
            h_height = height;
        }
    }

    //creating a 2d array.
    pgmStructs array[h_height + 1][h_width + 1];



    //loop through and read all the files.
    for (int x = 0; x < Loop_till; x++) {
//        printf("%d", x);

        strcpy(arrays[x].row, argv[(x * 3) + 4]);
        strcpy(arrays[x].col, argv[(x * 3) + 5]);
        strcpy(arrays[x].input_file, argv[(x * 3) + 6]);
//        printf(" %s, %s, %s\n", arrays[x].row,arrays[x].col,arrays[x].input_file);

        ReadFile(arrays[x].input_file, &array[atoi(arrays[x].row)][atoi(arrays[x].col)]);



    }

    FILE *fp = fopen(output_file, "w");

    if (fp == NULL) {
/* free memory                   */


/* print an error message        */
        printf("ERROR: Output Failed (%s)\n", output_file);
/* return an error code          */
        exit(EXIT_OUTPUT_FAILED);
    }

    size_t nBytesWritten = fprintf(fp, "P2\n%d %d\n%d\n", atoi(output_file_width), atoi(output_file_height),
                                   255);

    int Tile_counter = 0;


    int Tile_File_width = array[0][0].width;
    int Tile_File_height = array[0][0].height;


    int Repeat_Counter = 0;

    int value_col = 0;
    int value_row = 0;

    long nimageBytesForMainfile = atoi(output_file_height) * atoi(output_file_width) * sizeof(unsigned char);
    unsigned char *imageDataMainFile = (unsigned char *) malloc(nimageBytesForMainfile);

    unsigned char* data = malloc(atoi(output_file_width) * atoi(output_file_height) * sizeof (unsigned char));
//    unsigned char data[atoi(output_file_width) * atoi(output_file_height)];

    int count2 = 0;


    for (int row = 0; row < h_height + 1; row++) {


        for (int col = 0; col < h_width + 1; col++) {


            int value_col = 0;
            int values_row = 0;

            int End_row = array[row][col].width;


            for (array[row][col].nextGrayValue = array[row][col].imageData; array[row][col].nextGrayValue <
                                                                            array[row][col].imageData +
                                                                            array[row][col].nImageBytes; array[row][col].nextGrayValue++) {

                int nextCol = (array[row][col].nextGrayValue - array[row][col].imageData + 1) % array[row][col].width;
                unsigned char *nextGrayValue = array[row][col].nextGrayValue;

                count2++;

                data[count2] = *nextGrayValue;
//                printf("%d ", *nextGrayValue);
            }
        }
    }

//    printf("\n");
    int Valid = 0;
    int start_point = 1;


    int count_amount_rows = 0;

    int Count_amount_elements = 0;




    size_t n = sizeof(data)/sizeof(data[0]);
    if((n/Loop_till) == 1){
        for(int x=1; x<=Loop_till; x++){
            if(*array[0][0].magic_Number == MAGIC_NUMBER_ASCII_PGM){
                fprintf(fp, "%d%c", data[x], (' '));
            }
            else if(*array[0][0].magic_Number == MAGIC_NUMBER_RAW_PGM){
                fputc(data[x], fp);
            }

        }
    }
        // while the loop hasn't check all the rows. Keep sorting.
    else{



        while(Valid != atoi(output_file_width)*sqrt(Loop_till)){
//            printf("%d ", Valid);



            // count the number of elements looped through. set to 0 before looping through elements.
            int count_elements = 0;
//        printf("%d", count_loop);


            //loop through elements. Start position is 0 at beginning but changes throuhg to sort.
            for(int x=start_point; x<=count2; x++){
//                printf("%d ", data[x]);

                //write data to the file.
                if(*array[0][0].magic_Number == MAGIC_NUMBER_ASCII_PGM){
                    fprintf(fp, "%d%c", data[x], (' '));
                }
                else if(*array[0][0].magic_Number == MAGIC_NUMBER_RAW_PGM){
                    fputc(data[x], fp);
                }

                count_elements +=1;

//            printf("%d", count_loop);
                count_amount_rows += 1;
//            printf("%d ", count_loop);

//            printf("%d\n", count_amount_rows);

                //if the amount of elements
                if(count_amount_rows == (atoi(output_file_width) * array[0][0].width)){
                    start_point = count_amount_rows+1;
                    count_amount_rows = 0;

                    size_t  n = sizeof (data) / sizeof(data[0]);
//
//                    x+= n;




//                    for(int y=0; y<count2/(h_height+1); y++){
//                        size_t  n = sizeof (data) / sizeof(data[0]);
//                        memmove(data , data + 1, n);
//
//                    }




                    Valid +=1;
                    break;



                }




                //if the number of elements are equal to the full width of the file then start a new row.
                // and change the starting position for the next row.
                if(count_elements == atoi(output_file_width)){
                    start_point += array[0][0].width;
                    Valid += 1;
                    break;
                }
                //if the number of elements equal to the width of the tile then jump then skip the elements below and go to
                //the next row.
                if(count_elements==array[0][0].width){
                    x += (array[0][0].width * array[0][0].height) - array[0][0].width;
                    Valid += 1;



                }



            }



        }
    }


    printf("ASSEMBLED");
    return(EXIT_NO_ERRORS);




}


