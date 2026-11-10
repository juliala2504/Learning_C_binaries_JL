/*
 * ============================================================
 * main.c — Main program
 * ============================================================
 *
 * WHAT DOES THIS PROGRAM?
 * It is the entry point: the operating system starts the program
 * at main(). Here we:
 *   1. read the relation file (mass vs. magnitude),
 *   2. read one star cluster file,
 *   3. print some information to check that the reading works,
 *   4. free all the memory we reserved.
 *
 */



#include <stdio.h>
#include "reader.h"

//0 = success, anything else = error.
// "void" means it takes no command line arguments.

int main (void)
{
    int main(void) {

        // Create a Relation variable on the stack. This is not the data itself, only the container: two pointers (mbol, mass) and a count. The actual arrays are reserved later by read_relation() which returns 0 on success and -1 on error

        Relation rel;

        // The "&rel" gives the function the ADDRESS of the variable, so it can fill in the pointers and the count. The & symbol always defines the address for a pointer
        // If 'double' is the variable, then 'double*' is its pointer, *pointer' is then the variable where '&var' is the pointer.

        if (read_relation("files/The_mass_Mv_data_in_AppA_KTG93.dat", &rel) != 0) {
            /* Something went wrong: stop the program and report an error. */
            return 1;   /* 1 = program ended with an error */
        }

        /* rel.count was set by read_relation(), so we can print it. */
        printf("Relation: %d rows read.\n", rel.count);

        /* Only look at rel.mbol[0] and rel.mass[0] if there is at least
         *      one row. Otherwise we would read memory that does not exist. */
        if (rel.count > 0) {
            /* rel.mbol is a pointer to an array. The [0] takes the first
             *          element, just like with any normal array. */
            printf("First row: Mbol = %f, mass = %f\n",
                   rel.mbol[0], rel.mass[0]);
        }

        /* We are done with the relation data, so free its memory now.
         *      "&rel" passes the address again, so free_relation() can set the
         *      pointers to NULL afterwards. */
        free_relation(&rel);


        /* ============================================================
         * PART 2: read one star cluster file
         * ============================================================ */

        /* Cluster variable is only the container. The array of stars is reserved inside read_cluster(). */
        Cluster c;

        if (read_cluster("files/SC100Myr.dat", &c) != 0) {
            return 1;   /* error: stop the program */
        }

        /* ------------------------------------------------------------
         * Count the binary systems.
         * We go through all stars one by one and look at the is_binary
         * flag: 1 = binary, 0 = single star.
         * ------------------------------------------------------------ */

        /* Start counting at zero. */
        int binaries = 0;

        /* A for loop: i starts at 0, runs while i is smaller than the
         *      number of stars, and increases by 1 each time. */
        for (int i = 0; i < c.count; i++) {
            /* c.stars[i] is the i-th Star. The dot (.) reads a field
             *          of that Star, here is_binary. */
            if (c.stars[i].is_binary == 1) {
                binaries++;   /* same as: binaries = binaries + 1 */
            }
        }

        printf("Cluster: %d entries, of which %d binary systems.\n",
               c.count, binaries);


        /* ------------------------------------------------------------
         * Print the first five entries as a check that the data was
         * read correctly.
         * ------------------------------------------------------------ */

        printf("\nFirst 5 entries:\n");

        /* The condition "i < 5 && i < c.count" stops at 5 entries,
         *      or earlier if the cluster has fewer than 5 entries. */
        for (int i = 0; i < 5 && i < c.count; i++) {
            if (c.stars[i].is_binary) {
                /* Binary: print both masses. */
                printf("  Binary system: %f + %f\n",
                       c.stars[i].m1, c.stars[i].m2);
            } else {
                /* Single star: only m1 is meaningful. */
                printf("  Single star:   %f\n", c.stars[i].m1);
            }
        }


        /* ============================================================
         * CLEANUP
         * ============================================================ */

        /* Free the memory reserved for the star list. Every read_*
         *      function has a matching free_* function. Forgetting this
         *      causes a memory leak. */
        free_cluster(&c);

        /* 0 = the program finished successfully. */
        return 0;

}




