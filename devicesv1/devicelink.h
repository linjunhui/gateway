#ifndef __DEVICELINK_H_
#define __DEVICELINK_H_

#pragma pack(1)
struct attr_data {
	//属性名 占13字节
	char attr_name[13];
	//属性 性质 （读，写，可读可写） 占1个字节
	char property;
	//属性值 4个字节
	int data;
	//属性值的倍数 占4个字节
	int times;
};

#pragma pack(1)
typedef struct device_link
{
	//设备id 占4个字节
	unsigned int device_ip;

	//设备名字 占 21 个字节
	char name[22];

	//设备ID 占 9个字节
	char device_id[9];

	//是否绑定了 网关 1个字节
	char locked;

	//绑定的网关ID 13 
	char gate_id[13];

	//设备是否在线
	char online;

	//定义 设备的 10个参数参数

	struct attr_data attrs[10];

	struct device_link * pNext;
} device_node, * pdevice_link, *pdevice_node;

//创建设备链表
pdevice_link create_list(void);

//根据设备id来移除链表中的设备，传入链表和要移除的设备的id
void remove_from_list(pdevice_link phead, char *id);

//添加节点到链表
void list_add(pdevice_link phead, pdevice_node node);

//遍历链表，打印节点信息
void traverse_list(pdevice_link phead);
//所有设备设置为 离线状态
void traverse_list_off(pdevice_link phead);

//遍历链表回复给APP
void traverse_to_app(pdevice_link phead, int connfd);  
#endif


