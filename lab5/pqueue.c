/*****************************************
* lab05 -- coen12                        *
* Gordon Reis -- 5/14/19                 *
* priority queue abstract data type      *
*****************************************/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pqueue.h"

#define MAXQUEUESIZE 257

// structs and prototypes
typedef struct pqueue {
    int count;
    int length;
    void** data;
    int (*compare)();
} PQ;

static void doubleSize(PQ *pq);

/** @description: creates a pqueue with given compare function
 * @runtime: O(1)
 */
PQ *createQueue(int (*compare)()) {
    PQ *pq = malloc(sizeof(PQ));
    assert(pq != NULL);
    pq->compare = compare;
    pq->count = 0;
    pq->length = MAXQUEUESIZE;
    pq->data = malloc(sizeof(void*)*pq->length);
    
    return pq;
}

/** @description: frees all allocated memory
 * @runtime: O(n)
 */
void destroyQueue(PQ *pq) {
    int i;
    for(i = 0; i < pq->count; i++) {
        free(pq->data[i]);
    }
    free(pq->data);
    free(pq);
}

/** @description: returns the size of pqueue 
 * @runtime: O(1)
 */
int numEntries(PQ *pq) {
    return pq->count;
}

/** @description: add entry to the end of queue
 * @runtime: O(log n)
 */
void addEntry(PQ *pq, void *entry) {
    // check length of queue
    if(pq->count==pq->length) doubleSize(pq);
    
    // put new entry add end of queue
    pq->data[pq->count] = entry;
    
    // reheap up
    int i = pq->count;
    while(pq->compare(pq->data[i], pq->data[(i-1)/2]) < 0) {
        
        void* temp = pq->data[(i-1)/2];
        pq->data[(i-1)/2] = pq->data[i];
        pq->data[i] = temp;
        
        i = (i-1)/2;
    }
    
    // increment
    pq->count++;
}

/** @description: pop an entry from the start of the priority queue
 * @runtime: O(log n)
 */
void *removeEntry(PQ *pq) {
    // save root
    void** elt = pq->data[0];
    
    // replace root with end of tree
    pq->data[0] = pq->data[pq->count-1];
    pq->data[pq->count-1] = NULL;
    pq->count--;
    
    // reheap down
    int i = 0;
    int temp = 0;
    while(i*2+1 < pq->count) {
        temp = i*2+1;
        if(i*2+2 < pq->count) {
            if (pq->compare(pq->data[i*2+1], pq->data[i*2+2]) < 0) temp = i*2+1;
            else temp = i*2+2;
        }
        if(pq->compare(pq->data[temp], pq->data[i]) < 0) {
            void* elt = pq->data[temp];
            pq->data[temp] = pq->data[i];
            pq->data[i] = elt;
            i = temp;
        } else break;
    }
    
    // return
    return elt;
}

/**@description: reallocates memory to double size
 * @runtime: O(1)
 */
static void doubleSize(PQ *pq) {
    pq->data=realloc(pq->data, sizeof(pq->data)*2);
    pq->length*=2;
}
