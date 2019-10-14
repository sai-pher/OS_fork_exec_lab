//
// Created by sai-pher on 20/09/2019.
//

/**
 * Implement a parent process that finds and prints out the sum of all prime numbers that are
 * less than a given input number. Within this parent process, implement a child process that
 * requests for a number and prints out the sum of all even numbers less than that number.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <sys/wait.h>

#define TRUE 0
#define FALSE -1

/**
 * Returns the sum of all even numbers less than that number n.
 *
 * Param -> int n: A number >= 0.
 *
 * Return -> int res: The sum of all even values less than n.
 * */
int sum_evens(int n);

/**
 * Finds and returns the sum of all prime numbers that are less than a given input number n.
 *
 * Param -> int n: A number > 1.
 *
 * Return -> int res: The sum of all primes less than n.
 * */
int sum_primes(int n);

int main() {

    int x = -1;
    while (x < 0) {
        printf("Enter a number greater than 1 (for primes): ");
        scanf("%d", &x);
    }

    printf("\nSum of primes less than %d: %d\n", x, sum_primes(x));

    // Process tree

    int child_process = fork();

    if (child_process < 0) {
        printf("Error: Child process could not be created.\n");
        exit(1);
    } else if (child_process == 0) {
        // Do magic
        printf("\nSuccess: In child\n");

        int y = -1;
        while (y < 2) {
            printf("Enter a number greater than 0 (for evens): ");
            scanf("%d", &y);
        }

        printf("\nSum of Evens less than %d: %d\n", y, sum_evens(y));
    } else {
        // Complete
        wait(NULL);
        printf("\ncomplete: \nParent: %d\nChild: %d\n", (int) getpid(), child_process);
    }

    return 0;
}

int sum_evens(int n) {
//    int x = -1;
    int res = 0;

    if (n > -1) {
        for (int i = 0; i < n; i += 2) {
            res += i;
        }
    }
    return res;
}

int sum_primes(int n) {

    int res = 0;

    if (n > 1) {
        for (int i = 2; i < n; i += 1) {
            int prime = TRUE;
            for (int j = 2; j < i; j += 1) {
                if (i % j == 0) {
                    prime = FALSE;
                    break;
                }
            }
            if (prime == TRUE) {
                res += i;
            }
        }
    }

    return res;
}
