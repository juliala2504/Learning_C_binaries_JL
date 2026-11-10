/*
 * ============================================================
 * reader.c — Implementation of the reading functions
 * ============================================================
 *
 * WHAT IS THIS FILE?
 * reader.h only declares the functions. This file contains the bodies: the code that actually opens the files, reads the lines, stores the numbers and frees the memory.
 *
 * WHICH HEADERS DO WE NEED?
 *   stdio.h  : file functions (fopen, fgets, sscanf, fclose, rewind)
 *              and printf for error messages
 *   stdlib.h : memory functions (malloc, free)
 *   reader.h : my own types and prototypes
 */

#include <stdio.h>
#include <stdlib.h>
#include "reader.h"



// read_relation: reads The_mass_Mv_data_in_AppA_KTG93.dat, which has two numbers per line: bolometric magnitude and mass. path: the file name rel: pointer to the Relation the caller wants filled. Returns: 0 on success, -1 on error.


int read_relation(const char *path, Relation *rel) {

// Open the file with fopen and return a FILE pointer on success, or NULL on failure

FILE *file = fopen(path, "r");

/* Always check the result of fopen. If it is NULL, we cannot
 continue, so we prin*t a message and return the error code. */
if (file == NULL) {
    printf("Error: could not open file '%s'.\n", path);
    return -1;
}

/* A buffer for one line of text. fgets will fill it. */
char line[LINE_LENGTH];
