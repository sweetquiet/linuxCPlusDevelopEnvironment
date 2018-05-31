//
//  LoraTest.h
//  CAESKEY
//
//  Created by admindyn on 2018/5/31.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef LoraTest_h
#define LoraTest_h

#include <stdbool.h>
#include <stdio.h>
/*定义data数据帧格式 位域结构体 共用体
 FCtrl 报文格式 第1 - 3位设置 FOptsLen
 第4位设置 RFU
 
 第5位设置 ACK
 
 第6位设置 ADRACKReq
 
 第7位设置 ADR
 
 总共占1个字节
 */
typedef union un_fctrl {
    uint8_t data;
    struct {
        /*
         FOptsLen位字段描述了整个帧可选项(FOpts)的字段长度
         */
        uint8_t foptslen :4;
        uint8_t rfu :1;
        /*
         收到confirmed类型的消息时，接收端要回复一条应答消息(应答位ACK要进行置位)。如果发送者是终端，网络就利用终端发送操作后打开的两个接收窗口之一进行回复。如果发送者是网关，终端就自行决定是否发送应答。
         应答消息只会在收到消息后回复发送，并且不重发。
         */
        uint8_t ack :1;
        uint8_t adrack :1;
        /*
         根据adr 位置 是否有置位
         */
        uint8_t adr :1;
    }up;
    struct {
        /*
         FOptsLen位字段描述了整个帧可选项(FOpts)的字段长度
         */
        uint8_t foptslen :4;
        /*
         帧挂起位(FPending)只在下行交互中使用，表示网关还有挂起数据等待下发，需要终端尽快发送上行消息来再打开一个接收窗口
         */
        uint8_t fpending :1;
        uint8_t ack :1;
        uint8_t rfu :1;
        uint8_t adr :1;
    }down;
}Lora_Frame_Fctrl;

/*
 FOpts字段存放MAC命令，最长15字节，。
 
 如果FOptsLen为0，则FOpts为空。在FOptsLen非0时，则反之。如果MAC命令在FOpts字段中体现，port0不能用(FPort要么不体现，要么非0)。
 
 MAC命令不能同时出现在FRMPayload和FOpts中，如果出现了，设备丢掉该组数据。
 
 端口字段(FPort)
 
 如果帧载荷字段不为空，端口字段必须体现出来。端口字段有体现时，若FPort的值为0表示FRMPayload只包含了MAC命令； FPort的数值从1到223(0x01..0xDF)都是由应用层使用。 FPort的值从224到255(0xE0..0xFF)是保留用做未来的标准应用拓展
 */



typedef struct st_lora_frame_data {
    uint8_t mhdr; //命令字（000 join request 001 join accept 010 unconfirmed data up 011 unconfirmed data down 100 confirmed data up 101 confirmed data down 110 RFU 111 Propritary）
    uint8_t devaddr[4];
    Lora_Frame_Fctrl fctrl;
    uint8_t fcnt[2];
    uint8_t fopts[15];//0-15byte
    uint8_t fport;//1byte
    uint8_t size;
    uint8_t fmpayload[256];//0-256
}Lora_Frame;
/*
 入网数据包 解析顺序
 前面 还有一个 网关发来 NS_GW_INFO 偏移3字节 网关命令字 偏移12字节 网关对应的信息包NS_GW_RXPKT_INFO
 
 
 NS_GW_RXPKT_INFO 包含 NS_GW_RX_INFO结构体数组
 
 NS_GW_RX_INFO 结构体 对应一个终端
 
 Data +0 前8个字节 APPEUI 占8个字节
 
 偏移8个字节 Data +9 DEVEUI 占8个字节
 
 偏移16个字节 Data +17  DevNonce 占2个字节
 
 
 */
/*
 上行数据包 解析顺序
 前面 还有一个 网关发来 NS_GW_INFO 偏移3字节 网关命令字 偏移12字节 网关对应的信息包NS_GW_RXPKT_INFO
 
 
 NS_GW_RXPKT_INFO 包含 NS_GW_RX_INFO结构体数组
 
 NS_GW_RX_INFO 结构体 对应一个终端
 
 该结构体
Data
Size 整个Data的字节数
Data +0 第一个字节 右移五位 命令字 是入网 还是 上传数据 还是下行数据
 FHDR Frame header structure
Data + 1 右移1个字节 获取第一个32位整型 4字节的 devaddr
 
Data + 5 第五个字节 是 FCtrl 占一个字节
 
Data + 6 Data + 7 第6个字节起始 FCnt 占两个字节
 
Data + 8 Fopts 第8个字节 起始
 
占据0到15个字节不定 这里不定 是根据FCtrl的 up 或者down 的 foptslen（他只占1111 4个bit 最大值15） 来决定
 
 注意这里fopts 用来写什么 主要是来回上行同步 和 下行终端命令字
 fopts 第一个字节
 
 0x02 LinckCheckReq 由终端发送
 终端利用这个命令字来判断网络质量
 0x02 LinckCheckAns 由网关发送 是对LinckCheckReq的回复 包含接收信号的强度 告知终端质量
 
 0x03 LinkADRReq 由网关发送 向终端发送请求改变数据发送速率 发射功率 重传率 以及信道
 0x03 LinkADRAns 对LinkADRReq的回复
 
 0x04 DutyCycleReq 由网关发送 向终端发送的最大占空比
 0x04 DutyCycleAns 对DutyCycleReq的回复
 
 0x05 RXParamSetupReq 由网关发送 向终端设置接收时隙的参数
 0x05 RXParamSetupAns 对RXParamSetupReq的 应答
 
 0x06 DevStatusReq 由网关发送  向终端查询其状态
 0x06 DevStatusAns 返回终端状态 电池余量 与 网络状态
 0x07 NewChannelReq 创建或修改一个射频信道的定义
 0x07 NewChannelReq 对 NewChannelReq 的回复
 
 0x08 RXTimingSetupReq 由网关发送 设置接收时隙时间
 0x08 RXTimingSetupAns 对RXTimingSetupReq 回复
 
 
 
后面 是一个字节的FPort
 
 
Size 整个Data的字节数 减去 上面的len  剩余的size
 
 
最后才是终端携带的数据 最终携带的数据长度 是
 

 
 */

typedef struct st_ns_moterx {
    uint32_t up_seqnum_delay;
    
    bool confirmed;
    uint8_t __place_holder[3];  /* 占位符 */
    bool confirmed_ack;
    uint8_t __place_holder1[3];  /* 占位符 */
    uint32_t port;
    int size;
    uint8_t frame[256];
}MOTERX;

#endif /* LoraTest_h */
