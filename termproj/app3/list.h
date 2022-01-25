 /*******************************************
 * term project -- coen12                   *
 * Gordon Reis -- 06/03/19                  *
 * header file for list in application 1    *
 *******************************************/

#ifndef LIST_H
#define LIST_H

typedef struct list LIST;

typedef struct node NODE;

extern LIST *createDataSet();

extern void destroyDataSet(LIST *lp);

extern int searchAge(LIST *lp, int age);

extern int searchID(LIST *lp, int id);

extern void insertion(LIST *lp, int id, int age);

extern void deletion(LIST *lp, int id);

extern int maxAgeGap(LIST *lp);

#endif
