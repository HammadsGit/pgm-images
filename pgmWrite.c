#include <stdio.h>
#include <stdlib.h>

int WriteFile(const char *filename, pgmStructs *structure) {
    //open file for writing output.
    FILE *outputFile = fopen(filename, "w");

    // If file is null give error.
    if (outputFile == NULL) {
        /* free memory                   */
//        free(structure->commentLine);
        free(structure->imageData);

        /* print an error message        */
        printf("ERROR: Output Failed (%s)\n", filename);
        /* return an error code          */
        exit(EXIT_OUTPUT_FAILED);
    } /* NULL output file */

    /* write magic number, size & gray value */
    size_t nBytesWritten;




    // use this part of code if file is in ASCII
    if(*structure->magic_Number == MAGIC_NUMBER_ASCII_PGM){
        size_t nBytesWritten = fprintf(outputFile, "P2\n%d %d\n%d\n", structure->width, structure->height,
                                       structure->maxGray);

        if (nBytesWritten < 0) { /* dimensional write failed    */
            /* free memory                   */
            free(structure->commentLine);
            free(structure->imageData);

            /* print an error message        */


            /* return an error code          */

            printf("ERROR: Bad Dimensions (%s)\n", filename);

            /* return an error code          */
            exit(EXIT_BAD_DIMENSIONS);
        }

        for (unsigned char *nextGrayValue = structure->imageData;

             nextGrayValue < structure->imageData + structure->nImageBytes; nextGrayValue++) {


            /* get next char's column        */
            int nextCol = (nextGrayValue - structure->imageData + 1) % structure->width;




            /* write the entry & whitespace  */
            nBytesWritten = fprintf(outputFile, "%d%c", *nextGrayValue, (nextCol ? ' ' : '\n'));

            /* sanity check on write         */
            if (nBytesWritten < 0) { /* data write failed   */
                /* free memory           */
                free(structure->commentLine);
                free(structure->imageData);

                /* print error message   */
                printf("ERROR: Bad Data (%s)\n", filename);

                /* return an error code  */
                exit(EXIT_BAD_DATA);
            }



        }
    }
    // Use this code to write if File is in binary
    if(*structure->magic_Number == MAGIC_NUMBER_RAW_PGM){
        size_t nBytesWritten = fprintf(outputFile, "P5\n%d %d\n%d\n", structure->width, structure->height,
                                       structure->maxGray);

        if (nBytesWritten < 0) { /* dimensional write failed    */
            /* free memory                   */
            free(structure->commentLine);
            free(structure->imageData);

            /* print an error message        */
            printf("ERROR: Bad Dimensions (%s)\n", filename);

            /* return an error code          */
            exit(EXIT_BAD_DIMENSIONS);
        }

        //write it all once
        fwrite(structure->imageData, 1, structure->nImageBytes, outputFile);
    }

    //close the file
    fclose(outputFile);



    // if successful return back to main file.
    return EXIT_NO_ERRORS;
}