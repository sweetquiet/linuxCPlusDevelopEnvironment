//
//  main.c
//  LIBEV
//
//  Created by admindyn on 2018/3/6.
//  Copyright © 2018年 admindyn. All rights reserved.
//
#include "cJSON.h"
#include <ev.h>
#include <stdio.h>

ev_io stdin_wacher;
ev_timer timeout_watcher;

/*
  ev_io事件的回调函数，当有输入流stdin时，调用函数
 当有输入流stdin时调用函数
 */

static void stdin_cb(EV_P_ ev_io *w,int revents)
{
    puts("stdin ready");
    /*
     对ev_io事件的监控不会自动停止 需要手动在需要的时候停止
     EV_A_ 代表着 struct ev_loop* loop， loop这个指针
     并且 宏定义 已经加了逗号  因此下面两个参数 但是没有逗号
     */
    
    ev_io_stop(EV_A_ w);
    
    /*
     整体的loop时间在所有监控停止时停止 也可以手动关闭全部的ev_run
     */
    ev_break(EV_A_ EVBREAK_ALL);
    
}
/*
 时间事件的自定义回调函数 可定时触发
 */

static void timeout_cb(EV_P_ ev_timer*w,int revents)
{
    puts("time out");
    
    /*
     关闭最早的一个还在运行的ev_run
     */
    
    ev_break(EV_A_ EVBREAK_ONE);
    
}


/*
 {
 "name": "Awesome 4K",
 "resolutions": [
 {
 "width": 1280,
 "height": 720
 },
 {
 "width": 1920,
 "height": 1080
 },
 {
 "width": 3840,
 "height": 2160
 }
 ]
 }
 ---
 Let's build the above JSON and print it to a string:
 ```c
 //create a monitor with a list of supported resolutions
 */
/*
 方法一
 构建JSON对象 并形成JSON字符串
 */
char* create_monitor(void)
{
    const unsigned int resolution_numbers[3][2] = {
        {1280, 720},
        {1920, 1080},
        {3840, 2160}
    };
    char *string = NULL;
    cJSON *name = NULL;
    cJSON *resolutions = NULL;
    cJSON *resolution = NULL;
    cJSON *width = NULL;
    cJSON *height = NULL;
    size_t index = 0;
    
    cJSON *monitor = cJSON_CreateObject();
    if (monitor == NULL)
    {
        goto end;
    }
    
    name = cJSON_CreateString("Awesome 4K");
    if (name == NULL)
    {
        goto end;
    }
    /* after creation was successful, immediately add it to the monitor,
     * thereby transfering ownership of the pointer to it */
    cJSON_AddItemToObject(monitor, "name", name);
    
    resolutions = cJSON_CreateArray();
    if (resolutions == NULL)
    {
        goto end;
    }
    cJSON_AddItemToObject(monitor, "resolutions", resolutions);
    
    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
    {
        resolution = cJSON_CreateObject();
        if (resolution == NULL)
        {
            goto end;
        }
        cJSON_AddItemToArray(resolutions, resolution);
        
        width = cJSON_CreateNumber(resolution_numbers[index][0]);
        if (width == NULL)
        {
            goto end;
        }
        cJSON_AddItemToObject(resolution, "width", width);
        
        height = cJSON_CreateNumber(resolution_numbers[index][1]);
        if (height == NULL)
        {
            goto end;
        }
        cJSON_AddItemToObject(resolution, "height", height);
    }
    
    string = cJSON_Print(monitor);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }
    
end:
    cJSON_Delete(monitor);
    return string;
}
/*
 Alternatively we can use the `cJSON_Add...ToObject` helper functions to make our lifes a little easier
 */
/*
 方法二
 构建JSON对象 并形成JSON字符串
 */
