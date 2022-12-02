#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//function to skip comment lines.
int commentskip(FILE *fp, const char filename[256], pgmStructs *structure){
    //gets next char
    int ch = fgetc(fp);
    // max amount of comment length to get.
    char line[130];

    // if next comment get the whole comment line.
    if(ch == '#') {

        // check if comment is greater than 128 characters including the hash.
        fgets(line, sizeof(line), fp);
        if(strlen(line)  > MAX_COMMENT_LINE_LENGTH){
            free(structure->commentLine);
            free(structure->imageData);
            free(fp);

            printf("ERROR: Bad Comment Line (%s)\n", filename);
            exit(EXIT_BAD_COMMENT_LINE);

        }
        else{
            commentskip(fp, filename, structure);
        }
    }
        // if not put the comment back.
    else{
        ungetc(ch, fp);
    }
}




//Function to Read the pgm file.
int ReadFile(const char *filename, pgmStructs *structure){

    //stores the magic number
    structure->magic_number[0] = '0';
    structure->magic_number[1] = '0';

    //pointer for magic number array in struct
    structure->magic_Number = (unsigned short *) structure->magic_number;

    //stores the comment
    structure->commentLine = 0;


    // Storing the basics in the struct.
    structure->width = 0,structure->height = 0;

    structure->maxGray = 255;


    //pointer to raw image data
    structure->imageData = NULL;

    //open file with pointer
    FILE *inputFile = fopen(filename, "r");

    //if file is empty return bad file error.
    if (inputFile == NULL)
    {
        printf("ERROR: Bad File Name (%s)\n",filename);
        exit(EXIT_BAD_FILE_NAME);
    }

    //getting the magic numbers
    structure->magic_number[0] = fgetc(inputFile);
    structure->magic_number[1] = fgetc(inputFile);

    // checks if the file isn't binary or ASCII format
    if (*structure->magic_Number != MAGIC_NUMBER_ASCII_PGM && *structure->magic_Number != MAGIC_NUMBER_RAW_PGM)
    { /* failed magic number check   */
        /* be tidy: close the file       */
        free(structure->commentLine);
        free(structure->imageData);


        fclose(inputFile);

        /* print an error message */


        /* and return                    */

        printf("ERROR: Bad Magic Number (%s)\n", filename);
        exit(EXIT_BAD_MAGIC_NUMBER);

    }


    commentskip(inputFile, filename, structure);
    //scan for width

    int scanCount = fscanf(inputFile, " ");
    commentskip(inputFile, filename, structure);


    if(fscanf(inputFile, " %u", &(structure->width)) == 1)
    {
        scanCount += 1;
    }
    // skip comments between values
    commentskip(inputFile, filename, structure);
    //scan for height
    if(fscanf(inputFile, " %u", &(structure->height)) == 1)
    {
        scanCount += 1;
    }
    // skip comments between values
    commentskip(inputFile, filename, structure);
    //scan for maxGray.
    if(fscanf(inputFile, " %u", &(structure->maxGray)) == 1)
    {
        scanCount += 1;
    }

    //checks on the size.

    //Must exactly read 3 values

    if (            (scanCount != 3				)	||
                    (structure->width 	< MIN_IMAGE_DIMENSION	) 	||
                    (structure->width  	>= MAX_IMAGE_DIMENSION	) 	||
                    (structure->height  < MIN_IMAGE_DIMENSION	) 	||
                    (structure->height  >= MAX_IMAGE_DIMENSION	) )
    {
        free(structure->commentLine);
        free(structure->imageData);

        /* be tidy: close file pointer   */
        fclose(inputFile);

        /* print an error message */




        printf("ERROR: Bad Dimensions (%s)\n", filename);
        exit(EXIT_BAD_DIMENSIONS);
    }

    if 	((structure->maxGray 	!= 255		))
    { /* failed size sanity check    */
        /* free up the memory            */
        free(structure->commentLine);
        free(structure->imageData);

        /* be tidy: close file pointer   */
        fclose(inputFile);

        /* print an error message */

        printf("ERROR: Bad Max Gray Value (%s)\n", filename);


        /* and return                    */
        exit(EXIT_BAD_MAX_GRAY_VALUE);
    }

    // storing Imagebytes and ImageData in the structure.
    structure->nImageBytes = structure->width * structure->height * sizeof(unsigned char);
    structure->imageData = (unsigned char *) malloc(structure->nImageBytes);





    /* sanity check for memory alocation    */
    if (structure->imageData == NULL)
    { /* malloc failed */
        /* free up memory                */
        free(structure->commentLine);
        free(structure->imageData);

        /* close file pointer            */
        fclose(inputFile);

        /* print an error message */

        /* return error code             */
        printf("ERROR: Image Malloc Failed\n");
        exit(EXIT_IMAGE_MALLOC_FAILED);
    }




    // Read file if its ASCII

    //check too little and large data
    unsigned int Data_Value_Check = structure->width *  structure->width;
    int Data_Count = 0;

    if(*structure->magic_Number == MAGIC_NUMBER_ASCII_PGM){



        for (structure->nextGrayValue = structure->imageData; structure->nextGrayValue < structure->imageData + structure->nImageBytes; structure->nextGrayValue++)
        { /* per gray value */

            /* read next value               */
            int grayValue = -1;
            int scanCount = fscanf(inputFile, " %u", &grayValue);


            /* sanity check	                 */

            if ((scanCount != 1) || (grayValue < 0) || (grayValue > structure->maxGray))
            { /* fscanf failed */
                /* free memory           */
                free(structure->commentLine);
                free(structure->imageData);

                /* close file            */
                fclose(inputFile);

                /* print error message   */

                /* and return            */
                printf("ERROR: Bad Data (%s)\n", filename);
                exit(EXIT_BAD_DATA);
            } /* fscanf failed */

            /* set the pixel value           */
            *structure->nextGrayValue = (unsigned char) grayValue;


        }
        // return bad data if there is more data than needed, in an ascii file.
        int grayValue = -1;
        int scanCount2 = fscanf(inputFile, " %u", &grayValue);
        if(scanCount2 == 1){
            free(structure->commentLine);
            free(structure->imageData);
            fclose(inputFile);
            printf("ERROR: Bad Data (%s)\n", filename);
            exit(EXIT_BAD_DATA);
        }



        /* per gray value */

        /* we're done with the file, so close it */
        fclose(inputFile);
    }
    // Read file if it's in binary.
    if(*structure->magic_Number  == MAGIC_NUMBER_RAW_PGM ){
        // for binary files from stopping creating new lines
        char nextChar = fgetc(inputFile);
        if(nextChar != '\n'){
            ungetc(nextChar, inputFile);
        }

        for (structure->nextGrayValue = structure->imageData; structure->nextGrayValue < structure->imageData + structure->nImageBytes; structure->nextGrayValue++)
        { /* per gray value */



            /* read next value               */
            int grayValue = fgetc(inputFile);
            /* sanity check	                 */

            if ( (grayValue < 0) || (grayValue > structure->maxGray))
            { /* fscanf failed */
                /* free memory           */
                free(structure->commentLine);
                free(structure->imageData);

                /* close file            */
                fclose(inputFile);

                /* print error message   */
                printf("ERROR: Bad Data (%s)\n", filename);
                exit(EXIT_BAD_DATA);
            } /* fscanf failed */

            /* set the pixel value           */
            *structure->nextGrayValue = (unsigned char) grayValue;
            Data_Count += 1;

            if(Data_Count == Data_Value_Check){
                if(fgetc(inputFile) != EOF){
                    free(structure->commentLine);
                    free(structure->imageData);
                    fclose(inputFile);
                    printf("ERROR: Bad Data (%s)\n", filename);
                    exit(EXIT_BAD_DATA);
                }
            }



        }
//         Data_Value_Check = structure->width *  structure->width;

//        printf("%d", Data_Count);

        if(Data_Count != (structure->width * structure->height)){

            free(structure->commentLine);
            free(structure->imageData);
            fclose(inputFile);

            printf("ERROR: Bad Data (%s)\n", filename);
            exit(EXIT_BAD_DATA);
        }

        fread(structure->imageData, 1, structure->nImageBytes, inputFile);
    }


    return EXIT_NO_ERRORS;

}
