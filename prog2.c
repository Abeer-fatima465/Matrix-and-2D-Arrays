#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<time.h>
#include <string.h>

//#include "prog2.h"

/**
*
*  Function "stubs" for Assignment 2 exercises.
*
*  See prog2.h for specifications of function behavior.
*
*/



/***********************************************
*                                             **
*   MATRIX FUNCTIONS                          **
*                                             **
*   NOTE:  parameter n ALWAYS expresses the   **
*     dimensions of the square matrix in      **
*     question.                               **
*                                             **
***********************************************/
char **alloc_square_mtx(int n) {

    char **m = (char **) malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        m[i] = (char *) malloc(n * sizeof(int));
    }
    return m;
}

void free_square_mtx(char **m, int n) {
    for (int i = 0; i < n; i++) {
        free(m[i]);
    }
    return free(m);
}

void pop_mtx_alpha(char **m, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            m[i][j] = 'a' + rand() % 26;
        }
    }
}


void display_mtx(char **m, int n) {
    for (int i = 0; i < n; i++) {
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf("%c", m[i][j]);
        }
    }
}

void swap_rows(char **m, int n, int r1, int r2) {
    if (r1 >= 0 || r1 < n || r2 >= 0 || r2 < n) {
        for (int i = 0; i < n; i++) {
            char temp = m[r1][i];
            m[r1][i] = m[r2][i];
            m[r2][i] = temp;
        }
    }

}

void swap_cols(char **m, int n, int c1, int c2) {
    if (c1 >= 0 || c1 < n || c2 >= 0 || c2 < n) {
        for (int i = 0; i < n; i++) {
            char temp = m[i][c1];
            m[i][c1] = m[i][c2];
            m[i][c2] = temp;
        }
    }

}

void rotate_right(char **m, int n) {

    //Swapping the rows and cols in clockwise direction
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            char temp = m[i][j];
            m[i][j] = m[n - 1 - j][i];
            m[n - 1 - j][i] = m[n - 1 - i][n - 1 - j];
            m[n - 1 - i][n - 1 - j] = m[j][n - 1 - i];
            m[j][n - 1 - i] = temp;
        }
        // swap_cols(m,n,i,n-i-1);
    }
}


void floating_boulders(char **m, int n, int nb) {
    if (nb > (n * n)) {
        nb = n * n;
    } else if (nb < 0) {
        nb = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            m[i][j] = '.';
        }
    }
    srand(time(0));
    while (nb > 0) {
        int rand_r = (rand() % n);
        int rand_c = (rand() % n);
        if (m[rand_r][rand_c] == '.') {
            m[rand_r][rand_c] = '#';
            nb--;
        }
    }

}


void mountains(char **m, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int x = rand() % n;
        for (int j = 0; j < n; j++) {
            if (j < x) {
                m[j][i] = '.'; // air
            } else
                m[j][i] = '#'; //land
        }
    }
}

void sink(char **m, int n) {
    for (int i = n - 1; i > 0; i--) {
        swap_rows(m, n, i, i - 1);
    }
    for (int j = 0; j < n; j++) {
        m[0][j] = '.';
    }
}


void gravity(char **m, int n) {
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (m[i][j] == '.') {
                for (int k = i - 1; k >= 0; k--) {
                    if (m[k][j] != '.') {
                        char temp = m[i][j];
                        m[i][j] = m[k][j];
                        m[k][j] = temp;
                        break;
                    }
                }
            }
        }
    }
}


/***********************************************
*                                             **
*   STRING FUNCTIONS                          **
*                                             **
***********************************************/


void str_trim(char *s) {
    int i;
    int before_space = 0;
    int after_space = 0;
    while (before_space < strlen(s) && s[before_space] == ' ') {
        before_space += 1;
    }
    while (after_space < strlen(s) && s[strlen(s) - after_space - 1] == ' ') {
        after_space += 1;
    }
    for (i = before_space; i < strlen(s) - after_space; i++) {
        s[i - before_space] = s[i];
    }
    s[strlen(s) - before_space - after_space] = '\0';

}

int str_search(char *s, char *pattern) {
    int find;
    int fd_dx;
    if (strlen(s) < strlen(pattern)) {
        return -1;
    }
    for (int i = 0; s[i] != '\0'; i++) {
        int curr_dex = i; //search for patterns from current index
        find = 1;
        int j;

        for (j = 0; pattern[j] != '\0' && s[i + j] != '\0'; j++) {
            if (s[i + j] != pattern[j]) { //if the patterns are not found break
                find = -1;
                break;
            }
        }

        if (find >= 0) {
            return i;
        }
    }
    return -1;

    //return -1;  // just a placeholder to make gcc happy for now

}


#ifndef _LIB  // DO NOT REMOVE THIS LINE!!!
// IT DOESN"T CHANGE HOW YOUR PROGRAM
// WORKS, BUT IT GIVES US A WAY TO CALL
// YOUR FUNCTIONS FROM OUR CODE FOR
// TESTING

/**
* Write a test driver in main below to exercise and
*   your function implementations.
*
* Think carefully about your test cases!
*/
int main() {
    int n = 6;
    //Test allocation
    char **m = alloc_square_mtx(n);

    //Test random lowercase function
    pop_mtx_alpha(m, n);
    printf("\n \n Test random lowercase function...\n");
    display_mtx(m, n);

    //Test swap rows function
    printf("\n\n Test swaps rows function...\n");
    swap_rows(m, n, 0, 3);
    display_mtx(m, n);
    //   Test swap cols function
    printf("\n\n Test swap cols function...\n");
    swap_cols(m, n, 1, 3);
    display_mtx(m, n);
//
//    //Test rotate function
    rotate_right(m, n);
    printf("\n\n Test rotate right function...\n");
    display_mtx(m, n);

    //Test boulders function
    int nb = 5;
    floating_boulders(m, n, nb);
    printf("\n\n Test floating boulders function...\n");
    display_mtx(m, n);

    //Test gravity function
    gravity(m, n);
    printf("\n\n Test gravity function...\n");
    display_mtx(m, n);

    //Test mountains function
    mountains(m, n);
    printf("\n\n Test mountains function...");
    display_mtx(m, n);

    //Test sink functions
    sink(m, n);
    printf("\n\n Test sink function...\n");
    display_mtx(m, n);

    //Test trimming of strings
    int len = 17;
    printf("\n\n Test string trim function...\n");
    printf("\n Original string: \n");
    char s[] = "    ABCD dd WW    \n";
    printf("%s", s);
    str_trim(s);
    printf("\n Trimmed string: \n");
    printf("%s\n", s);


//    printf(" Test string trim function...\n");
//    char newString[40] = "       a   b   \n";
//    printf("the original string: \n");
//    printf("\n%s", newString);
//    str_trim(newString);
//    printf("Trimmed string: \n");
//    printf("\n%s", newString);

    //Test Search results
    char source[16] = "abc";
    char pattern[16] = "abcd";
    printf("\n\nTest search function: ");
    printf("\n%d\n", str_search(source, pattern));


    return 0;
}


#endif        // DO NOT REMOVE THIS LINE!!!
