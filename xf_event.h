#ifndef __XF_EVENT_H
#define __XF_EVENT_H

#include "xf_queue.h"
#include "xf_flag.h"

typedef struct xf_event_dispatch xf_event_dispatch_t;

typedef struct xf_event {
    xf_queue_t wait;            // 等待队列
    xf_queue_t active;          // 激活队列
    xf_event_dispatch_t *dp;
    int fd;                     // only socket fd
    short ev;                   // 只有网络读，写，所以只要标志者两个事件就行了
    void (*callback) (int fd, short ev, void *args);
    void *args;
    int is_active;                 // 是否处于激活队列中？
} xf_event_t; 

void xf_event_init(xf_event_t *e, xf_event_dispatch_t* dp, 
                   int fd, short ev, 
                   void(*cb)(int, short, void*));

void xf_event_add(xf_event_t *e);
void xf_event_del(xf_event_t *e);

#endif
