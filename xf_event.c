#include "xf_event.h"
#include "xf_flag.h"
#include "xf_queue.h"
#include "xf_event_dispatch.h"

#include <stdlib.h>

void xf_event_init(xf_event_t *e, xf_event_dispatch_t* dp, 
                   int fd, short ev, 
                   void(*cb)(int, short, void*)) {
    xf_queue_init(&e->wait);
    xf_queue_init(&e->active);
    
    e->dp = dp;
    e->fd = fd;
    e->ev = ev;
    e->callback = cb;
    e->args = NULL;
    e->is_active = 0;
}

void xf_event_add(xf_event_t *e) {
    /* 加入调度队列，然后是调用 loop 的 epoll 接口  */
    xf_event_dispatch_queue_add(e->dp, e, XF_EVENT_DISPATCH_QUEUE_WAIT);
    xf_epoll_add(e->dp->epollop, e);
}

void xf_event_del(xf_event_t *e) {
    /* 删除，可能在两个队列里面，可能是 active 队列和 wait 队列 */
    /* 如果处在激活队列 */
    if (e->is_active == 1) {
        /* fixme */
        xf_event_dispatch_queue_del(e->dp, e, XF_EVENT_DISPATCH_QUEUE_ACTIVE);
        e->is_active = 0;
    } else {
        xf_event_dispatch_queue_del(e->dp, e, XF_EVENT_DISPATCH_QUEUE_WAIT);
    }
    
    xf_epoll_del(e->dp->epollop, e);
}
