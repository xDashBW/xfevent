#ifndef __XF_EVENT_H
#define __XF_EVENT_H

#include "xf_queue.h"

typedef struct xf_eventloop xf_eventloop_t;

typedef struct xf_event {
    xf_queue_t wait;            // 等待队列
    xf_queue_t active;          // 激活队列
    
    xf_eventloop_t *loop;
    
    int fd;                     // only socket fd
    short ev;                   // 只有网络读，写，所以只要标志者两个事件就行了
    void (*callback) (int fd, short ev, void *args);
    void *args;
    
} xf_event_t; 

void xf_event_init(xf_event_t *e, int fd, short ev, void(*cb)(int, short, void*));

void xf_event_add(xf_event_t *e, xf_eventloop_t *loop);
void xf_event_del(xf_event_t *e, xf_eventloop_t *loop);

#endif
