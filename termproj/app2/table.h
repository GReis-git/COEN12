 /*******************************************
 * term project -- coen12                   *
 * Gordon Reis -- 06/03/19                  *
 * header file for hash table for app 2     *
 *******************************************/

# ifndef TABLE_H
# define TABLE_H

typedef struct set SET;

extern SET *createDataSet(int maxElts);

extern void destroyDataSet(SET *sp);

extern int numElements(SET *sp);

extern void addID(SET *sp, int ID);

extern void removeID(SET *sp, int ID);

extern int searchID(SET *sp, int ID);

# endif
