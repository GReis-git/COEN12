 /*****************************************
 * lab02 -- coen12                        *
 * Gordon Reis -- 4/10/19                 *
 * functions for unsorted sets            *
 *****************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "set.h"

// prototype functions and structs
static int searchElement(SET *sp, char *elt);

typedef struct set {
    int count;
    int length;
    char **data;
} SET ;

// Description: Creates the initial set
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

// Description: adds an element to data under sp if it does not exist in the set already
// Runtime: O(n)
void addElement(SET *sp, char *elt) {
    
    //sp->data[sp->count] = malloc(sizeof(char)*(strlen(elt)+1);
    
    if (sp->count == sp->length) {
        return;
    }
    else if (searchElement(sp, elt) == -1) {
        sp->data[sp->count] = strdup(elt);
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
    return sp->count;
}

// Description: Searches for elt in sp->data and returns elt
// Runtime: O(n)
char *findElement(SET *sp, char *elt) {
    if(searchElement(sp, elt) != -1) {
        return elt;
    } else {
        return NULL;
    }
}

// Description: Searches for elt in sp->data and returns the index location or -1 if not found
// Runtime: O(n)
static int searchElement(SET *sp, char *elt) {
    
    for(int i = 0; i < sp->count; i++) {
        if (strcmp(elt, sp->data[i]) == 0) {
            return i;
        }
    }
    return -1;
}

// Description: Removes an element from the set
// Runtime: O(1)
void removeElement(SET *sp, char *elt) {
    int location = searchElement(sp, elt);
    sp->data[location] = sp->data[sp->count-1];
    sp->count--;
}

// Description: returns the pointer to the set sp
// Runtime: O(1)
char **getElements(SET *sp) {
    return sp->data;
}



