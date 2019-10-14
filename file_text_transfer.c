//
// Created by sai-pher on 20/09/2019.
//

#include <stdlib.h>
#include <stdio.h>

#define ARG_COUNT 3

/**
 * Function to transfer text from one file to another.
 *
 * Param -> char *file_1: A pointer to the name of an existing file to copy from.
 * Param -> char *file_2: A pointer to the name of a file to copy to.
 *
 * Return -> int 0 | -1: An int value flagging if the operation was successful (0) or not (-1).
 * */
int text_transfer(const char *file_1, const char *file_2);

int main(int argc, char const *argv[]) {

    // Quick argument error check block
    if (argc != ARG_COUNT) {
        printf("Error: argc does no match required argument count %d", ARG_COUNT);
        return 1;
    } else {
        for (int i = 0; i < argc; ++i) {
            if (argv[i] == NULL) {
                printf("Error: no argument at position %d", i);
                return 1;
            }
        }
    }

    const char *in_file_name = argv[1];
    const char *out_file_name = argv[2];

    if (text_transfer(in_file_name, out_file_name) == 0)
        return 0;

    return 1;
}

int text_transfer(const char *file_1, const char *file_2) {

    // Create pointers to read - write files.
    FILE *in_file;
    FILE *out_file;

    // File reading block
    in_file = fopen(file_1, "r");                                   // Attempt to read file_1
    if (in_file == NULL) {
        printf("\nError (1): File %s could not be read.\n", file_1);
        exit(1);                                                    // Exit if program fails to read file_1
    } else {

        // file_1 successfully opened, attempt to open copy file.
        out_file = fopen(file_2, "w");
        if (out_file == NULL) {
            printf("\nError (2): File %s could not be read.\n", file_2);
            exit(1);                                                // Exit if program fails to read file_2
        } else {

            // Copy operation
            char nc;
            while (fscanf(in_file, "%c", &nc) == 1) {
                fprintf(out_file, "%c", nc);                        // Write copied nc (new char) to out_file
            }

            // Close files and return success flag.
            fclose(in_file);
            fclose(out_file);

            printf("\nSuccess: Data successfully transferred from %s to %s\n", file_1, file_2);

            return 0;
        }
    }

    return -1;
}

