 /********************************************
 * term project -- coen12                    *
 * Gordon Reis -- 6/03/19                    *
 * functions for hash table in application 2 *
 ********************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "table.h"

#define EMPTY 0
#define DELETED 1
#define FILLED 2

// prototype funtions and structs
static int findID(SET *sp, int ID, bool *found);
static int hash(int ID);

typedef struct set {
    int count;
    int length;
    int *data;
    char* flags;
    
} SET;

// hash function using two primes, a and b, that are relatively prime to each other, and b is length of hash table
static int hash(int ID) {
    return (ID * 32771) % 3001;
}

// creates the data structure to be used externally
SET *createDataSet(int maxElts) {
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(int)*maxElts);
    sp->flags = malloc(sizeof(char)*maxElts);
    assert(sp->data != NULL);
    int i;
    for(i = 0; i < sp->length; i++) {
        sp->flags[i] = EMPTY;
    }
    printf("Created Data Structure\n");
    return sp;
}

// frees all allocated data
void destroyDataSet(SET *sp) {
    assert(sp != NULL);
    free(sp->data);
    free(sp->flags);
    free(sp);
    printf("Data Freed\n");
}

// insert ID into set sp
void addID(SET *sp, int ID) {
    
    printf("Inserting Student #%d ID:%d at position %d\n", sp->count+1, ID, (hash(ID) % sp->length));
    assert(sp!=NULL);
    bool found = false;
    int num = findID(sp, ID, &found);

    if(found == false) {
        sp->data[num] = ID;
        sp->count++;
        sp->flags[num] = FILLED;
        printf("Student Insert Successful\n");
    } else printf("Student Insert Unsuccessful\n");
}

// remove ID from set sp
void removeID(SET *sp, int ID) {
    
    printf("Deleting Student ID:%d\n", ID);
    assert(sp!=NULL);
    bool found = false;
    int num = findID(sp, ID, &found);
    
    if (found == true) {
        sp->flags[num] = DELETED;
        sp->count--;
        printf("Student Deletion Successful\n");
    } else printf("Student Deletion Unsuccessful\n");
}

// externally used search function that returns the ID
int searchID(SET *sp, int ID) {
    assert(sp!=NULL);
    bool found = false;
    int num = findID(sp, ID, &found);
    if(found == true) {
        return sp->data[num];
    } else return -1;
}

// internally used search function that will return the location for input/removal and change external found boolean
static int findID(SET *sp, int ID, bool *found) {
    printf("Searching for ID: %d.\n", ID);
    assert(sp!=NULL);
    int num = hash(ID) % sp->length;
    int firstDeleted = -1;
    
    while (sp->flags[num] != EMPTY) {
        // note deleted spot to be filled
        if (sp->flags[num] == DELETED) {
            if (firstDeleted == -1) {
                firstDeleted = num;
            }
        }
        // if found, return
        else if (sp->flags[num] == FILLED) {
            if (sp->data[num] == ID) {
                *found = true;
                printf("Student of ID %d found\n", ID);
                return num;
            }
        }
        // increment
        printf("Position %d taken, probing for %d\n", num, ((num+1)%sp->length));
        num = (num+1)%sp->length;
        
    }
    // if nothing deleted, take first open spot
    if (firstDeleted == -1) return num;
    // else return first deleted spot
    return firstDeleted;
}

