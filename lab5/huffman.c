/*****************************************
* lab05 -- coen12                        *
* Gordon Reis -- 06/02/19                *
* huffman code implemented with pqueue   *
* For all runtimes, h refers to height   *
* of tree and n is # of chars in text.   *
*****************************************/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>
#include "pqueue.h"
#include "pack.h"

// prototypes
typedef struct node NODE;
int compare(NODE* first, NODE* second);
int nodeDepth(NODE* leaf);


/**@description: main function
 * @runtime: O(n)
 */
int main(int argc, char* argv[]) {
	
	// read in file
	FILE* f;
	if((f = fopen(argv[1], "r")) == NULL) return 0;
	
	int frequencies[257] = {0};
	char ch;
	
	//while(fscanf(f, "%c", &ch) == 1) {
    while((ch = fgetc(f)) != EOF) {
        printf("%c", ch);
		frequencies[(int) ch]++;
	}
    fclose(f);
    // end file
	
	// create and initialize priority queue
	PQ *queue = createQueue(compare);
	NODE* leaves[257] = {0};
	int i;
	for(i = 0; i < 257; i++) leaves[i] = NULL;
	
	for(i = 0; i < 256; i++) {
		if(frequencies[i] > 0) {
			NODE* temp = malloc(sizeof(NODE));
			
			temp->parent = NULL;
			temp->count = frequencies[i];
			
			leaves[i] = temp;
			addEntry(queue,temp);
		}
	}	
	
    NODE* EOFNode = malloc(sizeof(NODE));
    EOFNode->parent = NULL;
    EOFNode->count = 0;
    leaves[256] = EOFNode;
	addEntry(queue, EOFNode);
	// end init queue
	
	// create tree with pqueue
	while(numEntries(queue) > 1) {
		NODE* c1 = removeEntry(queue);
		NODE* c2 = removeEntry(queue);
		
		NODE* p = malloc(sizeof(NODE));
		p->parent = NULL;
		p->count = ((c1->count) + (c2->count));
		
		c1->parent = p;
		c2->parent = p;
		
		addEntry(queue, p);
	}
	// end tree
	
	// get depths and printf
	for(i = 0; i < 257; i++) {
		if(leaves[i] != NULL) {
			int depth = nodeDepth(leaves[i]);
			if(isprint(i)) {
				printf("\'%c\': %d x %d bits = %d bits\n", i, frequencies[i], depth, frequencies[i]*depth);
			} else {
				printf("%03o: %d x %d bits = %d bits\n", i, frequencies[i], depth, frequencies[i]*depth);
			}
		}
	}
	// end print
	
	// run pack.c and return
	pack(argv[1], argv[2], leaves);
	return 0;
}

/**@description: compares the count of nodes for our pqueue
 * @runtime: O(1)
 */
int compare(NODE* first, NODE* second) {
	if (first->count > second->count) {
		return 1;
	} else if (first->count < second->count) {
		return -1;
	} else {
		return 0;
	}
}

/**@description: returns the depth of a node on the tree
 * @runtime: O(h)
 */
int nodeDepth(NODE* node) {
	int depth = 0;
	while (node->parent != NULL) {
		node = node->parent;
		depth++;
	}
	return depth;
}
