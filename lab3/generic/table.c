 /*******************************************
 * lab03 -- coen12                          *
 * Gordon Reis -- 4/24/19                   *
 * functions for hash table of generic data *
 *******************************************/


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
static int searchElement(SET *sp, void *elt, bool *found);

typedef struct set {
    int count;
    int length;
    void **data;
    char* flags;
    int (*compare)();
    unsigned (*hash)();
    
} SET;

// Description: Creates the initial set and allocates necessary memory
// Runtime: O(n)
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(void*)*maxElts);
    sp->flags = malloc(sizeof(char)*maxElts);
    assert(sp->data != NULL);
    int i;
    for(i = 0; i < sp->length; i++) {
        sp->flags[i] = EMPTY;
    }
    
    sp->compare = compare;
    sp->hash = hash;
    return sp;
}

// Description:adds an element to data under sp
// Runtime: O(n)
void addElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    bool found = false;
    int num = searchElement(sp, elt, &found);

    if(found == false) {
        sp->data[num] = elt;
        sp->count++;
        sp->flags[num] = FILLED;
    }
}

// Description: frees all allocated memory
// Runtime: O(n)
void destroySet(SET *sp) {
    assert(sp != NULL);
    
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
void *findElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    bool found = false;
    int num = searchElement(sp, elt, &found);
    if(found == true) {
        return sp->data[num];
    } else return NULL;
}


// Description: searches for an element and returns its location or to be added location
// Runtime: O(n)
static int searchElement(SET *sp, void *elt, bool *found) {
    
    assert(sp!=NULL && elt!=NULL);
    int num = (*sp->hash)(elt) % sp->length;
    int firstDeleted = -1;
    while (sp->flags[num] != EMPTY) {
        if (sp->flags[num] == DELETED) {
            if (firstDeleted == -1) {
                firstDeleted = num;
            }
        }
        else if (sp->flags[num] == FILLED) {
            if ((*sp->compare)(sp->data[num],elt) == 0) {
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
void removeElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    bool found = false;
    int num = searchElement(sp, elt, &found);
    if (found == true) {
        sp->flags[num] = DELETED;
        sp->count--;
    } else return;
}

// Description: returns the pointer to a copy of the set sp
// Runtime: O(1)
void *getElements(SET *sp) {
    assert(sp!=NULL);
    void **elts;
    elts = malloc(sizeof(void*)*sp->count);
    int index = 0;
	int i;
    for (i = 0; i < sp->length; i++) {
        if (sp->flags[i] == FILLED) {
            elts[index] = (sp->data[i]);
            index++;
        }
    }
    
    return elts;
}
