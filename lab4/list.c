/*****************************************
* lab04 -- coen12                        *
* Gordon Reis -- 5/14/19                 *
* linked list functions                  *
*****************************************/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

// structs

typedef struct node {
    void* data;
    struct node* next;
    struct node* prev;
} NODE;

typedef struct list {
    int count;
    NODE *head;
    int (*compare)();
} LIST;

/* @description: creates a linked list with a memory allocated dummy node
 * @runtime: O(1)
 */
LIST *createList(int (*compare)()) {
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->compare = compare;
    lp->head = malloc(sizeof(NODE));
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    return lp;
}

/* @description: frees all allocated memory
 * @runtime: O(n)
 */
void destroyList(LIST *lp) {
    assert(lp != NULL);
    while(lp->count!=0) {
        removeFirst(lp);
    }
    
    
    free(lp);
    

}

/* @description: returns the number of items in the list
 * @runtime: O(1)
 */
int numItems(LIST *lp) {
    assert(lp != NULL);
    return lp->count;
}

/* @description: inserts an item in the first position after the dummy node
 * @runtime: O(1)
 */
void addFirst(LIST *lp, void *item) {
    NODE* temp = malloc(sizeof(NODE));
    temp->data = item;
    temp->next = lp->head->next;
    temp->prev = lp->head;
    lp->head->next->prev = temp;
    lp->head->next = temp;
    lp->count++;
}

/* @description: inserts an item in the last position before the dummy node
 * @runtime: O(1)
 */
void addLast(LIST *lp, void *item) {
    NODE* temp = malloc(sizeof(NODE));
    temp->data = item;
    temp->next = lp->head;
    temp->prev = lp->head->prev;
    lp->head->prev->next = temp;
    lp->head->prev = temp;
    lp->count++;
}

/* @description: removes the item after the dummy node
 * @runtime: O(1)
 */
void *removeFirst(LIST *lp) {
    assert(lp->count > 0);
    NODE* temp = lp->head->next;
    void* data = temp->data;
    lp->head->next = temp->next;
    temp->next->prev = lp->head;
    
    free(temp);
    lp->count--;
    return data;
}

/* @description: removes the item before the dummy node
 * @runtime: O(1)
 */
void *removeLast(LIST *lp) {
    assert(lp->count > 0);
    NODE* temp = lp->head->prev;
    void* data = temp->data;
    lp->head->prev = temp->prev;
    temp->prev->next = lp->head;
    
    free(temp);
    lp->count--;
    return data;
}

/* @description: returns the first item after the dummy node
 * @runtime: O(1)
 */
void *getFirst(LIST *lp) {
    
    assert(lp->head->next != NULL && lp!=NULL);
    return lp->head->next->data;
}

/* @description: returns the last item before the dummy node
 * @runtime: O(1)
 */
void *getLast(LIST *lp) {
    assert(lp->head->prev != NULL && lp!=NULL);
    return lp->head->prev->data;
}

/* @description: searches for a NODE to return for removeItem and findItem
 * @runtime: O(n)
 */
NODE* findNode(LIST *lp, void* item) {
    NODE* temp = lp->head->next;
	int i;
    for(i = 0; i < lp->count; i++) {
        if(lp->compare(temp->data,item) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/* @description: removes an item from the list
 * @runtime: O(n)
 */
void removeItem(LIST *lp, void *item) {
    assert(lp != NULL);
    NODE* temp = findNode(lp, item);
    if (temp == NULL) return;
    temp->next->prev = temp->prev;
    temp->prev->next = temp->next;
    free(temp);
    lp->count--;
}

/* @description: searches for an item and returns it
 * @runtime: O(n)
 */
void *findItem(LIST *lp, void *item) {
    assert(lp != NULL);
    NODE* temp = findNode(lp, item);
    if (temp == NULL) {
        return NULL;
    } else return temp->data;
}

/* @description: creates a copy of the list and returns it
 * @runtime: O(n)
 */
void *getItems(LIST *lp) {
    assert(lp!=NULL);
    void** elts = malloc(sizeof(void*)*lp->count);
    NODE* temp = lp->head->next;
	int i;
    for(i = 0; i < lp->count; i++) {
        elts[i] = temp->data;
        temp = temp->next;
    }
    return elts;
}
