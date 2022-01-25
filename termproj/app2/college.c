 /*******************************************
 * term project -- coen12                   *
 * Gordon Reis -- 6/03/19                   *
 * main function for application 2          *
 *******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "table.h"

#define NUM_STUDENTS 3001 // nextprime(3000)

int main() {
    // set a time seed for psuedorandom number generator
    srand(time(NULL));
    
    SET* sp = createDataSet(NUM_STUDENTS);
    
    int i;
    int id = 0;
    int age;
    int increment;
    
    // create 1000 students in the hash table
    for(int i = 0; i < 1000; i++) {
        age = (rand() % 13) + 18;
        increment = (rand() % 2) + 1;
        id += increment;
        addID(sp, id);
    }
    printf("\nInsertions Complete\n\n");
    
    int randID = (rand() % (3001)) + 1;
    
    // search is handled in remove function
    removeID(sp, randID);
    
    destroyDataSet(sp);
    
    
    return 0;
}
