#ifndef __DEVICELINK_H_
#define __DEVICELINK_H_

#pragma pack(1)
typedef struct device_link
{
	//设备id 占4个字节
	unsigned int device_ip;

	//设备名字 占 21 个字节
	char name[21];

	//设备ID 占 9个字节
	char deviced_id[9];

	//是否绑定了 网关 1个字节
	char loccked;

	//绑定的网关ID 13 
	char gate_id[13];

	//定义 设备的 10个参数参数

	struct attr_data attrs[10];
} device_node, *pdeviceLink;

#pragma pack(1)
struct attr_data {
	//属性名 占11字节
	char attr_name[11];
	//属性 性质 （读，写，可读可写） 占1个字节
	char property;
	//属性值 4个字节
	int data;
	//属性值的倍数 占4个字节
	int times;
};

//创建设备链表
pdeviceLink create_list(void);
//遍历设备链表
int travese_list(pdeviceLink phead);
//添加结点
int add_list(pdeviceLink phead, device_node node);




