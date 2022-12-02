#include <stdio.h>
#include <stdlib.h>

//
// Created by Hammad Shahid on 10/03/2022.
//

#define EXIT_NO_ERRORS 0


#define EXIT_BAD_ARG_COUNT 1
#define EXIT_BAD_FILE_NAME 2
#define EXIT_BAD_MAGIC_NUMBER 3
#define EXIT_BAD_COMMENT_LINE 4
#define EXIT_BAD_DIMENSIONS 5
#define EXIT_BAD_MAX_GRAY_VALUE 6
#define EXIT_IMAGE_MALLOC_FAILED 7
#define EXIT_BAD_DATA 8
#define EXIT_OUTPUT_FAILED 9
#define EXIT_BAD_LAYOUT 10
#define EXIT_MISC_ERROR 100

#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65536
#define MAX_COMMENT_LINE_LENGTH 128


typedef struct pgmStructs pgmStructs;

typedef struct  pgmStructs{
    unsigned char *nextGrayValue;
    long nImageBytes;
    char *commentLine;
    unsigned char *imageData;
    unsigned char magic_number[2];
    unsigned short *magic_Number;
    unsigned int width;
    unsigned int height;
    unsigned int maxGray;
} pgmStructs;

pgmStructs pgmStructs1;

int Checkfor0args(int argc, char **argv){
    if(argc == 1){
        printf("Usage: %s inputImage.pgm outputImage.pgm\n", argv[0]);
        exit(0);
    }
}


int Checkfor3args(int argc, char **argv){
    if (argc != 3) { /* wrong arg count */
        /* print an error message        */
        printf("ERROR: Bad Argument Count\n");
        /* and return an error code      */
        exit(EXIT_BAD_ARG_COUNT);
    }
}

int Checkfor4args(int argc, char **argv){
    if (argc != 4) { /* wrong arg count */
        /* print an error message        */
        printf("ERROR: Bad Argument Count\n");
        /* and return an error code      */
        exit(EXIT_BAD_ARG_COUNT);
    }
}

void Check_Empty_File(const char *filename, pgmStructs *structure){

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
/* free memory                   */
        free(structure->commentLine);
        free(structure->imageData);

/* print an error message        */
        printf("ERROR: Output Failed (%s)\n", filename);
/* return an error code          */
        exit(EXIT_OUTPUT_FAILED);
    }
    else{
        fclose(fp);
    }
}