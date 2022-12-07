#ifndef __XF_QUEUE_H
#define __XF_QUEUE_H

typedef struct xf_queue {
    struct xf_queue *prev, *next;
} xf_queue_t;

#define XF_QUEUE_INIT(x) ((x)->prev = (x), (x)->next = (x))

#define OFFSETOF(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define CONTAINEROF(ptr, type, member) ( \
		(type*)( ((char*)((type*)ptr)) - OFFSETOF(type, member)) )
#define XF_QUEUE_ENTRY(ptr, type, member) CONTAINEROF(ptr, type, member)

inline void __xf_queue_push(xf_queue_t * node, xf_queue_t *prev, xf_queue_t *next) {
    node->prev = prev;
    node->next = next;
    prev->next = node;
    next->prev = node;
}

inline void xf_queue_push_back(xf_queue_t *head, xf_queue_t * node) {
    __xf_queue_push(node, head->prev, head);
}

inline void xf_queue_push_head(xf_queue_t *head, xf_queue_t *node) {
    __xf_queue_push(node, head, head->next);
}
    
inline void xf_queue_del(xf_queue_t *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = 0;
    node->next = 0;
}

#define XF_QUEUE_FOREACH(head, iter, type, member)                   \
    for ( (iter) = xf_queue_entry((head)->next, type, member);       \
          (iter)->member != (head);                                  \
          (iter) = xf_queue_entry((iter)->member->next, type, member))


#define xf_queue_init XF_QUEUE_INIT
#define xf_queue_entry XF_QUEUE_ENTRY
#define xf_queue_foreach XF_QUEUE_FOREACH

#endif
