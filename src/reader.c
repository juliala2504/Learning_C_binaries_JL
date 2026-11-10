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
 *   reader.h : my own datatypes and prototypes
 */

#include <stdio.h>
#include <stdlib.h>
#include "reader.h"

/* Define the maximum length of one line in a file, including the line end. */
#define LINE_LENGTH 256

/*
* read_relation
* Reads The_mass_Mv_data_in_AppA_KTG93.dat.
* Each line has two numbers: magnitude and mass.
* Parameters:
*   path : file name, e.g. "files/The_mass_Mv_data_in_AppA_KTG93.dat"
*   rel  : the Relation we fill in
*
* Returns: 0 on success, -1 on error
*/


int read_relation(const char *path, Relation *rel) {

// STEP 1: Open the file with fopen and return a FILE pointer on success, or NULL on failure
FILE *file = fopen(path, "r");

/* Always check the result of fopen. If it is NULL, we cannot
 continue, so we print a message and return the error code. */
if (file == NULL) {
    printf("Error: could not open file '%s'.\n", path);
    return -1;
}

/* A buffer for one line of text. fgets will fill it. */
char line[LINE_LENGTH];

/* STEP 2: Count how many lines have two numbers. We need this count to know how much memory to reserve */

int count = 0;

while (fgets(line, LINE_LENGTH, file) != NULL) {
    double a, b;

/* sscanf returns how many numbers it found in the line. We only count the lines where it found exactly 2 */

    if (sscanf(line, "%lf %lf", &a, &b) == 2) {
        count++;
    }
}



/* STEP 3: Reserve memory for the two lists. malloc returns NULL if there is not enough memory */
rel->mbol = malloc(count * sizeof(double));
rel->mass = malloc(count *sizeof(double));
rel->count = 0;

if (rel->mbol == NULL || rel->mass == NULL) {
    printf("Error: Not enough memory.\n");
    fclose(file);
    return -1;
}

/* STEP 4: read the file a second time and store the values. rewind moves the read position back to the start of the file */
rewind(file);

/*index = the position where the next pair of numbers goes to */
int index = 0;
while (fgets(line, LINE_LENGTH, file) != NULL) {
    double a, b;
    if (sscanf(line, "%lf %lf", &a, &b) == 2) {
    rel->mbol[index] = a; /* magnitude */
    rel->mass[index] = b; /* mass */
    index++;
    }
}

/* STEP 5: Save the number of stored rows and closer the file */
rel->count = index;
fclose(file);

return 0; /* success, yay! */

}











/* read_cluster: reads the SC X Myr.dat files. Each line is either one number (single star) or two numbers (a binary system) with
 * Parameters:
 * path: file name
 * cluster: the Cluster we fill in
 * Returns 0 on success, -1 on error */

int read_cluster(const char *path, Cluster *cluster) {

    /* STEP 1: Open file */

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Error: could not open file '%s'.\n", path);
        return -1;
    }

    char line[LINE_LENGTH];

    /* STEP 2: Count the lines that contain at least one number */
    int count = 0;
    while (fgets(line, LINE_LENGTH, file) != NULL) {
        double a, b;
        /* sscanf returns 1 for one number, 2 for two numbers, and -1 for an empty line. */
        int values = sscanf(line, "%lf %lf", &a, &b);
        if (values >= 1) {
            count++;
        }
    }


    /* STEP 3: Reserve memory for the star list. sizeof(star) is the number of bytes one star needs */
    cluster->stars = malloc(count * sizeof(Star));
    cluster->count = 0;

    if (cluster->stars == NULL) {
        printf("Error: not enough memory.\n");
        fclose(file);
        return -1;
    }
    /* Step 4: read the file a second time and store the stars. */
    rewind(file);

    int index = 0;
    while (fgets(line, LINE_LENGTH, file) != NULL) {
        double a, b;
        int values = sscanf(line, "%lf %lf", &a, &b);

        if (values == 1) {
            /* Single star: m1 is set, m2 stays 0.0. */
            cluster->stars[index].m1 = a;
            cluster->stars[index].m2 = 0.0;
            cluster->stars[index].is_binary = 0;
            index++;
        } else if (values == 2) {
            /* Binary system: both masses are stored. */
            cluster->stars[index].m1 = a;
            cluster->stars[index].m2 = b;
            cluster->stars[index].is_binary = 1;
            index++;
        }
        /* values == -1 (empty line): nothing is stored. */
    }

    /* Step 5: save the number of stars and close the file. */
    cluster->count = index;
    fclose(file);

    return 0;
}


/* ============================================================
 * free_relation / free_cluster
 * Free the memory that malloc reserved. Every malloc needs
 * exactly one matching free, otherwise there is a memory leak.
 * ============================================================ */

void free_relation(Relation *rel) {
    free(rel->mbol);
    free(rel->mass);

    /* Set the pointers to NULL, so we do not accidentally use
     * memory that has already been freed. */
    rel->mbol = NULL;
    rel->mass = NULL;
    rel->count = 0;
}

void free_cluster(Cluster *cluster) {
    free(cluster->stars);
    cluster->stars = NULL;
    cluster->count = 0;
}





