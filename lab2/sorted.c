 /*****************************************
 * lab02 -- coen12                        *
 * Gordon Reis -- 4/10/19                 *
 * functions for sorted sets              *
 *****************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

// prototype funtions and structs
static int bSearchElement(SET *sp, char *elt, bool *found);

typedef struct set {
    int count;
    int length;
    char **data;
} SET;


// Description: Creates the initial set and allocates necessary memory
// Runtime: O(1)
SET *createSet(int maxElts) {
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    sp->length = maxElts;
    sp->count = 0;
    sp->data = malloc(sizeof(char*)*maxElts);
    assert(sp->data != NULL);
    return sp;
}

// Description:adds an element to data under sp
// Runtime: O(n)
void addElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    
    bool found = true;
    int insertValue = bSearchElement(sp, elt, &found);
    
    if (found == false) {
        for (int i = sp->count; i > insertValue; i--) {
            sp->data[i] = sp->data[i-1];
        }
        sp->data[insertValue] = strdup(elt);
        sp->count++;
    } else {
        return;
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
    bSearchElement(sp, elt, &found);
    
    if(found == true) {
        return elt;
    } else {
        return NULL;
    }
}

// Description: Binary search to find elt in sp->data
// Runtime: O(log n)
static int bSearchElement(SET *sp, char *elt, bool *found) {
    assert(sp!=NULL && elt!=NULL);
    int mid, hi, lo;
    hi = sp->count-1;
    lo = 0;
    while (hi >= lo) {
        mid = (lo + hi)/2;

        if (strcmp(sp->data[mid],elt) > 0) {
            hi = mid-1;
        } else if (strcmp(sp->data[mid],elt) < 0) {
            lo = mid+1;
        } else {
            *found = true;
            return mid;
        }
    }
    *found = false;
    return lo;
}

// Description: Removes a value from sp->data and moves everything else down
// Runtime: O(n)
void removeElement(SET *sp, char *elt) {
    assert(sp!=NULL && elt!=NULL);
    bool found;
    int location = bSearchElement(sp, elt, &found);
    if (found == true) {
        for(int i = location; i < sp->count-1; i++) {
                sp->data[i] = sp->data[i+1];
        }
        sp->count--;
    }
}

// Description: returns the pointer to the set sp
// Runtime: O(1)
char **getElements(SET *sp) {
    assert(sp!=NULL);
    return sp->data;
}
