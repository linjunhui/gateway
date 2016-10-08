#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include "devicelink.h"

//创建设备链表
pdevice_link create_list(void) {
	//创建一个节点 
	pdevice_link phead = (pdevice_link)malloc(sizeof(device_node));
	if (NULL == phead) {
		printf("create list failed!\n");
		exit(-1);
	}
	phead->pNext = NULL;

	return phead;
}

//根据设备id来移除链表中的设备，传入链表和要移除的设备的id
void remove_from_list(pdevice_link phead, char *id) {

	pdevice_node t1 = phead;
	pdevice_node t2 = t1->pNext;


	while(NULL !=t2 && strcmp(t2->device_id, id) != 0) {
		t1=t1->pNext;
		t2=t2->pNext;
	}

	if(NULL != t2) {
		t1->pNext = t2->pNext;
		free(t2);
	}

	// pdevice_node tmp = phead;
	// pdevice_node p = phead->pNext;
	// pdevice_node node1 = phead->pNext;
	// pdevice_node node2 = NULL;


	// while(node1 != NULL) {
	// 	node2 = node1;
		
	// 	if(strcmp(node2->device_id, id) == 0) {
	// 		node1->pNext = node2->pNext;
	// 		free(node2);
	// 		break;
	// 	}
	// 	node2 = node2->pNext;
	// 	node1 = node1->pNext;
	// }

	// if(p->device_id )


	// while(NULL !=p && strcmp(p->device_id, id) != 0) {
	// 	//保存被删除节点的前一个节点的地址
	// 	tmp = tmp->pNext;
	// 	printf("tmp %p \n", tmp);	
	// 	p = p->pNext;
	// }

	// if(p != NULL) {
	// 	// printf("找到了 p->device_id %s\n", p->device_id);
	// 	// printf("p 的地址 %p\n", p);
	// 	// printf("tmp->pNext 的地址 %p\n", tmp->pNext);

	// 	pdevice_node tp = p->pNext;
	// 	free(p);
	// 	tmp->pNext = tp;
		
	// }
	
}

void list_add(pdevice_link phead, pdevice_node node) {
	pdevice_node p = phead;
	printf("链表地址%p\n", phead);

	while(NULL != p->pNext){
		printf("p->pNext:%p \n", p->pNext);
		p = p->pNext;		
	}
	
	node->pNext = NULL;
	p->pNext = node;
	printf("node 地址 %p\n", node);
	// printf("node-pNext 地址 %p\n", node->pNext);
	// printf("p-pNext->pNext 地址 %p\n", p->pNext->pNext);
}

void traverse_list(pdevice_link phead) {
	pdevice_node p = phead->pNext;

	while(NULL != p) {
		printf("名字:%s, id: %s online: %c\n", p->name, p->device_id, p->online);
		printf("online: %c\n", p->online);
		p = p->pNext;
	}

	printf("遍历完成\n");
}

//所有随便设置为 离线状态
void traverse_list_off(pdevice_link phead) {
	pdevice_node p = phead->pNext;

	while(NULL != p) {
		printf("名字:%s, id: %s\n", p->name, p->device_id);
		p->online = 'n';
		printf("online: %c\n", p->online);
		p = p->pNext;
	}

	printf("设置离线完成\n");
}