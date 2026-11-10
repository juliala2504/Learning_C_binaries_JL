/*
 * ============================================================
 * reader.h — Header file (interface)
 * ============================================================
 *
 * WHAT IS THIS FILE?
 * A header file describes WHAT exists (data types and functions),
 * but not HOW it works. The actual work is implemented in reader.c.
 *
 * WHO INCLUDES IT?
 *   - reader.c : implements the functions
 *   - main.c   : calls the functions
 * Both use the same description.
 */


// Include guard: prevents this file from being processed twice. The first time, READER_H gets defined. The second time, the whole block is skipped.
#ifndef READER_H
#define READER_H


// Defines a new type called star which has 2 masses and a flag that says whether it's a binary or not. 1 is binary, 0 is no binary'
typedef struct {
    double m1;        /* mass of the first star (in solar masses) */
    double m2;        /* mass of the second star; 0.0 for single stars */
    int is_binary;    /* 1 = binary system, 0 = single star */
} Star;


// A whole star cluster: a list of stars.
typedef struct {
    Star *stars;      // pointer to the list (memory comes from malloc), pointer is a variable itself
    int count;        // number of stars in the list
} Cluster;


/* The relation from The_mass_Mv_data_in_AppA_KTG93.dat:
 two parallel lists, one for Mbol, one for the mass. */
typedef struct {
    double *mbol;     /* first column: bolometric magnitude */
    double *mass;     /* second column: mass in solar masses. so mbol[1] corresponds to mass[1]*/
    int count;        /* number of rows */
} Relation;




/* ------------------------------------------------------------
 * FUNCTION PROTOTYPES
 * The following are the "signatures" of the functions: return type, name
 * and parameters. The body (the "how") is in reader.c, here only the declaration.
 *
 * Why a prototype? main.c calls these functions. For the compiler
 * to check the calls (correct number and types of arguments), it
 * must know the signature beforehand. This header provides that.
 *
 * Return value of the read functions:
 *    0 = success
 *   -1 = error (file not found or not enough memory)
 * ------------------------------------------------------------ */

/* Reads the relation file into rel.
 path: file path as text (const = not modified by the function)
 rel:  pointer to a Relation that the function fills in */
int read_relation(const char *path, Relation *rel);

/* Reads an SC...Myr.dat file into cluster.
 path:    file path* as text
 cluster: pointer to a Cluster that the function fills in */
int read_cluster(const char *path, Cluster *cluster);

/* Frees the memory reserved with malloc.
 Every malloc needs a matching free */
void free_relation(Relation *rel);
void free_cluster(Cluster *cluster);


#endif
