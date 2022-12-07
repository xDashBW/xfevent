#include "xf_event_dispatch.h"
#include "xf_event.h"
#include "xf_queue.h"
#include "xf_flag.h"

#include <assert.h>
#include <stdlib.h>


void xf_event_dispatch_init(xf_event_dispatch_t *dp) {
    xf_queue_init(&dp->wait);
    xf_queue_init(&dp->active);
    dp->epollop = xf_epoll_new();
    assert(dp->epollop != NULL);
}

void xf_event_dispatch_queue_add(xf_event_dispatch_t *dp,
                                 xf_event_t *ev, short flag) {
    if (flag == XF_EVENT_DISPATCH_QUEUE_WAIT) 
        xf_queue_push_back(&dp->wait, &ev->wait);
    else if (flag == XF_EVENT_DISPATCH_QUEUE_ACTIVE)
        xf_queue_push_back(&dp->active, &ev->active);
}

void xf_event_dispatch_queue_del(xf_event_dispatch_t *dp,
                                 xf_event_t *ev, short flag) {
    if (flag == XF_EVENT_DISPATCH_QUEUE_WAIT)
        xf_queue_del(&ev->wait);
    else if (flag == XF_EVENT_DISPATCH_QUEUE_ACTIVE) 
        xf_queue_del(&ev->active);
}

void xf_event_dispatch_loop(xf_event_dispatch_t *dp) {
    
    while (1) {
        xf_epoll_dispatch(dp->epollop);
        
        /* 从 active 队列里面取出事件，然后处理 */
        xf_event_t *active_e;
        xf_queue_foreach(&dp->active, active_e, xf_event_t, active) {
            active_e->callback(active_e->fd, active_e->ev, active_e->args);
        }
    }
}
