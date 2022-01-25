 /*******************************************
 * lab04 -- coen12                          *
 * Gordon Reis -- 5/14/19                   *
 * functions for hash table of linked lists *
 * for runtimes, m is maxElts/averagelength *
 * and p is the average size of the lists   *
 *******************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"
#include "list.h"

#define AVERAGE_LENGTH 20

// structs

typedef struct set {
    int count;
    int length;
    LIST** lists;
    int (*compare)();
    unsigned (*hash)();
    
} SET;

/* @description: Creates the initial set and lists and allocates necessary memory
 * @runtime: O(m)
 */
SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()) {
    
    SET *sp = malloc(sizeof(SET));
    assert(sp != NULL);
    
    sp->length = maxElts/AVERAGE_LENGTH;
    sp->count = 0;
    
    sp->compare = compare;
    sp->hash = hash;
    
    sp->lists = malloc(sizeof(void*)*sp->length);
	int i;
    for(i = 0; i < sp->length; i++) {
        sp->lists[i] = createList(sp->compare);
    }
    assert(sp->lists != NULL);
    return sp;
}

/* @description: adds an element to the hashed list
 * @runtime: O(n)
 */
 void addElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    int num = (*sp->hash)(elt) % sp->length;
    if (findItem(sp->lists[num], elt) == NULL) {
        addLast(sp->lists[num], elt);
        sp->count++;
    }
}

/* @description: frees all allocated memory
 * @runtime: O(m)
 */
void destroySet(SET *sp) {
    assert(sp != NULL);
    
	int i;
    for(i = 0; i < sp->length; i++) {
        destroyList(sp->lists[i]);
    }
    
    free(sp->lists);
    free(sp);
    
}

/* @description: returns the number of elements in data
 * @runtime: O(1)
 */
int numElements(SET *sp) {
    assert(sp!=NULL);
    return sp->count;
}

/* @description: Finds elt in sp->data and returns elt if found
 * @runtime: O(p)
 */
void *findElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    int num = (*sp->hash)(elt) % sp->length;
    return findItem(sp->lists[num],elt);
}

/* @description: Removes a value from sp->data and marks position as DELETED in flags
 * @runtime: O(p)
 */
void removeElement(SET *sp, void *elt) {
    assert(sp!=NULL && elt!=NULL);
    int num = (*sp->hash)(elt) % sp->length;
    if (findItem(sp->lists[num], elt) != NULL) {
        removeItem(sp->lists[num], elt);
        sp->count--;
    }
}

/* @description: returns the pointer to a copy of the set sp
 * @runtime: O(n)
 */
void *getElements(SET *sp) {
    assert(sp!=NULL);
    void **elts;
    elts = malloc(sizeof(void*)*sp->count);
    int index = 0;
	int i, j;
    for (i = 0; i < sp->length; i++) {
        void **subElts = getItems(sp->lists[i]);
        for (j = 0; j < numItems(sp->lists[i]); j++) {
            elts[index] = subElts[j];
            index++;
        }
    }
    return elts;
}
