#include "xf_queue.h"
#include "xf_event.h"
#include "xf_epoll.h"

typedef struct xf_event_dispatch {
    xf_queue_t wait;            // 等待队列
    xf_queue_t active;          // 激活队列
    
    xf_epoll_t * epollop;
    
} xf_event_dispatch_t;

void xf_event_dispatch_init(xf_event_dispatch_t *dp);
void xf_event_dispatch_queue_add(xf_event_dispatch_t *dp, xf_event_t *ev, short flag);
void xf_event_dispatch_queue_del(xf_event_dispatch_t *dp, xf_event_t *ev, short flag);
void xf_event_dispatch_loop(xf_event_dispatch_t *dp);
