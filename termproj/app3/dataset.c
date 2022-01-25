/*****************************************
* term project -- coen12                 *
* Gordon Reis -- 6/03/19                 *
* linked list implementation for app 3   *
*****************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

// structs and prototypes
typedef struct node {
    int id;
    int age;
    struct node *next;
    struct node *prev;
} NODE;

typedef struct list {
    int max;
    int min;
    int count;
    NODE* head;
} LIST;

// creates the list structure to be used externally
LIST* createDataSet() {
    
    LIST *lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->count = 0;
    lp->min = 30;
    lp->max = 18;
    lp->head = malloc(sizeof(NODE));
    lp->head->next = lp->head;
    lp->head->prev = lp->head;
    lp->head->age = -1;
    printf("Created Data Structure\n");
    return lp;
}

// frees all allocated data
void destroyDataSet(LIST *lp) {
    assert(lp != NULL);
    NODE* temp1 = lp->head;
    NODE* temp2 = lp->head;
    do {
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    } while(temp1 != lp->head);
    free(lp);
    printf("Data Freed\n");
}

// search the list for people of age x
int searchAge(LIST *lp, int age) {
    assert(lp != NULL);
    NODE* temp = lp->head->next;
    printf("Searching for Age: %d.\n", age);
    int i;
    int found = 0;
    for(i = 0; i < lp->count; i++) {
        if(temp->age == age) {
            printf("Student of Age %d found: ID:%d\n", age, temp->id);
            found = 1;
        }
        temp = temp->next;
    }
    if(found != 0) printf("Search Completed\n");
    else printf("Search Completed, No Student of Age:%d Found.\n", age);
    return -1;
    
}

// search the list for a matching ID
int searchID(LIST *lp, int id) {
    assert(lp != NULL);
    NODE* temp = lp->head->next;
    printf("Searching for ID: %d.\n", id);
    int i;
    for(i = 0; i < lp->count; i++) {
        if(temp->id == id) {
            printf("Student of ID %d found: Age:%d\n", id, temp->age);
            return temp->id;
        }
        temp = temp->next;
    }
    printf("Search Unsuccessful, Student not Found\n");
    return -1;
}

// inserts an item to the back of the list
void insertion(LIST *lp, int id, int age) {
    assert(lp != NULL);
    NODE* temp = malloc(sizeof(NODE));
    temp->id = id;
    temp->age = age;
    
    if(age > lp->max) lp->max = age;
    else if (age < lp->min) lp->min = age;
    else;
    
    printf("Inserting Student #%d ID:%d, Age:%d\n", lp->count+1, id, age);
    temp->next = lp->head;
    temp->prev = lp->head->prev;
    lp->head->prev->next = temp;
    lp->head->prev = temp;
    lp->count++;
    printf("Student Insert Successful\n");
}

// deleted searched for item from list
void deletion(LIST *lp, int id) {
    assert(lp != NULL);
    NODE* temp = lp->head->next;
    printf("Deleting Student ID:%d\n", id);
    for(int i = 0; i < lp->count; i++) {
        if(temp->id == id) {
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            free(temp);
            lp->count--;
            printf("Student Deletion Successful\n");
            return;
        }
        temp = temp->next;
    }
    printf("Student Deletion Unsuccessful\n");
}

// calculates max age gap
int maxAgeGap(LIST *lp) {
    assert(lp != NULL);
    printf("Max Age Gap is %d\n", (lp->max-lp->min));
    return lp->max-lp->min;
}







