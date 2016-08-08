
# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
#include "linklist.h"

PdevicelistNode create_list(void) {

	PdevicelistNode pHead = (PdevicelistNode)malloc(sizeof(devicelistNode));
	if (NULL == pHead) {
		printf("creat linklist failed!\n");
		exit(-1);
	}

	PdevicelistNode pTail = pHead;
	pTail->pNext = NULL;

	return pHead;
}

int list_add(PdevicelistNode pdevicelist, PdevicelistNode deviceNode) {
	PdevicelistNode p = pdevicelist;

	while(NULL != p->pNext)
		p = p->pNext;
	p->pNext = deviceNode;
}

int traverse_list(PdevicelistNode pHead, PdevicelistNode* devices, int n ) {
	PdevicelistNode p = pHead->pNext;
	int count = 0;

	while(NULL != p) {
		devices[count++] = p;
		p = p->pNext;
	}

	return count;
}
