 /*****************************************
 * lab03 -- coen12                        *
 * Gordon Reis -- 4/24/19                 *
 * functions for hash table               *
 *****************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

#define EMPTY 0
#define DELETED 1
#define FILLED 2

// prototype funtions and structs
static unsigned strhash(char *s);
static int searchElement(SET *sp, char *elt, bool *found);

typedef struct set {
    int count;
    int length;
    char **data;
    char* flags;
} SET;

// Description: Creates the initial set and allocates necessary memory
// Runtime: O(n)
SET *createSet(int maxElts) {
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char*)*maxElts);
    sp->flags = malloc(sizeof(char)*maxElts);
    assert(sp->data != NULL);
    
    for(int i = 0; i < sp->length; i++) {
        sp->flags[i] = EMPTY;
    }
    return sp;
}

// Description:adds an element to data under sp
// Runtime: O(n)
void addElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    bool found = false;
    int num = searchElement(sp, elt, &found);

    if(found == false) {
        sp->data[num] = strdup(elt);
        sp->count++;
        sp->flags[num] = FILLED;
    }
}

// Description: frees all allocated memory
// Runtime: O(n)
void destroySet(SET *sp) {
    assert(sp != NULL);
    for (int i = 0; i < sp->count; i++) {
        free(sp->data[i]);
    }
    free(sp->data);
    free(sp->flags);
    free(sp);
    
}

// Description: returns the number of elements in data
// Runtime: O(1)
int numElements(SET *sp) {
    assert(sp!=NULL);
    return sp->count;
}

// Description: Finds elt in sp->data and returns elt if found
// Runtime: O(log n)
char *findElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    bool found = false;
    searchElement(sp, elt, &found);
    if(found == true) {
        return elt;
    } else return NULL;
}

// Description: Hashing function used to store string as an int
// Runtime: O(1)
unsigned strhash(char *s) {
    unsigned hash = 0;
    while (*s != '\0')
        hash = 31 * hash + *s ++;
    return hash;
}

// Description: searches for an element and returns its location or to be added location
// Runtime: O(n)
static int searchElement(SET *sp, char *elt, bool *found) {
    
    assert(sp!=NULL && elt!=NULL);
    int num = strhash(elt) % sp->length;
    int firstDeleted = -1;
    while (sp->flags[num] != EMPTY) {
        if (sp->flags[num] == DELETED) {
            if (firstDeleted == -1) {
                firstDeleted = num;
            }
        }
        else if (sp->flags[num] == FILLED) {
            if (strcmp(sp->data[num],elt) == 0) {
                *found = true;
                return num;
            }
        }
        num = (num+1)%sp->length;
    }
    
    if (firstDeleted == -1) {
        return num;
    }
    return firstDeleted;
}

// Description: Removes a value from sp->data and marks position as DELETED in flags
// Runtime: O(n)
void removeElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    bool found = false;
    int num = searchElement(sp, elt, &found);
    if (found == true) {
        sp->flags[num] = DELETED;
        sp->count--;
    } else return;
}

// Description: returns the pointer to the set sp
// Runtime: O(1)
char **getElements(SET *sp) {
    assert(sp!=NULL);
    char **elts;
    elts = malloc(sizeof(char*)*sp->count);
    int index = 0;
    for (int i = 0; i < sp->length; i++) {
        if (sp->flags[i] == FILLED) {
            elts[index] = strdup(sp->data[i]);
            index++;
        }
    }
    
    return elts;
}
