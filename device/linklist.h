#ifndef __LINKLIST_H_
#define __LINKLIST_H_

#pragma pack(1)
typedef struct deviceAttr {
	char attrName[11];
	char dataType;
	char dataproperty;
	int data;
	char times;

} Attr, *PAttr;

#pragma pack(1)
typedef struct devicelistNode
{
	short msgtype;//消息类型占两个字节
	unsigned int deviceIP;//设备的IP 4个字节
	char name[21];//设备名称占21个字节，可以存10个汉字
	char deviceID[9];//设备的ID
	char locked;	//设备是否绑定了网关
	char gateID[13];	//设备绑定的网关ID

	struct deviceAttr attrs[20];

	struct devicelistNode *pNext;
} devicelistNode, *PdevicelistNode;




PdevicelistNode create_list(void); 
int traverse_list(PdevicelistNode pHead, PdevicelistNode* devices, int n );
int is_empty(PdevicelistNode pHead);
int length_list(PdevicelistNode);
int list_add(PdevicelistNode pdevicelist, PdevicelistNode deviceNode); 



#endif