char *create_monitor_with_helpers(void)
{
    const unsigned int resolution_numbers[3][2] = {
        {1280, 720},
        {1920, 1080},
        {3840, 2160}
    };
    char *string = NULL;
    cJSON *resolutions = NULL;
    size_t index = 0;
    
    cJSON *monitor = cJSON_CreateObject();
    
    if (cJSON_AddStringToObject(monitor, "name", "Awesome 4K") == NULL)
    {
        goto end;
    }
    
    resolutions = cJSON_AddArrayToObject(monitor, "resolutions");
    if (resolutions == NULL)
    {
        goto end;
    }
    
    for (index = 0; index < (sizeof(resolution_numbers) / (2 * sizeof(int))); ++index)
    {
        cJSON *resolution = cJSON_CreateObject();
        
        if (cJSON_AddNumberToObject(resolution, "width", resolution_numbers[index][0]) == NULL)
        {
            goto end;
        }
        
        if(cJSON_AddNumberToObject(resolution, "height", resolution_numbers[index][1]) == NULL)
        {
            goto end;
        }
        
        cJSON_AddItemToArray(resolutions, resolution);
    }
    
    string = cJSON_Print(monitor);
    if (string == NULL) {
        fprintf(stderr, "Failed to print monitor.\n");
    }
    
end:
    cJSON_Delete(monitor);
    return string;
}
/*
 上面两个方法 都是构建JSON对象 并形成JSON字符串
 */

/*
 解析JSON
 */
int supports_full_hd(const char * const monitor)
{
    const cJSON *resolution = NULL;
    const cJSON *resolutions = NULL;
    const cJSON *name = NULL;
    int status = 0;
    cJSON *monitor_json = cJSON_Parse(monitor);
    if (monitor_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        goto end;
    }
    
    name = cJSON_GetObjectItemCaseSensitive(monitor_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking monitor \"%s\"\n", name->valuestring);
    }
    
    resolutions = cJSON_GetObjectItemCaseSensitive(monitor_json, "resolutions");
    cJSON_ArrayForEach(resolution, resolutions)
    {
        cJSON *width = cJSON_GetObjectItemCaseSensitive(resolution, "width");
        cJSON *height = cJSON_GetObjectItemCaseSensitive(resolution, "height");
        
        if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height))
        {
            status = 0;
            goto end;
        }
        
        if ((width->valuedouble == 1920) && (height->valuedouble == 1080))
        {
            status = 1;
            goto end;
        }
    }
    
end:
    cJSON_Delete(monitor_json);
    return status;
}
/*
 http://blog.csdn.net/cxy450019566/article/details/52606512
 */
int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    /*
     封装JSON数据
     */
   char * res = create_monitor();
    /*
     输出JSON字符串
     */
    printf("%s\n",res);
    /*
     解析JSON数据
     
     */
    supports_full_hd(res);
    
    /*
     定义默认的event_loop 它就像一个大容器 可以装载很多事件不停运行
     EV_DEFAULT宏是以下指令：
     
     ev_default_loop(EVBACKEND_POLL | EVBACKEND_SELECT | EVFLAG_NOENV);
     
     返回一个最基础的ev_loop，并自动完成它的初始化，注意，如果程序中已经执行过该创建，将直接返回之前的创建。
     */
    
    struct ev_loop * loop = EV_DEFAULT;
    
    /*
     初始化ev_io事件监控 并设置它的回调函数 和 stdin
     */
    
    ev_io_init(&stdin_wacher,stdin_cb,0/*模式 STDIN_FILENO*/,EV_READ);
    
        ev_io_start(EV_A_ &stdin_wacher);
    
    
    /*
     初始化 ev_timer事件监控
     设置它的回调函数
     间隔时间
     是否重复
     */
    
    ev_timer_init(&timeout_watcher, timeout_cb, 5.5, 0);
    
    /*
     将ev_timer事件放到event loop里运行起来
     */
    ev_timer_start(EV_A_ &timeout_watcher);
    
    
    
    /*
     函数ev_run(loop, int flags)
     flags的作用，用于设置ev_loop的运行方式：
     
     通常设置为0，表示该ev_loop在所有watcher结束后停止，也可以手动break，官方鼓励手动break。
     
     除了0之外，还有一些选择，如EVRUN_NOWAIT、EVRUN_ONCE
     */
    ev_loop(EV_A_ 0);
    
    
    
    
    
    
    
    
    
    return 0;
}

















