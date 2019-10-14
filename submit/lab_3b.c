//
// Created by sai-pher on 20/09/2019.
//


/**
 * I) Write a C script that transfers all of the information in one text file to another text file. Let
 * this script take the names of the two text files as parameters.
 *
 * II) Create a parent process that counts and prints the number of words in a given text file,
 * where the name of the text file is provided as a parameter to the parent process. Within this
 * parent process, create a child process to execute the C script written in I above.
 * */

#include <stdlib.h>
#include <stdio.h>
#include <zconf.h>
#include <sys/wait.h>

#define ARG_COUNT 4

/**
 * Function to count words in a .txt file.
 * It does this by counting the ' ' chars in the file.
 *
 * Param -> char *file_name: The name of the file to count.
 *
 * Return -> int word_count: The count of words in file. Returns -1 if some operation fails.
 * */
int count_words(const char *file_name);

int main(int argc, const char *argv[]) {


    // Quick argument error check block
    if (argc != ARG_COUNT) {
        printf("Error: argc does no match required argument count %d, %d, %s\n", ARG_COUNT, argc, argv[0]);
        return 1;
    } else {
        for (int i = 0; i < argc; ++i) {
            if (argv[i] == NULL) {
                printf("Error: no argument at position %d", i);
                return 1;
            }
        }
    }

    int word_count = count_words(argv[1]);
    if (word_count == -1) {
        printf("\nError: Something went wrong with counting\n");
        exit(1);
    } else {
        printf("\nfile %s has %d words\n", argv[1], word_count);
    }

    // Process tree

    int child_process = fork();


    if (child_process < 0) {
        printf("Error: Child process could not be created.\n");
        exit(1);
    } else if (child_process == 0) {
        // Do magic
        printf("\nSuccess: In child\n");

        char *const *args[] = {(char *const *) "../submit/file_text_transfer", (char *const *) argv[2],
                               (char *const *) argv[3], NULL};

        execv((const char *) args[0], (char *const *) args);
    } else {
        // Complete
        wait(NULL);
        printf("\ncomplete: \nParent: %d\nChild: %d\n", (int) getpid(), child_process);
    }

    return 0;
}

int count_words(const char *file_name) {

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("\nError: File %s could not be read.\n", file_name);
        exit(1);
    } else {

        int word_count = 1;
        char nc;
        while (fscanf(file, "%c", &nc) == 1) {
            if (nc == ' ')
                word_count += 1;
        }

        fclose(file);
        printf("\nSuccess: Count complete.\n");
        return word_count;
    }

    return -1;
}

