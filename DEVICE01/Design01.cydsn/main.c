/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <string.h>
//宏定义进入命令模式
#define ENTCMD  UART_UartPutString("+++");\
                while(UART_UartGetChar() == 0);\
                UART_UartPutString("a\n")
                
#define Delay_500ms
#define ATDELAY  CyDelay(50) 
#define D1s CyDelay(1000)                

#define D1s CyDelay(1000) 
#define BZ 300
char8 tbuf[BZ];
char8 rbuf[BZ];
short msgtype = 0x0002;
char rid[9];

uint8 outvalue = 0xff;
uint8 keyvalue = 0u;
uint8 lvalue = 0xff;   

char ch;
#pragma pack(1)
struct attr_data {
    //属性名占13字节
    char8 attr_name[13];
    //属性性质（读，写，可读可写）占1个字节
    char8 property;
    //属性值4个字节
    int data;
    //属性值的倍数占4个字节
    int times;
};
#pragma pack(1)
typedef struct device_link
{
    //设备id 占4个字节
    unsigned int device_ip;
    //设备名字占22 个字节
    unsigned char name[22];
    //设备ID 占9个字节
    char8 device_id[9];
    //是否绑定了网关1个字节
    char8 locked;
    //设备是否在线, 在设备中只是为了对齐使用
    char8 online;
    //绑定的网关ID 13 
    char8 gate_id[13];
    //定义设备的10个参数参数
    struct attr_data attrs[10];
    struct device_link * pNext;
} device, *pdevice;
device dc;
//写一个函数来put字符数组 发送n字节的数组
void put_char_array(int16 size, char8 arr[]) {
    int i;
    UART_SpiUartClearTxBuffer();
    for(i=0;i<size;i++) 
        UART_UartPutChar(arr[i]);
}
void sendInfo(void) {
    memcpy(tbuf, &msgtype, 2); 
    memcpy(tbuf+2, &dc, 274);
    
    
//    CyDelay(100);
    put_char_array(300, tbuf);
}
void read_nchar(uint16 length, char8 buf[]) {
    uint32 ch;
    uint16  i;
    //UART_SpiUartClearRxBuffer();
    //这里千万不要清除 rxbuffer，会清除掉读入的第一位，导致错位
    //UART_SpiUartClearTxBuffer();
    for (i = 0;i<length;i++) {     
        //while((ch = UART_UartGetChar()) == 0u);
        while((ch=UART_UartGetByte()) == UART_UART_RX_UNDERFLOW);
        buf[i] = ch;
    }
}
CY_ISR(UART_SCB_IRQ_Interrupt)
{
    //UART_SCB_IRQ_Stop();//关闭串口中断


    
    #ifdef UART_SCB_IRQ_INTERRUPT_INTERRUPT_CALLBACK
        UART_SCB_IRQ_Interrupt_InterruptCallback();
    #endif /* UART_SCB_IRQ_INTERRUPT_INTERRUPT_CALLBACK */
    /*  Place your Interrupt code here. */
//   ch = UART_UartGetByte();
    read_nchar(1, rbuf);
    if(rbuf[0] == 0x05) {
        
        //ch = UART_UartGetByte();
        read_nchar(1, rbuf);
        if(rbuf[0] == 0x00) {
            //再读298字节
            read_nchar(270, rbuf);
            
            memset(rid, 0, 9);
            memcpy(rid, rbuf+26, 9);
            //UART_UartPutString(rid);

           // UART_UartPutChar(rbuf[26]);
           // UART_UartPutString("\r\n");
            if( strcmp(rid, dc.device_id) == 0) {
//                UART_UartPutString("ss\r\n");
//                UART_UartPutString("\r\n");
//                UART_UartPutChar(rbuf[67]+48);
//                UART_UartPutString("\r\n");
                if(rbuf[67]==2) {  
                    //关 P2.5 给高
                    dc.attrs[0].data = 2;
                    outvalue = 0xff;
                    OutputPinSW_Write(outvalue);
                } else if(rbuf[67]==1) {
                    //开 P2.5 给低
                    outvalue = 0x00;
                    OutputPinSW_Write(outvalue);
                    dc.attrs[0].data = 1;
                }
                
//                OutputPinSW_Write(outvalue);
//                outvalue = !outvalue;                
            }
 
        }      
    }
    
    //CyDelay(100);
    UART_SpiUartClearRxBuffer();//清除串口接收缓冲区
    bzero(rbuf, BZ);
    UART_ClearRxInterruptSource(UART_INTR_RX_NOT_EMPTY);//清除串口接收中断标志位,这个很重要如果没有清除的话会无限进入串口接收中断函数即UART_SCB_IRQ_Interrupt函数
    
    /* `#END` */
}  

CY_ISR(SWPin_Control)
{
    CyDelay(100);
    keyvalue = InputPin_Read();
    if(keyvalue != lvalue) {
        outvalue = ~outvalue;
        OutputPinSW_Write(outvalue);
        lvalue = keyvalue;
        //改变状态
        if(outvalue == 0x00){
             dc.attrs[0].data = 1; 
        } else {
            dc.attrs[0].data = 2; 
        }
    }
    InputPin_ClearInterrupt();
}

int main()
{
    //InputInterrupt_StartEx(SWPin_Control);
    //CY_ISR_PROTO(MY_UART_SCB_IRQ_Interrupt);
    //UART_SCB_IRQ_StartEx(MY_UART_SCB_IRQ_Interrupt);//使能中断
    
    InputInterrupt_StartEx(SWPin_Control);
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    //一定要的
    CyDelay(2000);
    UART_Start();
    //UART_SCB_IRQ_Start();
    //进入透传模式前关闭串口中断
    UART_SCB_IRQ_Stop();
    
    
    
    ENTCMD;
    D1s; //延时要够
    //设置socket
    UART_UartPutString("AT+NETP=UDP,SERVER,9799,0.0.0.0\n");
    CyDelay(2000);
    
    //重启
    ATDELAY;
    UART_UartPutString("AT+Z\r\n");
    
    D1s;
    D1s;
    D1s;
    UART_SpiUartClearRxBuffer();
    UART_SpiUartClearTxBuffer();
    ENTCMD;
    
    D1s;
    UART_UartPutString("AT+ENTM\r\n");
    D1s;
    //进入透传模式
    CyDelay(2000);
    UART_SCB_IRQ_Start();
    //UART_SpiUartPutArray("Helon Test\r\n",sizeof("Helon Test\r\n"));
  //  UART_SCB_IRQ_StartEx(UART_SCB_IRQ_Interrupt);
    // OutputPinSW_Write(outvalue);
    
        dc.device_ip = 0x0005;
        memcpy(dc.device_id, "123456", 7); 
        strcpy(dc.name, "智能台灯");
        //memcpy(dc.attrs[0].attr_name, "开关", 13); 
        strcpy(dc.attrs[0].attr_name, "开关");
        dc.attrs[0].data=1;
        dc.attrs[0].property = 0x07;
        memcpy(tbuf, &msgtype, 2); 
        memcpy(tbuf+2, &dc, 274);
    
    for(;;) {
        
        sendInfo();
        CyDelay(10000);
    }
}

/* [] END OF FILE */
