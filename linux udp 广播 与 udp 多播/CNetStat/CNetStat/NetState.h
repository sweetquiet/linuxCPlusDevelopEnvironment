//
//  NetState.h
//  CNetStat
//
//  Created by admindyn on 2018/7/11.
//  Copyright © 2018年 admindyn. All rights reserved.
//

#ifndef NetState_h
#define NetState_h

#include <stdio.h>



int info_list(int all);

int get_interface_info(char *interface_name);
int set_interface(char *interface_name);
int get_ipaddr(char *interface_name);
int get_mac(char *interface_name);
int get_netmask(char *interface_name);
int get_broadcast(char *interface_name);
int set_ipaddr(char *interface_name, char *ip);
int set_mac(char *interface_name, char *mac);
int set_netmask(char *interface_name, char *netmask);
int set_broadcast(char *interface_name, char *broadcast);

int interface_up(char *interface_name);
int interface_down(char *interface_name);

int usage();












#endif /* NetState_h */
