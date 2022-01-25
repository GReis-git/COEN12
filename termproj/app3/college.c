 /*******************************************
 * term project -- coen12                   *
 * Gordon Reis -- 6/03/19                   *
 * main function for application 3          *
 *******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define NUM_STUDENTS 1000

int main() {
    // set a time seed for psuedorandom number generator
    srand(time(NULL));
    
    LIST* lp = createDataSet();
    
    int i;
    int id = 0;
    int age;
    int increment;
    
    // create 1000 students in the list
    for(int i = 0; i < NUM_STUDENTS; i++) {
        age = (rand() % 13) + 18;
        increment = (rand() % 2) + 1;
        id += increment;
        insertion(lp, id, age);
    }
    printf("\nInsertions Complete\n\n");
    
    int randID = (rand() % (2000)) + 1;
    
    // search based on age (yields many results ~NUM_STUDENTS/MaxAgeGap)
    searchAge(lp, age);
    printf("\n");
    
    if (searchID(lp, randID) != -1) deletion(lp, randID);
    maxAgeGap(lp);
    destroyDataSet(lp);
    printf("\n");
    
    return 0;
}
